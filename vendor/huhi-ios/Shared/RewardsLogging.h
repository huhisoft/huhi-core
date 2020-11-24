/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef RewardsLogging_h
#define RewardsLogging_h

#include <ostream>
#include <sstream>
#include <string>

#import <Foundation/Foundation.h>

@class BATHuhiRewards;

namespace rewards {

void set_rewards_client_for_logging(BATHuhiRewards *rewards);

void LogMessage(const char* file,
         int line,
         int verbose_level,
         NSString *message);

void Log(const char* file,
         int line,
         int verbose_level,
         NSString *format,
         ...) NS_FORMAT_FUNCTION(4,5);

#define BLOG(verbose_level, format, ...) rewards::Log(__FILE__, __LINE__, \
  verbose_level, format, ##__VA_ARGS__);

} // namespace rewards

#endif // RewardsLogging_h
