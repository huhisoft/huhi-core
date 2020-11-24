/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/infobars/ipfs_infobar_delegate.h"

#include <memory>
#include <utility>

#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/ui/huhi_pages.h"
#include "huhi/components/ipfs/browser/huhi_ipfs_client_updater.h"
#include "huhi/components/ipfs/common/ipfs_constants.h"
#include "huhi/common/pref_names.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "chrome/browser/infobars/infobar_service.h"
#include "chrome/browser/ui/browser_finder.h"
#include "components/infobars/core/infobar.h"
#include "components/prefs/pref_service.h"
#include "components/user_prefs/user_prefs.h"
#include "content/public/browser/browser_context.h"
#include "ui/base/l10n/l10n_util.h"
#include "ui/views/vector_icons.h"

// static
void IPFSInfoBarDelegate::Create(InfoBarService* infobar_service) {
  infobar_service->AddInfoBar(infobar_service->CreateConfirmInfoBar(
      std::unique_ptr<ConfirmInfoBarDelegate>(
          new IPFSInfoBarDelegate())));
}

IPFSInfoBarDelegate::IPFSInfoBarDelegate() {}

IPFSInfoBarDelegate::~IPFSInfoBarDelegate() {}

infobars::InfoBarDelegate::InfoBarIdentifier
IPFSInfoBarDelegate::GetIdentifier() const {
  return IPFS_INFOBAR_DELEGATE;
}

const gfx::VectorIcon& IPFSInfoBarDelegate::GetVectorIcon() const {
  return views::kInfoIcon;
}

void IPFSInfoBarDelegate::InfoBarDismissed() {
}

base::string16 IPFSInfoBarDelegate::GetMessageText() const {
  return l10n_util::GetStringUTF16(IDS_HUHI_IPFS_INSTALL);
}

int IPFSInfoBarDelegate::GetButtons() const {
  return BUTTON_OK | BUTTON_CANCEL;
}

base::string16 IPFSInfoBarDelegate::GetButtonLabel(
    InfoBarButton button) const {
  if (button == BUTTON_CANCEL) {
    return l10n_util::GetStringUTF16(IDS_HUHI_IPFS_SETTINGS);
  }

  return l10n_util::GetStringUTF16(IDS_HUHI_IPFS_ENABLE_IPFS);
}

base::string16 IPFSInfoBarDelegate::GetLinkText() const {
  return base::string16();
}

GURL IPFSInfoBarDelegate::GetLinkURL() const {
  return GURL();  // No learn more link for now.
}

bool IPFSInfoBarDelegate::Accept() {
  content::WebContents* web_contents =
    InfoBarService::WebContentsFromInfoBar(infobar());
  auto* browser_context = web_contents->GetBrowserContext();
  user_prefs::UserPrefs::Get(browser_context)->
      SetInteger(kIPFSResolveMethod,
          static_cast<int>(ipfs::IPFSResolveMethodTypes::IPFS_LOCAL));
  g_huhi_browser_process->ipfs_client_updater()->Register();
  return true;
}

bool IPFSInfoBarDelegate::Cancel() {
  content::WebContents* web_contents =
    InfoBarService::WebContentsFromInfoBar(infobar());
  if (web_contents) {
    Browser* browser = chrome::FindBrowserWithWebContents(web_contents);
    huhi::ShowExtensionSettings(browser);
  }

  return true;
}
