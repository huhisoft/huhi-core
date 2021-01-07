/* Copyright 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/importer/huhi_external_process_importer_client.h"

#include <utility>

#include "base/bind.h"
#include "huhi/browser/importer/huhi_in_process_importer_bridge.h"
#include "chrome/browser/service_sandbox_type.h"
#include "chrome/grit/generated_resources.h"
#include "content/public/browser/service_process_host.h"

namespace {
bool ShouldUseHuhiImporter(importer::ImporterType type) {
  if (type == importer::TYPE_CHROME)
    return true;

  return false;
}
}  // namespace

HuhiExternalProcessImporterClient::HuhiExternalProcessImporterClient(
    base::WeakPtr<ExternalProcessImporterHost> importer_host,
    const importer::SourceProfile& source_profile,
    uint16_t items,
    InProcessImporterBridge* bridge)
    : ExternalProcessImporterClient(
          importer_host, source_profile, items, bridge) {}

HuhiExternalProcessImporterClient::
    ~HuhiExternalProcessImporterClient() = default;

void HuhiExternalProcessImporterClient::Start() {
  if (!ShouldUseHuhiImporter(source_profile_.importer_type)) {
    ExternalProcessImporterClient::Start();
    return;
  }

  AddRef();  // balanced in Cleanup.

  auto options = content::ServiceProcessHost::Options()
                     .WithDisplayName(IDS_UTILITY_PROCESS_PROFILE_IMPORTER_NAME)
                     .Pass();
  options.sandbox_type =
      content::GetServiceSandboxType<huhi::mojom::ProfileImport>();
  content::ServiceProcessHost::Launch(
      huhi_profile_import_.BindNewPipeAndPassReceiver(), std::move(options));

  huhi_profile_import_.set_disconnect_handler(
      base::BindOnce(&ExternalProcessImporterClient::OnProcessCrashed, this));

  base::flat_map<uint32_t, std::string> localized_strings;
  huhi_profile_import_->StartImport(
      source_profile_, items_, localized_strings,
      receiver_.BindNewPipeAndPassRemote(),
      huhi_receiver_.BindNewPipeAndPassRemote());
}

void HuhiExternalProcessImporterClient::Cancel() {
  if (!ShouldUseHuhiImporter(source_profile_.importer_type)) {
    ExternalProcessImporterClient::Cancel();
    return;
  }

  if (cancelled_)
    return;

  cancelled_ = true;
  huhi_profile_import_->CancelImport();
  CloseMojoHandles();
  Release();
}

void HuhiExternalProcessImporterClient::CloseMojoHandles() {
  if (!ShouldUseHuhiImporter(source_profile_.importer_type)) {
    ExternalProcessImporterClient::CloseMojoHandles();
    return;
  }

  huhi_profile_import_.reset();
  huhi_receiver_.reset();
  receiver_.reset();
}

void HuhiExternalProcessImporterClient::OnImportItemFinished(
    importer::ImportItem import_item) {
  if (!ShouldUseHuhiImporter(source_profile_.importer_type)) {
    ExternalProcessImporterClient::OnImportItemFinished(import_item);
    return;
  }

  if (cancelled_)
    return;

  bridge_->NotifyItemEnded(import_item);
  huhi_profile_import_->ReportImportItemFinished(import_item);
}

void HuhiExternalProcessImporterClient::OnCreditCardImportReady(
    const base::string16& name_on_card,
    const base::string16& expiration_month,
    const base::string16& expiration_year,
    const base::string16& decrypted_card_number,
    const std::string& origin) {
  if (cancelled_)
    return;

  static_cast<HuhiInProcessImporterBridge*>(
      bridge_.get())->SetCreditCard(name_on_card,
                                    expiration_month,
                                    expiration_year,
                                    decrypted_card_number,
                                    origin);
}
