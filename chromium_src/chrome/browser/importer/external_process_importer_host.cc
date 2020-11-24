/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/importer/huhi_external_process_importer_client.h"
#include "huhi/browser/importer/huhi_in_process_importer_bridge.h"

#define ExternalProcessImporterClient HuhiExternalProcessImporterClient
#define InProcessImporterBridge HuhiInProcessImporterBridge
#include "../../../../../chrome/browser/importer/external_process_importer_host.cc"
#undef ExternalProcessImporterClient
#undef InProcessImporterBridge
