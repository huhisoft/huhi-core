/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_AUTH_MANAGER_H_
#define HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_AUTH_MANAGER_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "components/sync/driver/sync_auth_manager.h"

namespace syncer {

class HuhiSyncAuthManager : public SyncAuthManager {
 public:
  HuhiSyncAuthManager(signin::IdentityManager* identity_manager,
                       const AccountStateChangedCallback& account_state_changed,
                       const CredentialsChangedCallback& credentials_changed);
  ~HuhiSyncAuthManager() override;

  void DeriveSigningKeys(const std::string& seed);
  void ResetKeys();

  void RequestAccessToken() override;

  // signin::IdentityManager::Observer implementation.
  void OnPrimaryAccountSet(
      const CoreAccountInfo& primary_account_info) override {}
  void OnPrimaryAccountCleared(
      const CoreAccountInfo& previous_primary_account_info) override {}
  void OnRefreshTokenUpdatedForAccount(
      const CoreAccountInfo& account_info) override {}
  void OnRefreshTokenRemovedForAccount(
      const CoreAccountId& account_id) override {}
  void OnRefreshTokensLoaded() override {}
  void OnUnconsentedPrimaryAccountChanged(
      const CoreAccountInfo& unconsented_primary_account_info) override {}

 private:
  SyncAccountInfo DetermineAccountToUse() const override;
  std::string GenerateAccessToken(const std::string& timestamp);
  void OnNetworkTimeFetched(const base::Time& time);

  std::vector<uint8_t> public_key_;
  std::vector<uint8_t> private_key_;

  base::WeakPtrFactory<HuhiSyncAuthManager> weak_ptr_factory_{this};

  DISALLOW_COPY_AND_ASSIGN(HuhiSyncAuthManager);
};

}  // namespace syncer

#endif  // HUHI_COMPONENTS_SYNC_DRIVER_HUHI_SYNC_AUTH_MANAGER_H_
