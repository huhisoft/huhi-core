/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_UI_VIEWS_HUHI_LAYOUT_PROVIDER_H_
#define HUHI_BROWSER_UI_VIEWS_HUHI_LAYOUT_PROVIDER_H_

#include "base/macros.h"
#include "chrome/browser/ui/views/chrome_layout_provider.h"

class HuhiLayoutProvider : public ChromeLayoutProvider {
 public:
  HuhiLayoutProvider() = default;
  ~HuhiLayoutProvider() override = default;

  int GetCornerRadiusMetric(views::EmphasisMetric emphasis_metric,
                            const gfx::Size& size = gfx::Size()) const override;

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiLayoutProvider);
};

#endif  // HUHI_BROWSER_UI_VIEWS_HUHI_LAYOUT_PROVIDER_H_
