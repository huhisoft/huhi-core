/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_PROCHLO_HUHI_PROCHLO_CRYPTO_H_
#define HUHI_COMPONENTS_HUHI_PROCHLO_HUHI_PROCHLO_CRYPTO_H_

#include <vector>

#include "base/macros.h"
#include "huhi/components/huhi_prochlo/prochlo_crypto.h"

namespace prochlo {

class HuhiProchloCrypto : public Crypto {
 public:
  HuhiProchloCrypto();

  // Load the public key for the Analyzer from bytes.
  bool load_analyzer_key_from_bytes(const std::vector<char>& bytes);

  // Load the public key for the Analyzer from bytes.
  bool load_shuffler_key_from_bytes(const std::vector<char>& bytes);

 private:
  // Load a public key returning the structure.
  EVP_PKEY* load_public_key_from_bytes(const std::vector<char>& bytes);

  DISALLOW_COPY_AND_ASSIGN(HuhiProchloCrypto);
};

}  // namespace prochlo

#endif  // HUHI_COMPONENTS_HUHI_PROCHLO_HUHI_PROCHLO_CRYPTO_H_
