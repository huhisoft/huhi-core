/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include <map>

#include "base/files/file_path.h"
#include "components/crash/core/app/crashpad.h"

namespace crashpad {

namespace {
const char huhi_crash_url[] = "https://cr.hnq.vn";
}

class HuhiCrashpadClient {
 public:
#if defined(OS_ANDROID)

  bool StartJavaHandlerAtCrash(
      const std::string& class_name,
      const std::vector<std::string>* env,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments);

  static bool StartJavaHandlerForClient(
      const std::string& class_name,
      const std::vector<std::string>* env,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments,
      int socket);

  bool StartHandlerWithLinkerAtCrash(
      const std::string& handler_trampoline,
      const std::string& handler_library,
      bool is_64_bit,
      const std::vector<std::string>* env,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments);

  void SetUnhandledSignals(const std::set<int>& unhandled_signals);

  static bool StartHandlerWithLinkerForClient(
      const std::string& handler_trampoline,
      const std::string& handler_library,
      bool is_64_bit,
      const std::vector<std::string>* env,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments,
      int socket);

#endif  // defined(OS_ANDROID)

  bool StartHandlerAtCrash(
      const base::FilePath& handler,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments);
  static bool StartHandlerForClient(
      const base::FilePath& handler,
      const base::FilePath& database,
      const base::FilePath& metrics_dir,
      const std::string& url,
      const std::map<std::string, std::string>& annotations,
      const std::vector<std::string>& arguments,
      int socket);
};

}  // namespace crashpad

namespace crash_reporter {

crashpad::HuhiCrashpadClient& GetHuhiCrashpadClient() {
  static crashpad::HuhiCrashpadClient* const client =
      new crashpad::HuhiCrashpadClient();
  return *client;
}

}  // namespace crash_reporter

#define COMPONENTS_CRASH_CONTENT_APP_CRASHPAD_H_
#define GetCrashpadClient GetHuhiCrashpadClient
#include "../../../../../../components/crash/core/app/crashpad_android.cc"
#undef GetCrashpadClient

namespace crash_reporter {
crashpad::CrashpadClient& GetCrashpadClient();
}

namespace crashpad {

#if defined(OS_ANDROID)

bool HuhiCrashpadClient::StartJavaHandlerAtCrash(
    const std::string& class_name,
    const std::vector<std::string>* env,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments) {
  return crash_reporter::GetCrashpadClient().StartJavaHandlerAtCrash(
      class_name, env, database, metrics_dir,
      huhi_crash_url, annotations, arguments);
}

// static
bool HuhiCrashpadClient::StartJavaHandlerForClient(
    const std::string& class_name,
    const std::vector<std::string>* env,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments,
    int socket) {
  return CrashpadClient::StartJavaHandlerForClient(
      class_name, env, database, metrics_dir, huhi_crash_url,
      annotations, arguments, socket);
}

bool HuhiCrashpadClient::StartHandlerWithLinkerAtCrash(
    const std::string& handler_trampoline,
    const std::string& handler_library,
    bool is_64_bit,
    const std::vector<std::string>* env,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments) {
  return crash_reporter::GetCrashpadClient().StartHandlerWithLinkerAtCrash(
      handler_trampoline, handler_library, is_64_bit, env, database,
      metrics_dir, huhi_crash_url, annotations, arguments);
}

void HuhiCrashpadClient::SetUnhandledSignals(
    const std::set<int>& unhandled_signals) {
  return crash_reporter::GetCrashpadClient().SetUnhandledSignals(
      unhandled_signals);
}

// static
bool HuhiCrashpadClient::StartHandlerWithLinkerForClient(
    const std::string& handler_trampoline,
    const std::string& handler_library,
    bool is_64_bit,
    const std::vector<std::string>* env,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments,
    int socket) {
  return CrashpadClient::StartHandlerWithLinkerForClient(
      handler_trampoline, handler_library, is_64_bit, env, database,
      metrics_dir, huhi_crash_url, annotations, arguments, socket);
}

#endif  // defined(OS_ANDROID)

bool HuhiCrashpadClient::StartHandlerAtCrash(
    const base::FilePath& handler,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments) {
  return crash_reporter::GetCrashpadClient().StartHandlerAtCrash(
      handler, database, metrics_dir,
      huhi_crash_url, annotations, arguments);
}

// static
bool HuhiCrashpadClient::StartHandlerForClient(
    const base::FilePath& handler,
    const base::FilePath& database,
    const base::FilePath& metrics_dir,
    const std::string& url,
    const std::map<std::string, std::string>& annotations,
    const std::vector<std::string>& arguments,
    int socket) {
  return crash_reporter::GetCrashpadClient().StartHandlerForClient(
    handler, database, metrics_dir, huhi_crash_url,
    annotations, arguments, socket);
}

}  // namespace crashpad
