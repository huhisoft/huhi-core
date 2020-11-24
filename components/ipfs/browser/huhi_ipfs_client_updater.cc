/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/ipfs/browser/huhi_ipfs_client_updater.h"

#include "base/files/file_enumerator.h"
#include "base/files/file_path.h"
#include "base/files/file_util.h"
#include "base/logging.h"
#include "base/task/post_task.h"
#include "base/task_runner.h"
#include "base/task_runner_util.h"
#include "third_party/re2/src/re2/re2.h"

namespace ipfs {

std::string HuhiIpfsClientUpdater::g_ipfs_client_component_id_(
    kIpfsClientComponentId);
std::string HuhiIpfsClientUpdater::g_ipfs_client_component_base64_public_key_(
    kIpfsClientComponentBase64PublicKey);

HuhiIpfsClientUpdater::HuhiIpfsClientUpdater(
    HuhiComponent::Delegate* delegate)
    : HuhiComponent(delegate),
      task_runner_(base::CreateSequencedTaskRunner(
          {base::ThreadPool(), base::MayBlock()})),
      registered_(false),
      weak_ptr_factory_(this) {
}

HuhiIpfsClientUpdater::~HuhiIpfsClientUpdater() {
}

void HuhiIpfsClientUpdater::Register() {
  if (registered_)
    return;

  HuhiComponent::Register(kIpfsClientComponentName,
                           g_ipfs_client_component_id_,
                           g_ipfs_client_component_base64_public_key_);
  registered_ = true;
}

namespace {

base::FilePath InitExecutablePath(const base::FilePath& install_dir) {
  base::FilePath executable_path;
  base::FileEnumerator traversal(install_dir, false,
                                 base::FileEnumerator::FILES,
                                 FILE_PATH_LITERAL("go-ipfs_v*"));
  for (base::FilePath current = traversal.Next(); !current.empty();
       current = traversal.Next()) {
    base::FileEnumerator::FileInfo file_info = traversal.GetInfo();
    if (!RE2::FullMatch(file_info.GetName().MaybeAsASCII(),
                        "go-ipfs_v\\d+\\.\\d+\\.\\d+\\_\\w+-amd64"))
      continue;
    executable_path = current;
    break;
  }

  if (executable_path.empty()) {
    LOG(ERROR) << "Failed to locate Ipfs client executable in "
               << install_dir.value().c_str();
    return base::FilePath();
  }

#if defined(OS_POSIX)
  // Ensure that Ipfs client executable has appropriate file
  // permissions, as CRX unzipping does not preserve them.
  // See https://crbug.com/555011
  if (!base::SetPosixFilePermissions(executable_path, 0755)) {
    LOG(ERROR) << "Failed to set executable permission on "
               << executable_path.value().c_str();
    return base::FilePath();
  }
#endif  // defined(OS_POSIX)

  return executable_path;
}

}  // namespace

void HuhiIpfsClientUpdater::SetExecutablePath(const base::FilePath& path) {
  executable_path_ = path;
  for (Observer& observer : observers_)
    observer.OnExecutableReady(path);
}

base::FilePath HuhiIpfsClientUpdater::GetExecutablePath() const {
  return executable_path_;
}

void HuhiIpfsClientUpdater::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  base::PostTaskAndReplyWithResult(
      GetTaskRunner().get(), FROM_HERE,
      base::BindOnce(&InitExecutablePath, install_dir),
      base::BindOnce(&HuhiIpfsClientUpdater::SetExecutablePath,
        weak_ptr_factory_.GetWeakPtr()));
}

void HuhiIpfsClientUpdater::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void HuhiIpfsClientUpdater::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

// static
void HuhiIpfsClientUpdater::SetComponentIdAndBase64PublicKeyForTest(
    const std::string& component_id,
    const std::string& component_base64_public_key) {
  g_ipfs_client_component_id_ = component_id;
  g_ipfs_client_component_base64_public_key_ = component_base64_public_key;
}

///////////////////////////////////////////////////////////////////////////////

// The Huhi Ipfs client extension factory.
std::unique_ptr<HuhiIpfsClientUpdater> HuhiIpfsClientUpdaterFactory(
    HuhiComponent::Delegate* delegate) {
  return std::make_unique<HuhiIpfsClientUpdater>(delegate);
}

}  // namespace ipfs
