/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef HUHI_COMPONENTS_SERVICES_BAT_LEDGER_BAT_LEDGER_APP_H_
#define HUHI_COMPONENTS_SERVICES_BAT_LEDGER_BAT_LEDGER_APP_H_

#include <memory>
#include <string>

#include "huhi/components/services/bat_ledger/public/interfaces/bat_ledger.mojom.h"
#include "mojo/public/cpp/bindings/binder_map.h"
#include "mojo/public/cpp/bindings/pending_receiver.h"
#include "mojo/public/cpp/bindings/unique_receiver_set.h"
#include "services/service_manager/public/cpp/service.h"
#include "services/service_manager/public/cpp/service_keepalive.h"
#include "services/service_manager/public/cpp/service_receiver.h"

namespace bat_ledger {

class BatLedgerApp : public service_manager::Service {
 public:
  explicit BatLedgerApp(
      mojo::PendingReceiver<service_manager::mojom::Service> receiver);
  ~BatLedgerApp() override;

  BatLedgerApp(const BatLedgerApp&) = delete;
  BatLedgerApp& operator=(const BatLedgerApp&) = delete;

 private:
  // |Service| override:
  void OnStart() override;
  void OnConnect(const service_manager::ConnectSourceInfo& source_info,
                 const std::string& interface_name,
                 mojo::ScopedMessagePipeHandle receiver_pipe) override;

  service_manager::ServiceReceiver service_receiver_;
  service_manager::ServiceKeepalive service_keepalive_;
  mojo::BinderMap binders_;
  mojo::UniqueReceiverSet<mojom::BatLedgerService> receivers_;

  void BindBatLedgerServiceReceiver(
      service_manager::ServiceKeepalive* keepalive,
      mojo::PendingReceiver<mojom::BatLedgerService> receiver);
};

}  // namespace bat_ledger

#endif  // HUHI_COMPONENTS_SERVICES_BAT_LEDGER_BAT_LEDGER_APP_H_
