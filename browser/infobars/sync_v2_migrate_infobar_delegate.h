// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_BROWSER_INFOBARS_SYNC_V2_MIGRATE_INFOBAR_DELEGATE_H_
#define HUHI_BROWSER_INFOBARS_SYNC_V2_MIGRATE_INFOBAR_DELEGATE_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/strings/string16.h"
#include "components/infobars/core/confirm_infobar_delegate.h"
#include "url/gurl.h"

class Browser;
class InfoBarService;
class Profile;
class PrefService;

namespace huhi_sync {
class Prefs;
}  // namespace huhi_sync

// An infobar that is run with a string, buttons, and a "Learn More" link.
class SyncV2MigrateInfoBarDelegate : public ConfirmInfoBarDelegate {
 public:
  static void Create(InfoBarService* infobar_service, bool is_v2_user,
                                            Profile* profile, Browser* browser);

 private:
  explicit SyncV2MigrateInfoBarDelegate(Browser* browser, Profile* profile);
  ~SyncV2MigrateInfoBarDelegate() override;

  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  const gfx::VectorIcon& GetVectorIcon() const override;
  bool ShouldExpire(const NavigationDetails& details) const override;
  void InfoBarDismissed() override;
  base::string16 GetMessageText() const override;
  int GetButtons() const override;
  base::string16 GetButtonLabel(InfoBarButton button) const override;
  bool Accept() override;

  Profile* profile_;
  Browser* browser_;

  DISALLOW_COPY_AND_ASSIGN(SyncV2MigrateInfoBarDelegate);
};

#endif  // HUHI_BROWSER_INFOBARS_SYNC_V2_MIGRATE_INFOBAR_DELEGATE_H_
