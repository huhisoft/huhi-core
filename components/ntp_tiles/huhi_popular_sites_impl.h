/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_NTP_TILES_HUHI_POPULAR_SITES_IMPL_H_
#define HUHI_COMPONENTS_NTP_TILES_HUHI_POPULAR_SITES_IMPL_H_

#include <map>

#include "components/ntp_tiles/popular_sites_impl.h"

namespace ntp_tiles {

class HuhiPopularSitesImpl : public PopularSitesImpl {
 public:
  using PopularSitesImpl::PopularSitesImpl;

  // PopularSitesImpl overrides:
  const std::map<SectionType, SitesVector>& sections() const override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiPopularSitesImpl);
};

}  // namespace ntp_tiles

#endif  // HUHI_COMPONENTS_NTP_TILES_HUHI_POPULAR_SITES_IMPL_H_
