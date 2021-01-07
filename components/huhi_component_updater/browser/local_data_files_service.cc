/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/components/huhi_component_updater/browser/local_data_files_service.h"

#include "huhi/components/huhi_component_updater/browser/local_data_files_observer.h"

using huhi_component_updater::HuhiComponent;

namespace huhi_component_updater {

std::string LocalDataFilesService::g_local_data_files_component_id_(
    kLocalDataFilesComponentId);
std::string LocalDataFilesService::
g_local_data_files_component_base64_public_key_(
    kLocalDataFilesComponentBase64PublicKey);

LocalDataFilesService::LocalDataFilesService(HuhiComponent::Delegate* delegate)
  : HuhiComponent(delegate),
    initialized_(false) {}

LocalDataFilesService::~LocalDataFilesService() {
  for (auto& observer : observers_)
    observer.OnLocalDataFilesServiceDestroyed();
}

bool LocalDataFilesService::Start() {
  if (initialized_)
    return true;
  Register(kLocalDataFilesComponentName,
           g_local_data_files_component_id_,
           g_local_data_files_component_base64_public_key_);
  initialized_ = true;
  return true;
}

void LocalDataFilesService::OnComponentReady(
    const std::string& component_id,
    const base::FilePath& install_dir,
    const std::string& manifest) {
  for (auto& observer : observers_)
    observer.OnComponentReady(component_id, install_dir, manifest);
}

void LocalDataFilesService::AddObserver(LocalDataFilesObserver* observer) {
  observers_.AddObserver(observer);
}

void LocalDataFilesService::RemoveObserver(LocalDataFilesObserver* observer) {
  observers_.RemoveObserver(observer);
}

// static
void LocalDataFilesService::SetComponentIdAndBase64PublicKeyForTest(
    const std::string& component_id,
    const std::string& component_base64_public_key) {
  g_local_data_files_component_id_ = component_id;
  g_local_data_files_component_base64_public_key_ = component_base64_public_key;
}

///////////////////////////////////////////////////////////////////////////////

std::unique_ptr<LocalDataFilesService>
LocalDataFilesServiceFactory(HuhiComponent::Delegate* delegate) {
  return std::make_unique<LocalDataFilesService>(delegate);
}

}  // namespace huhi_component_updater
