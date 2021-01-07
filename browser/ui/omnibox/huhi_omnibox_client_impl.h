/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_OMNIBOX_HUHI_OMNIBOX_CLIENT_IMPL_H_
#define HUHI_BROWSER_UI_OMNIBOX_HUHI_OMNIBOX_CLIENT_IMPL_H_

#include "huhi/browser/autocomplete/huhi_autocomplete_scheme_classifier.h"
#include "chrome/browser/ui/omnibox/chrome_omnibox_client.h"

class OmniboxEditController;
class PrefRegistrySimple;
class Profile;

class HuhiOmniboxClientImpl : public ChromeOmniboxClient {
 public:
  HuhiOmniboxClientImpl(OmniboxEditController* controller, Profile* profile);
  ~HuhiOmniboxClientImpl() override;

  static void RegisterPrefs(PrefRegistrySimple* prefs);

  const AutocompleteSchemeClassifier& GetSchemeClassifier() const override;
  bool IsAutocompleteEnabled() const override;

  void OnInputAccepted(const AutocompleteMatch& match) override;

 private:
  Profile* profile_;
  HuhiAutocompleteSchemeClassifier scheme_classifier_;

  DISALLOW_COPY_AND_ASSIGN(HuhiOmniboxClientImpl);
};

#endif  // HUHI_BROWSER_UI_OMNIBOX_HUHI_OMNIBOX_CLIENT_IMPL_H_
