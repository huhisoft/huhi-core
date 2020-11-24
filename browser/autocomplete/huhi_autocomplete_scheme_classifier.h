/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_AUTOCOMPLETE_HUHI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_
#define HUHI_BROWSER_AUTOCOMPLETE_HUHI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

#include <string>

#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"
#include "chrome/browser/autocomplete/chrome_autocomplete_scheme_classifier.h"

class HuhiAutocompleteSchemeClassifier
    : public ChromeAutocompleteSchemeClassifier {
 public:
  explicit HuhiAutocompleteSchemeClassifier(Profile* profile);
  ~HuhiAutocompleteSchemeClassifier() override;

  metrics::OmniboxInputType GetInputTypeForScheme(
      const std::string& scheme) const override;

 private:
#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
  Profile* profile_ = nullptr;
#endif

  DISALLOW_COPY_AND_ASSIGN(HuhiAutocompleteSchemeClassifier);
};

#endif  // HUHI_BROWSER_AUTOCOMPLETE_HUHI_AUTOCOMPLETE_SCHEME_CLASSIFIER_H_

