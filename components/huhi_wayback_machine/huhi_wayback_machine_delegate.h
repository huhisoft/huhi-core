/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_DELEGATE_H_
#define HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_DELEGATE_H_


namespace content {
class WebContents;
}  // namespace content

class HuhiWaybackMachineInfoBarDelegate;

class HuhiWaybackMachineDelegate {
 public:
  virtual ~HuhiWaybackMachineDelegate() = default;

  virtual void CreateInfoBar(content::WebContents* web_contents) = 0;
};

#endif  // HUHI_COMPONENTS_HUHI_WAYBACK_MACHINE_HUHI_WAYBACK_MACHINE_DELEGATE_H_
