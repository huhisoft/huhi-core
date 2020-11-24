/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <string>

#include "base/values.h"
#include "base/json/json_reader.h"
#include "extensions/common/constants.h"

namespace huhi {

bool HuhiRewriteManifest(const std::string& extension_id,
    base::DictionaryValue* manifest) {
  if (extension_id == ipfs_companion_extension_id ||
      extension_id == ipfs_companion_beta_extension_id) {
    // Set appropriate sockets permissions for IPFS Companion
    // extensions
    std::string json = R"(
      {
        "udp": {
          "send": "*",
          "bind": "*"
        },
        "tcp": {
          "connect": "*"
        },
        "tcpServer": {
          "listen": "*:*"
        }
      }
    )";

    base::Value sockets = base::JSONReader::Read(json).value();
    manifest->SetKey("sockets", std::move(sockets));
    return true;
  }
  return false;
}

}  // namespace huhi

#define HUHI_SANDBOXEDUNPACKER_REWRITEMANIFESTFILE \
  base::DictionaryValue* dict_manifest;             \
  final_manifest.GetAsDictionary(&dict_manifest);   \
  huhi::HuhiRewriteManifest(extension_id_, dict_manifest);

#include "../../../../extensions/browser/sandboxed_unpacker.cc"
#undef HUHI_SANDBOXEDUNPACKER_REWRITEMANIFESTFILE
