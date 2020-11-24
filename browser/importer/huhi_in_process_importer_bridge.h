/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_IMPORTER_HUHI_IN_PROCESS_IMPORTER_BRIDGE_H_
#define HUHI_BROWSER_IMPORTER_HUHI_IN_PROCESS_IMPORTER_BRIDGE_H_

#include <string>

#include "huhi/common/importer/huhi_importer_bridge.h"
#include "chrome/browser/importer/in_process_importer_bridge.h"

class HuhiInProcessImporterBridge : public InProcessImporterBridge,
                                     public HuhiImporterBridge {
 public:
  using InProcessImporterBridge::InProcessImporterBridge;

  HuhiInProcessImporterBridge(const HuhiInProcessImporterBridge&) = delete;
  HuhiInProcessImporterBridge operator=(
      const HuhiInProcessImporterBridge&) = delete;

  // HuhiImporterBridge overrides:
  void SetCreditCard(const base::string16& name_on_card,
                     const base::string16& expiration_month,
                     const base::string16& expiration_year,
                     const base::string16& decrypted_card_number,
                     const std::string& origin) override;

 private:
  ~HuhiInProcessImporterBridge() override;
};

#endif  // HUHI_BROWSER_IMPORTER_HUHI_IN_PROCESS_IMPORTER_BRIDGE_H_
