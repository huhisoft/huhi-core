/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_EXTENSIONS_HUHI_TOR_CLIENT_UPDATER_H_
#define HUHI_BROWSER_EXTENSIONS_HUHI_TOR_CLIENT_UPDATER_H_

#include <memory>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/sequenced_task_runner.h"
#include "huhi/components/huhi_component_updater/browser/huhi_component.h"

class HuhiProfileManagerTest;
class HuhiProfileManagerExtensionTest;
class HuhiTorClientUpdaterTest;
class SearchEngineProviderServiceTest;

using huhi_component_updater::HuhiComponent;

// TODO(bridiver) - this doesn't belong under extensions
namespace extensions {

#if defined(OS_WIN)
extern const char kTorClientComponentName[];
extern const char kTorClientComponentId[];
#elif defined(OS_MAC)
extern const char kTorClientComponentName[];
extern const char kTorClientComponentId[];
extern const char kTorClientComponentBase64PublicKey[];
#elif defined(OS_LINUX)
extern const char kTorClientComponentName[];
extern const char kTorClientComponentId[];
extern const char kTorClientComponentBase64PublicKey[];
#endif

class HuhiTorClientUpdater : public HuhiComponent {
 public:
  class Observer : public base::CheckedObserver {
   public:
    virtual void OnExecutableReady(const base::FilePath& path) = 0;

   protected:
    ~Observer() override = default;
  };

  explicit HuhiTorClientUpdater(HuhiComponent::Delegate* delegate);
  ~HuhiTorClientUpdater() override;

  void Register();
  void Unregister();
  void Cleanup();
  base::FilePath GetExecutablePath() const;
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() {
    return task_runner_;
  }

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 protected:
  void OnComponentReady(const std::string& component_id,
      const base::FilePath& install_dir,
      const std::string& manifest) override;

 private:
  friend class ::HuhiProfileManagerTest;
  friend class ::HuhiProfileManagerExtensionTest;
  friend class ::HuhiTorClientUpdaterTest;
  friend class ::SearchEngineProviderServiceTest;

  static std::string g_tor_client_component_name_;
  static std::string g_tor_client_component_id_;
  static std::string g_tor_client_component_base64_public_key_;
  static void SetComponentIdAndBase64PublicKeyForTest(
      const std::string& component_id,
      const std::string& component_base64_public_key);
  void SetExecutablePath(const base::FilePath& path);

  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  bool registered_;
  base::FilePath executable_path_;
  base::ObserverList<Observer> observers_;

  base::WeakPtrFactory<HuhiTorClientUpdater> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiTorClientUpdater);
};

// Creates the HuhiTorClientUpdater
std::unique_ptr<HuhiTorClientUpdater>
HuhiTorClientUpdaterFactory(HuhiComponent::Delegate* delegate);

}  // namespace extensions

#endif  // HUHI_BROWSER_EXTENSIONS_HUHI_TOR_CLIENT_UPDATER_H_
