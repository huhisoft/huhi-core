/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/infobars/huhi_confirm_p3a_infobar_delegate.h"

#include <memory>
#include <utility>

#include "huhi/common/pref_names.h"
#include "huhi/common/url_constants.h"
#include "huhi/components/p3a/pref_names.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/infobars/infobar_service.h"
#include "chrome/grit/chromium_strings.h"
#include "components/infobars/core/infobar.h"
#include "components/prefs/pref_service.h"
#include "components/strings/grit/components_strings.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/vector_icons.h"

// static
void HuhiConfirmP3AInfoBarDelegate::Create(InfoBarService* infobar_service,
                                            PrefService* local_state) {
  // Don't show infobar if:
  // - P3A is disabled
  // - notice has already been acknowledged
  if (local_state) {
    if (!local_state->GetBoolean(huhi::kP3AEnabled) ||
        local_state->GetBoolean(huhi::kP3ANoticeAcknowledged)) {
      local_state->SetBoolean(huhi::kP3ANoticeAcknowledged, true);
      return;
    }
  }

  infobar_service->AddInfoBar(infobar_service->CreateConfirmInfoBar(
      std::unique_ptr<ConfirmInfoBarDelegate>(
          new HuhiConfirmP3AInfoBarDelegate(local_state))));
}

HuhiConfirmP3AInfoBarDelegate::HuhiConfirmP3AInfoBarDelegate(
    PrefService* local_state)
    : ConfirmInfoBarDelegate(), local_state_(local_state) {}

HuhiConfirmP3AInfoBarDelegate::~HuhiConfirmP3AInfoBarDelegate() {}

infobars::InfoBarDelegate::InfoBarIdentifier
HuhiConfirmP3AInfoBarDelegate::GetIdentifier() const {
  return HUHI_CONFIRM_P3A_INFOBAR_DELEGATE;
}

const gfx::VectorIcon& HuhiConfirmP3AInfoBarDelegate::GetVectorIcon() const {
  return views::kInfoIcon;
}

bool HuhiConfirmP3AInfoBarDelegate::ShouldExpire(
    const NavigationDetails& details) const {
  return false;
}

void HuhiConfirmP3AInfoBarDelegate::InfoBarDismissed() {
  // Mark notice as acknowledged when infobar is dismissed
  if (local_state_) {
    local_state_->SetBoolean(huhi::kP3ANoticeAcknowledged, true);
  }
}

base::string16 HuhiConfirmP3AInfoBarDelegate::GetMessageText() const {
  return l10n_util::GetStringUTF16(IDS_HUHI_CONFIRM_P3A_INFO_BAR);
}

int HuhiConfirmP3AInfoBarDelegate::GetButtons() const {
  return BUTTON_OK | BUTTON_CANCEL;
}

base::string16 HuhiConfirmP3AInfoBarDelegate::GetButtonLabel(
    InfoBarButton button) const {
  if (button == BUTTON_CANCEL) {
    return l10n_util::GetStringUTF16(IDS_HUHI_CONFIRM_P3A_INFO_BAR_DISABLE);
  }
  return l10n_util::GetStringUTF16(IDS_HUHI_CONFIRM_P3A_INFO_BAR_ACKNOWLEDGE);
}

base::string16 HuhiConfirmP3AInfoBarDelegate::GetLinkText() const {
  return l10n_util::GetStringUTF16(IDS_LEARN_MORE);
}

GURL HuhiConfirmP3AInfoBarDelegate::GetLinkURL() const {
  return GURL(kP3ALearnMoreURL);
}

bool HuhiConfirmP3AInfoBarDelegate::Accept() {
  // Mark notice as acknowledged when infobar is dismissed
  if (local_state_) {
    local_state_->SetBoolean(huhi::kP3ANoticeAcknowledged, true);
  }
  return true;
}

bool HuhiConfirmP3AInfoBarDelegate::Cancel() {
  // OK button is "Disable"
  // Clicking should disable P3A
  if (local_state_) {
    local_state_->SetBoolean(huhi::kP3AEnabled, false);
  }
  return true;
}
