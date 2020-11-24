/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_HUHI_DOM_WINDOW_STORAGE_H_
#define HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_HUHI_DOM_WINDOW_STORAGE_H_

namespace blink {

class ExceptionState;
class LocalDOMWindow;
class StorageArea;

class HuhiDOMWindowStorage {
 public:
  static StorageArea* sessionStorage(LocalDOMWindow&, ExceptionState&);
  static StorageArea* localStorage(LocalDOMWindow&, ExceptionState&);

 private:
  HuhiDOMWindowStorage();
  ~HuhiDOMWindowStorage();
};

}  // namespace blink

#endif  // HUHI_CHROMIUM_SRC_THIRD_PARTY_BLINK_RENDERER_MODULES_STORAGE_HUHI_DOM_WINDOW_STORAGE_H_
