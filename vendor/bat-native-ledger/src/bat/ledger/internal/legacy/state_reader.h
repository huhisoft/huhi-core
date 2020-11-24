/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHILEDGER_STATE_READER_H_
#define HUHILEDGER_STATE_READER_H_

#include <string>

#include "base/values.h"

namespace ledger {
namespace state {

template <class T>
class Reader {
 public:
  virtual bool FromJson(
      const std::string& json,
      T*) const = 0;

  virtual bool FromDict(
      const base::DictionaryValue* dictionary,
      T*) const = 0;
};

}  // namespace state
}  // namespace ledger

#endif  // HUHILEDGER_STATE_READER_H_
