/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
#define HUHI_BROWSER_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_

#include <string>

#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "huhi/common/importer/profile_import.mojom.h"
#include "chrome/browser/importer/external_process_importer_client.h"
#include "mojo/public/cpp/bindings/receiver.h"
#include "mojo/public/cpp/bindings/remote.h"

class HuhiExternalProcessImporterClient
    : public ExternalProcessImporterClient,
      public huhi::mojom::ProfileImportObserver {
 public:
  HuhiExternalProcessImporterClient(
      base::WeakPtr<ExternalProcessImporterHost> importer_host,
      const importer::SourceProfile& source_profile,
      uint16_t items,
      InProcessImporterBridge* bridge);

  HuhiExternalProcessImporterClient(
      const HuhiExternalProcessImporterClient&) = delete;
  HuhiExternalProcessImporterClient& operator=(
      const HuhiExternalProcessImporterClient&) = delete;

  // ExternalProcessImportClient overrides:
  void Start() override;
  void Cancel() override;
  void CloseMojoHandles() override;
  void OnImportItemFinished(importer::ImportItem import_item) override;

  // huhi::mojom::ProfileImportObserver overrides:
  void OnCreditCardImportReady(
      const base::string16& name_on_card,
      const base::string16& expiration_month,
      const base::string16& expiration_year,
      const base::string16& decrypted_card_number,
      const std::string& origin) override;

 protected:
  ~HuhiExternalProcessImporterClient() override;

 private:
  // Used to start and stop the actual huhi importer running in a different
  // process.
  mojo::Remote<huhi::mojom::ProfileImport> huhi_profile_import_;

  // Used to receive progress updates from the huhi importer.
  mojo::Receiver<huhi::mojom::ProfileImportObserver> huhi_receiver_{this};
};

#endif  // HUHI_BROWSER_IMPORTER_HUHI_EXTERNAL_PROCESS_IMPORTER_CLIENT_H_
