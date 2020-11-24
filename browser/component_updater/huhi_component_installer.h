/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_INSTALLER_H_
#define HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_INSTALLER_H_

#include <stdint.h>

#include <memory>
#include <string>
#include <vector>

#include "base/bind.h"
#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"
#include "components/component_updater/component_installer.h"
#include "components/update_client/update_client.h"

using huhi_component_updater::HuhiComponent;

namespace huhi {

class HuhiComponentInstallerPolicy :
    public component_updater::ComponentInstallerPolicy {
 public:
  explicit HuhiComponentInstallerPolicy(const std::string& name,
      const std::string& base64_public_key,
      HuhiComponent::ReadyCallback ready_callback);

  ~HuhiComponentInstallerPolicy() override;

 private:
  // The following methods override ComponentInstallerPolicy
  bool VerifyInstallation(const base::DictionaryValue& manifest,
      const base::FilePath& install_dir) const override;
  bool SupportsGroupPolicyEnabledComponentUpdates() const override;
  bool RequiresNetworkEncryption() const override;
  update_client::CrxInstaller::Result OnCustomInstall(
      const base::DictionaryValue& manifest,
      const base::FilePath& install_dir) override;
  void OnCustomUninstall() override;
  void ComponentReady(
      const base::Version& version,
      const base::FilePath& install_dir,
      std::unique_ptr<base::DictionaryValue> manifest) override;
  base::FilePath GetRelativeInstallDir() const override;
  void GetHash(std::vector<uint8_t>* hash) const override;
  std::string GetName() const override;
  std::vector<std::string> GetMimeTypes() const override;
  update_client::InstallerAttributes GetInstallerAttributes() const override;

  std::string name_;
  std::string base64_public_key_;
  std::string public_key_;
  HuhiComponent::ReadyCallback ready_callback_;

  DISALLOW_COPY_AND_ASSIGN(HuhiComponentInstallerPolicy);
};

void RegisterComponent(component_updater::ComponentUpdateService* cus,
    const std::string& name,
    const std::string& base64_public_key,
    base::OnceClosure registered_callback,
    HuhiComponent::ReadyCallback ready_callback);

}  // namespace huhi

#endif  // HUHI_BROWSER_COMPONENT_UPDATER_HUHI_COMPONENT_INSTALLER_H_
