/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/extensions/huhi_component_loader.h"

#include <string>

#include "base/bind.h"
#include "base/command_line.h"
#include "bat/ads/pref_names.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/component_updater/huhi_component_installer.h"
#include "huhi/common/huhi_switches.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_ads/common/pref_names.h"
#include "huhi/components/huhi_component_updater/browser/huhi_on_demand_updater.h"
#include "huhi/components/huhi_extension/grit/huhi_extension.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/common/pref_names.h"
#include "huhi/components/huhi_rewards/resources/extension/grit/huhi_rewards_extension_resources.h"
#include "huhi/components/huhi_webtorrent/grit/huhi_webtorrent_resources.h"
#include "chrome/browser/extensions/extension_service.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/common/pref_names.h"
#include "components/grit/huhi_components_resources.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "extensions/browser/extension_prefs.h"
#include "extensions/browser/extension_registry.h"
#include "extensions/browser/extension_system.h"
#include "extensions/common/constants.h"

#if BUILDFLAG(HUHI_WALLET_ENABLED)
#include "huhi/browser/extensions/huhi_wallet_util.h"
#include "huhi/components/huhi_wallet/huhi_wallet_constants.h"
#include "huhi/components/huhi_wallet/pref_names.h"
#endif

namespace extensions {

HuhiComponentLoader::HuhiComponentLoader(ExtensionSystem* extension_system,
                                           Profile* profile)
    : ComponentLoader(extension_system, profile),
      profile_(profile),
      profile_prefs_(profile->GetPrefs()) {
#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  pref_change_registrar_.Init(profile_prefs_);
  pref_change_registrar_.Add(huhi_rewards::prefs::kAutoContributeEnabled,
      base::Bind(&HuhiComponentLoader::CheckRewardsStatus,
      base::Unretained(this)));
#endif
}

HuhiComponentLoader::~HuhiComponentLoader() {
}

void HuhiComponentLoader::OnComponentRegistered(std::string extension_id) {
  huhi_component_updater::HuhiOnDemandUpdater::GetInstance()->OnDemandUpdate(
      extension_id);
}

void HuhiComponentLoader::OnComponentReady(std::string extension_id,
    bool allow_file_access,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  Add(manifest, install_dir);
  if (allow_file_access) {
    ExtensionPrefs::Get(profile_)->SetAllowFileAccess(extension_id, true);
  }
}

void HuhiComponentLoader::AddExtension(const std::string& extension_id,
    const std::string& name, const std::string& public_key) {
  huhi::RegisterComponent(g_browser_process->component_updater(),
    name,
    public_key,
    base::Bind(&HuhiComponentLoader::OnComponentRegistered,
        base::Unretained(this), extension_id),
    base::Bind(&HuhiComponentLoader::OnComponentReady,
        base::Unretained(this), extension_id, true));
}

void HuhiComponentLoader::AddHangoutServicesExtension() {
  if (!profile_prefs_->FindPreference(kHangoutsEnabled) ||
      profile_prefs_->GetBoolean(kHangoutsEnabled)) {
    ForceAddHangoutServicesExtension();
  }
}

void HuhiComponentLoader::ForceAddHangoutServicesExtension() {
  ComponentLoader::AddHangoutServicesExtension();
}

void HuhiComponentLoader::AddDefaultComponentExtensions(
    bool skip_session_components) {
  ComponentLoader::AddDefaultComponentExtensions(skip_session_components);

  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableHuhiExtension)) {
    base::FilePath huhi_extension_path(FILE_PATH_LITERAL(""));
    huhi_extension_path =
        huhi_extension_path.Append(FILE_PATH_LITERAL("huhi_extension"));
    Add(IDR_HUHI_EXTENSION, huhi_extension_path);
  }

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  // Enable rewards extension if already opted-in
  CheckRewardsStatus();
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
  // Only load if the eagerly load Crypto Wallets setting is on and there is a
  // project id configured in the build.
  if (HasInfuraProjectID() &&
      profile_prefs_->GetBoolean(kLoadCryptoWalletsOnStartup)) {
    AddEthereumRemoteClientExtension();
  }
#endif
}

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
void HuhiComponentLoader::AddRewardsExtension() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableHuhiRewardsExtension) &&
      !Exists(huhi_rewards_extension_id)) {
    base::FilePath huhi_rewards_path(FILE_PATH_LITERAL(""));
    huhi_rewards_path =
        huhi_rewards_path.Append(FILE_PATH_LITERAL("huhi_rewards"));
    Add(IDR_HUHI_REWARDS, huhi_rewards_path);
  }
}

void HuhiComponentLoader::CheckRewardsStatus() {
  const bool is_ac_enabled = profile_prefs_->GetBoolean(
      huhi_rewards::prefs::kAutoContributeEnabled);

  if (is_ac_enabled) {
    AddRewardsExtension();
  }
}
#endif

#if BUILDFLAG(HUHI_WALLET_ENABLED)
void HuhiComponentLoader::AddEthereumRemoteClientExtension() {
  AddExtension(ethereum_remote_client_extension_id,
      ethereum_remote_client_extension_name,
      ethereum_remote_client_extension_public_key);
}
#endif

void HuhiComponentLoader::AddWebTorrentExtension() {
  const base::CommandLine& command_line =
      *base::CommandLine::ForCurrentProcess();
  if (!command_line.HasSwitch(switches::kDisableWebTorrentExtension) &&
      (!profile_prefs_->FindPreference(kWebTorrentEnabled) ||
      profile_prefs_->GetBoolean(kWebTorrentEnabled))) {
    base::FilePath huhi_webtorrent_path(FILE_PATH_LITERAL(""));
    huhi_webtorrent_path =
      huhi_webtorrent_path.Append(FILE_PATH_LITERAL("huhi_webtorrent"));
    Add(IDR_HUHI_WEBTORRENT, huhi_webtorrent_path);
  }
}

}  // namespace extensions
