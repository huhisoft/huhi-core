/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/autocomplete/huhi_autocomplete_scheme_classifier.h"

#include <string>

#include "base/strings/string_util.h"
#include "huhi/common/url_constants.h"
#include "huhi/components/ipfs/browser/buildflags/buildflags.h"
#include "chrome/browser/profiles/profile.h"

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
#include "huhi/components/huhi_webtorrent/browser/webtorrent_util.h"
#endif

HuhiAutocompleteSchemeClassifier::HuhiAutocompleteSchemeClassifier(
    Profile* profile)
    : ChromeAutocompleteSchemeClassifier(profile) {
#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
  profile_ = profile;
#endif
}

HuhiAutocompleteSchemeClassifier::~HuhiAutocompleteSchemeClassifier() {
}

// Without this override, typing in huhi:// URLs will search Google
metrics::OmniboxInputType
HuhiAutocompleteSchemeClassifier::GetInputTypeForScheme(
    const std::string& scheme) const {
  if (scheme.empty()) {
    return metrics::OmniboxInputType::EMPTY;
  }
  if (base::IsStringASCII(scheme) &&
      base::LowerCaseEqualsASCII(scheme, kHuhiUIScheme)) {
    return metrics::OmniboxInputType::URL;
  }

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
  if (base::IsStringASCII(scheme) &&
      webtorrent::IsWebtorrentPrefEnabled(profile_) &&
      base::LowerCaseEqualsASCII(scheme, kMagnetScheme)) {
    return metrics::OmniboxInputType::URL;
  }
#endif

#if BUILDFLAG(IPFS_ENABLED)
  if (base::IsStringASCII(scheme) &&
      (base::LowerCaseEqualsASCII(scheme, kIPFSScheme) ||
       base::LowerCaseEqualsASCII(scheme, kIPNSScheme))) {
    return metrics::OmniboxInputType::URL;
  }
#endif


  return ChromeAutocompleteSchemeClassifier::GetInputTypeForScheme(scheme);
}
