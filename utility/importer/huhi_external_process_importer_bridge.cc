/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/utility/importer/huhi_external_process_importer_bridge.h"

#include <utility>

HuhiExternalProcessImporterBridge::HuhiExternalProcessImporterBridge(
    const base::flat_map<uint32_t, std::string>& localized_strings,
    mojo::SharedRemote<chrome::mojom::ProfileImportObserver> observer,
    mojo::SharedRemote<huhi::mojom::ProfileImportObserver> huhi_observer)
    : ExternalProcessImporterBridge(std::move(localized_strings),
                                         std::move(observer)),
      huhi_observer_(std::move(huhi_observer)) {}

HuhiExternalProcessImporterBridge::
    ~HuhiExternalProcessImporterBridge() = default;

void HuhiExternalProcessImporterBridge::SetCreditCard(
    const base::string16& name_on_card,
    const base::string16& expiration_month,
    const base::string16& expiration_year,
    const base::string16& decrypted_card_number,
    const std::string& origin) {
  huhi_observer_->OnCreditCardImportReady(
      name_on_card, expiration_month,
      expiration_year, decrypted_card_number,
      origin);
}
