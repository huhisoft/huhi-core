// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/infobars/sync_v2_migrate_infobar_delegate.h"

#include <memory>
#include <utility>

#include "base/feature_list.h"
#include "huhi/browser/ui/huhi_pages.h"
#include "huhi/common/pref_names.h"
#include "huhi/common/url_constants.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "huhi/components/huhi_sync/features.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/infobars/infobar_service.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "chrome/browser/ui/chrome_pages.h"
#include "chrome/grit/chromium_strings.h"
#include "components/infobars/core/infobar.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/vector_icons.h"

// static
void SyncV2MigrateInfoBarDelegate::Create(
    InfoBarService* infobar_service, bool is_v2_user, Profile* profile,
    Browser* browser) {
  // Show infobar if user had enabled sync v1 (even if they hadn't
  // re-enabled it via the flag).
  // Don't show infobar if:
  // - sync flag is disabled
  // - problem with local_state
  // - user has setup sync v2
  // - dismissed notification (don't auto-dismiss)
  const bool is_flag_enabled =
      base::FeatureList::IsEnabled(huhi_sync::features::kHuhiSync);
  if (!is_flag_enabled) {
    return;
  }
  huhi_sync::Prefs huhi_sync_prefs(profile->GetPrefs());
  const bool was_v1_user = huhi_sync_prefs.IsSyncV1Enabled();
  if (!was_v1_user) {
    // Not v1 user
    return;
  }
  const bool has_dismissed = huhi_sync_prefs.IsSyncMigrateNoticeDismissed();
  if (has_dismissed) {
    return;
  }
  if (is_v2_user) {
    // Make sure this doesn't automatically show again if sync is turned off.
    // TODO(petemill): Might be better to change a pref in an event handler
    // rather than here.
    huhi_sync_prefs.SetDismissSyncMigrateNotice(true);
    return;
  }
  // Show infobar
  infobar_service->AddInfoBar(infobar_service->CreateConfirmInfoBar(
      std::unique_ptr<ConfirmInfoBarDelegate>(
          new SyncV2MigrateInfoBarDelegate(browser, profile))));
}

// Start class impl
SyncV2MigrateInfoBarDelegate::SyncV2MigrateInfoBarDelegate(Browser* browser,
    Profile* profile)
          : ConfirmInfoBarDelegate(),
            profile_(profile),
            browser_(browser) {
}

SyncV2MigrateInfoBarDelegate::~SyncV2MigrateInfoBarDelegate() {
}

infobars::InfoBarDelegate::InfoBarIdentifier
SyncV2MigrateInfoBarDelegate::GetIdentifier() const {
  return SYNC_V2_MIGRATE_INFOBAR_DELEGATE;
}

const gfx::VectorIcon& SyncV2MigrateInfoBarDelegate::GetVectorIcon() const {
  return views::kInfoIcon;
}

bool SyncV2MigrateInfoBarDelegate::ShouldExpire(
    const NavigationDetails& details) const {
  return false;
}

void SyncV2MigrateInfoBarDelegate::InfoBarDismissed() {
  huhi_sync::Prefs huhi_sync_prefs(profile_->GetPrefs());
  huhi_sync_prefs.SetDismissSyncMigrateNotice(true);
}

base::string16 SyncV2MigrateInfoBarDelegate::GetMessageText() const {
  return l10n_util::GetStringUTF16(IDS_HUHI_SYNC_V2_MIGRATE_INFOBAR_MESSAGE);
}

int SyncV2MigrateInfoBarDelegate::GetButtons() const {
  return BUTTON_OK;
}

base::string16 SyncV2MigrateInfoBarDelegate::GetButtonLabel(
    InfoBarButton button) const {
  return l10n_util::GetStringUTF16(IDS_HUHI_SYNC_V2_MIGRATE_INFOBAR_COMMAND);
}

bool SyncV2MigrateInfoBarDelegate::Accept() {
  huhi::ShowSync(browser_);
  return true;
}
