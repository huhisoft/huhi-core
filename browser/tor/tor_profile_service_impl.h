/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_BROWSER_TOR_TOR_PROFILE_SERVICE_IMPL_H_
#define HUHI_BROWSER_TOR_TOR_PROFILE_SERVICE_IMPL_H_

#include <memory>

#include "base/memory/weak_ptr.h"
#include "base/optional.h"
#include "huhi/browser/extensions/huhi_tor_client_updater.h"
#include "huhi/browser/tor/tor_launcher_factory.h"
#include "huhi/browser/tor/tor_profile_service.h"
#include "net/proxy_resolution/proxy_info.h"

class Profile;

namespace net {
class ProxyConfigService;
class ProxyConfigServiceTor;
}

using extensions::HuhiTorClientUpdater;

namespace tor {

using NewTorCircuitCallback = base::OnceCallback<void(
    const base::Optional<net::ProxyInfo>& proxy_info)>;

class TorProfileServiceImpl : public TorProfileService,
                              public HuhiTorClientUpdater::Observer {
 public:
  explicit TorProfileServiceImpl(Profile* profile);
  ~TorProfileServiceImpl() override;

  // TorProfileService:
  void SetNewTorCircuit(content::WebContents* web_contents) override;
  std::unique_ptr<net::ProxyConfigService> CreateProxyConfigService() override;
  bool IsTorLaunched() override;
  void SetTorLaunchedForTest() override;

  void KillTor();

  // For internal observer
  void NotifyTorLauncherCrashed();
  void NotifyTorCrashed(int64_t pid);
  void NotifyTorLaunched(bool result, int64_t pid);

 private:
  void LaunchTor();

  // HuhiTorClientUpdater::Observer
  void OnExecutableReady(const base::FilePath& path) override;

  bool is_tor_launched_for_test_ = false;
  Profile* profile_;  // NOT OWNED
  TorLauncherFactory* tor_launcher_factory_;  // Singleton
  net::ProxyConfigServiceTor* proxy_config_service_;  // NOT OWNED
  base::WeakPtrFactory<TorProfileServiceImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(TorProfileServiceImpl);
};

}  // namespace tor

#endif  // HUHI_BROWSER_TOR_TOR_PROFILE_SERVICE_IMPL_H_
