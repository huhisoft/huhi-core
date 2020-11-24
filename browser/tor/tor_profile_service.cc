/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/tor/tor_profile_service.h"

#include <string>

#include "huhi/browser/huhi_browser_process_impl.h"
// TODO(bridiver) - move this out of extensions
#include "huhi/browser/extensions/huhi_tor_client_updater.h"
#include "huhi/browser/tor/tor_launcher_service_observer.h"
#include "huhi/common/tor/pref_names.h"
#include "chrome/common/channel_info.h"
#include "components/version_info/channel.h"
#include "components/pref_registry/pref_registry_syncable.h"
#include "components/prefs/pref_registry_simple.h"
#include "components/prefs/pref_service.h"

namespace tor {

namespace {

constexpr char kTorProxyScheme[] = "socks5://";
constexpr char kTorProxyAddress[] = "127.0.0.1";

}  // namespace

TorProfileService::TorProfileService() {
}

TorProfileService::~TorProfileService() {
}

// static
void TorProfileService::RegisterLocalStatePrefs(PrefRegistrySimple* registry) {
  std::string port;
  switch (chrome::GetChannel()) {
    case version_info::Channel::STABLE:
      port = std::string("9350");
      break;
    case version_info::Channel::BETA:
      port = std::string("9360");
      break;
    case version_info::Channel::DEV:
      port = std::string("9370");
      break;
    case version_info::Channel::CANARY:
      port = std::string("9380");
      break;
    case version_info::Channel::UNKNOWN:
    default:
      port = std::string("9390");
  }
  const std::string tor_proxy_uri =
      std::string(kTorProxyScheme) + std::string(kTorProxyAddress) + ":" + port;
  registry->RegisterStringPref(prefs::kTorProxyString, tor_proxy_uri);
  registry->RegisterBooleanPref(prefs::kTorDisabled, false);
}

// static
bool TorProfileService::IsTorDisabled() {
  if (!g_huhi_browser_process)
    return false;
  return g_browser_process->local_state()->GetBoolean(prefs::kTorDisabled);
}

// static
void TorProfileService::SetTorDisabled(bool disabled) {
  if (g_huhi_browser_process)
    g_browser_process->local_state()->SetBoolean(prefs::kTorDisabled, disabled);
}

// static
void TorProfileService::RegisterTorClientUpdater() {
  if (g_huhi_browser_process) {
    g_huhi_browser_process->tor_client_updater()->Register();
  }
}

// static
void TorProfileService::UnregisterTorClientUpdater() {
  if (g_huhi_browser_process) {
    g_huhi_browser_process->tor_client_updater()->Unregister();
  }
}

std::string TorProfileService::GetTorProxyURI() {
  return g_browser_process->local_state()->GetString(prefs::kTorProxyString);
}

base::FilePath TorProfileService::GetTorExecutablePath() {
  return g_huhi_browser_process->tor_client_updater()->GetExecutablePath();
}

void TorProfileService::AddObserver(TorLauncherServiceObserver* observer) {
  observers_.AddObserver(observer);
}

void TorProfileService::RemoveObserver(TorLauncherServiceObserver* observer) {
  observers_.RemoveObserver(observer);
}

}  // namespace tor
