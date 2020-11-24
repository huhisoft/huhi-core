/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_NET_BASE_HOST_PORT_PAIR_H_
#define HUHI_CHROMIUM_SRC_NET_BASE_HOST_PORT_PAIR_H_

#include <string>

// Nudges HostPortPair past Chromium's style
// threshold for in-line constructors and destructors.
#define HUHI_HOST_PORT_PAIR_H_ \
  HostPortPair(const std::string& username, const std::string& password, \
               const std::string& in_host, uint16_t in_port); \
  ~HostPortPair(); \
  HostPortPair(const HostPortPair&); \
  const std::string& username() const; \
  const std::string& password() const; \
  void set_username(const std::string& username); \
  void set_password(const std::string& password); \
  bool operator<(const HostPortPair& other) const; \
  bool Equals(const HostPortPair& other) const; \
 private: \
  std::string username_; \
  std::string password_;

#include "../../../../net/base/host_port_pair.h"

#undef HUHI_HOST_PORT_PAIR_H_

#endif  // HUHI_CHROMIUM_SRC_NET_BASE_HOST_PORT_PAIR_H_
