/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_prochlo/huhi_prochlo_crypto.h"

#include "third_party/boringssl/src/include/openssl/pem.h"

namespace prochlo {

HuhiProchloCrypto::HuhiProchloCrypto() = default;

bool HuhiProchloCrypto::load_analyzer_key_from_bytes(
    const std::vector<char>& bytes) {
  public_analyzer_key_ = load_public_key_from_bytes(bytes);
  return public_analyzer_key_ != nullptr;
}

bool HuhiProchloCrypto::load_shuffler_key_from_bytes(
    const std::vector<char>& bytes) {
  public_shuffler_key_ = load_public_key_from_bytes(bytes);
  return public_shuffler_key_ != nullptr;
}

EVP_PKEY* HuhiProchloCrypto::load_public_key_from_bytes(
    const std::vector<char>& bytes) {
  bssl::UniquePtr<BIO> bio(
      BIO_new_mem_buf(bytes.data(), static_cast<int>(bytes.size())));
  if (!bio) {
    return nullptr;
  }
  return PEM_read_bio_PUBKEY(bio.get(), nullptr, nullptr, nullptr);
}

}  // namespace prochlo
