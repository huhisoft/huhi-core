/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_
#define HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_

#define HUHI_VISIT_DEVICE_INFO_SPECIFICS_HUHI_FIELDS \
VISIT(huhi_fields);

#define HUHI_VISIT_PROTO_FIELDS_HUHI_SPECIFIC_FIELD                  \
VISIT_PROTO_FIELDS(const sync_pb::HuhiSpecificFields& proto) {        \
  VISIT(is_self_delete_supported);                                     \
}

#include "../../../../../components/sync/protocol/proto_visitors.h"

#endif  // HUHI_CHROMIUM_SRC_COMPONENTS_SYNC_PROTOCOL_PROTO_VISITORS_H_
