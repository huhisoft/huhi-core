// NOLINT(build/header_guard)
/* Copyright 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

// Multiply-included file, no traditional include guard.

#include <string>
#include <vector>

#include "ipc/ipc_message_macros.h"

// The message starter should be declared in ipc/ipc_message_start.h. Since
// we don't want to patch Chromium, we just pretend to be Content Shell.

#define IPC_MESSAGE_START FrameMsgStart

// Tell RenderFrame(s) to temporary allow scripts from a list of origins once.
IPC_MESSAGE_ROUTED1(
    HuhiFrameMsg_AllowScriptsOnce,
    std::vector<std::string> /* origins to allow scripts once */)