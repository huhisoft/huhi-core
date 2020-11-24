/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_COMPONENT_H_
#define HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_COMPONENT_H_

#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"

namespace huhi_component_updater {

class HuhiComponent {
 public:
  using ReadyCallback = base::RepeatingCallback<void(const base::FilePath&,
                                                const std::string& manifest)>;
  class Delegate {
   public:
    virtual ~Delegate() = default;
    virtual void Register(const std::string& component_name,
                          const std::string& component_base64_public_key,
                          base::OnceClosure registered_callback,
                          ReadyCallback ready_callback) = 0;
    virtual bool Unregister(const std::string& component_id) = 0;
    virtual void OnDemandUpdate(const std::string& component_id) = 0;
    virtual scoped_refptr<base::SequencedTaskRunner> GetTaskRunner() = 0;
  };

  explicit HuhiComponent(Delegate* delegate);
  virtual ~HuhiComponent();
  void Register(const std::string& component_name,
                const std::string& component_id,
                const std::string& component_base64_public_key);
  bool Unregister();
  scoped_refptr<base::SequencedTaskRunner> GetTaskRunner();

 protected:
  virtual void OnComponentReady(const std::string& component_id,
                                const base::FilePath& install_dir,
                                const std::string& manifest);

 private:
  static void OnComponentRegistered(Delegate* delegate,
                                    const std::string& component_id);
  void OnComponentReadyInternal(const std::string& component_id,
                                const base::FilePath& install_dir,
                                const std::string& manifest);

  std::string component_name_;
  std::string component_id_;
  std::string component_base64_public_key_;
  Delegate* delegate_;  // NOT OWNED
  base::WeakPtrFactory<HuhiComponent> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiComponent);
};

}  // namespace huhi_component_updater

#endif  // HUHI_COMPONENTS_HUHI_COMPONENT_UPDATER_BROWSER_HUHI_COMPONENT_H_