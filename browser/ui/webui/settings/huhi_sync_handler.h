// Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Huhi Software
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_SYNC_HANDLER_H_
#define HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_SYNC_HANDLER_H_

#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/values.h"
#include "chrome/browser/ui/webui/settings/settings_page_ui_handler.h"
#include "chrome/services/qrcode_generator/public/cpp/qrcode_generator_service.h"
#include "components/sync_device_info/device_info_tracker.h"

namespace syncer {
class DeviceInfoTracker;
class LocalDeviceInfoProvider;
class HuhiProfileSyncService;
}  // namespace syncer
class Profile;

class HuhiSyncHandler : public settings::SettingsPageUIHandler,
                         public syncer::DeviceInfoTracker::Observer {
 public:
  HuhiSyncHandler();
  ~HuhiSyncHandler() override;

  // syncer::DeviceInfoTracker::Observer
  void OnDeviceInfoChange() override;

 private:
  // SettingsPageUIHandler overrides:
  void RegisterMessages() override;
  void OnJavascriptAllowed() override;
  void OnJavascriptDisallowed() override;

  // Custom message handlers:
  void HandleGetDeviceList(const base::ListValue* args);
  void HandleGetSyncCode(const base::ListValue* args);
  void HandleSetSyncCode(const base::ListValue* args);
  void HandleGetQRCode(const base::ListValue* args);
  void HandleReset(const base::ListValue* args);

  void OnResetDone(base::Value callback_id);

  base::Value GetSyncDeviceList();
  syncer::HuhiProfileSyncService* GetSyncService() const;
  syncer::DeviceInfoTracker* GetDeviceInfoTracker() const;
  syncer::LocalDeviceInfoProvider* GetLocalDeviceInfoProvider() const;

  // Callback for the request to the OOP service to generate a new image.
  void OnCodeGeneratorResponse(
      base::Value callback_id,
      const qrcode_generator::mojom::GenerateQRCodeResponsePtr response);

  // Remote to service instance to generate QR code images.
  mojo::Remote<qrcode_generator::mojom::QRCodeGeneratorService>
      qr_code_service_remote_;

  Profile* profile_ = nullptr;

  // Manages observer lifetimes.
  ScopedObserver<syncer::DeviceInfoTracker, syncer::DeviceInfoTracker::Observer>
      device_info_tracker_observer_{this};

  base::WeakPtrFactory<HuhiSyncHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HuhiSyncHandler);
};

#endif  // HUHI_BROWSER_UI_WEBUI_SETTINGS_HUHI_SYNC_HANDLER_H_
