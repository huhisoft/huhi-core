/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_UTILITY_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
#define HUHI_UTILITY_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_

#include <string>

#include "huhi/common/importer/huhi_importer_bridge.h"
#include "huhi/common/importer/profile_import.mojom.h"
#include "chrome/utility/importer/external_process_importer_bridge.h"

class HuhiExternalProcessImporterBridge : public ExternalProcessImporterBridge,
                                           public HuhiImporterBridge {
 public:
  HuhiExternalProcessImporterBridge(
      const base::flat_map<uint32_t, std::string>& localized_strings,
      mojo::SharedRemote<chrome::mojom::ProfileImportObserver> observer,
      mojo::SharedRemote<huhi::mojom::ProfileImportObserver> huhi_observer);

  HuhiExternalProcessImporterBridge(
      const HuhiExternalProcessImporterBridge&) = delete;
  HuhiExternalProcessImporterBridge& operator=(
      const HuhiExternalProcessImporterBridge&) = delete;

  void SetCreditCard(const base::string16& name_on_card,
                     const base::string16& expiration_month,
                     const base::string16& expiration_year,
                     const base::string16& decrypted_card_number,
                     const std::string& origin) override;

 private:
  ~HuhiExternalProcessImporterBridge() override;

  mojo::SharedRemote<huhi::mojom::ProfileImportObserver> huhi_observer_;
};

#endif  // HUHI_UTILITY_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_BRIDGE_H_
