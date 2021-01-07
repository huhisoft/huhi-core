// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

#include "huhi/browser/ui/webui/settings/huhi_sync_handler.h"

#include <string>
#include <utility>
#include <vector>

#include "base/bind.h"
#include "base/strings/string_number_conversions.h"
#include "huhi/components/huhi_sync/huhi_sync_prefs.h"
#include "huhi/components/huhi_sync/crypto/crypto.h"
#include "huhi/components/huhi_sync/profile_sync_service_helper.h"
#include "huhi/components/sync/driver/huhi_sync_profile_sync_service.h"
#include "huhi/components/sync_device_info/huhi_device_info.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/device_info_sync_service_factory.h"
#include "chrome/browser/sync/profile_sync_service_factory.h"
#include "components/sync/driver/sync_user_settings.h"
#include "components/sync_device_info/device_info_sync_service.h"
#include "components/sync_device_info/device_info_tracker.h"
#include "components/sync_device_info/local_device_info_provider.h"
#include "content/public/browser/web_ui.h"
#include "ui/base/webui/web_ui_util.h"

HuhiSyncHandler::HuhiSyncHandler() : weak_ptr_factory_(this) {}

HuhiSyncHandler::~HuhiSyncHandler() {}

void HuhiSyncHandler::RegisterMessages() {
  profile_ = Profile::FromWebUI(web_ui());
  web_ui()->RegisterMessageCallback(
      "SyncGetDeviceList",
      base::BindRepeating(&HuhiSyncHandler::HandleGetDeviceList,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "SyncSetupSetSyncCode",
      base::BindRepeating(&HuhiSyncHandler::HandleSetSyncCode,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "SyncSetupGetSyncCode",
      base::BindRepeating(&HuhiSyncHandler::HandleGetSyncCode,
                          base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "SyncGetQRCode", base::BindRepeating(&HuhiSyncHandler::HandleGetQRCode,
                                           base::Unretained(this)));
  web_ui()->RegisterMessageCallback(
      "SyncSetupReset", base::BindRepeating(&HuhiSyncHandler::HandleReset,
                                            base::Unretained(this)));

  web_ui()->RegisterMessageCallback(
      "SyncDeleteDevice",
      base::BindRepeating(&HuhiSyncHandler::HandleDeleteDevice,
                          base::Unretained(this)));
}

void HuhiSyncHandler::OnJavascriptAllowed() {
  syncer::DeviceInfoTracker* tracker = GetDeviceInfoTracker();
  DCHECK(tracker);
  if (tracker)
    device_info_tracker_observer_.Add(tracker);
}

void HuhiSyncHandler::OnJavascriptDisallowed() {
  device_info_tracker_observer_.RemoveAll();
}

void HuhiSyncHandler::OnDeviceInfoChange() {
  if (IsJavascriptAllowed())
    FireWebUIListener("device-info-changed", GetSyncDeviceList());
}

void HuhiSyncHandler::HandleGetDeviceList(const base::ListValue* args) {
  AllowJavascript();
  const auto& list = args->GetList();
  CHECK_EQ(1U, list.size());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));

  ResolveJavascriptCallback(*callback_id, GetSyncDeviceList());
}

void HuhiSyncHandler::HandleGetSyncCode(const base::ListValue* args) {
  AllowJavascript();

  CHECK_EQ(1U, args->GetSize());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));

  auto* sync_service = GetSyncService();
  std::string sync_code;
  if (sync_service)
    sync_code = sync_service->GetOrCreateSyncCode();

  ResolveJavascriptCallback(*callback_id, base::Value(sync_code));
}

void HuhiSyncHandler::HandleGetQRCode(const base::ListValue* args) {
  AllowJavascript();
  CHECK_EQ(2U, args->GetSize());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));
  const base::Value* sync_code;
  CHECK(args->Get(1, &sync_code));

  std::vector<uint8_t> seed;
  if (!huhi_sync::crypto::PassphraseToBytes32(sync_code->GetString(), &seed)) {
    LOG(ERROR) << "invalid sync code when generating qr code";
    RejectJavascriptCallback(*callback_id, base::Value("invalid sync code"));
    return;
  }

  // QR code version 3 can only carry 84 bytes so we hex encode 32 bytes
  // seed then we will have 64 bytes input data
  const std::string sync_code_hex = base::HexEncode(seed.data(), seed.size());

  base::Value callback_id_disconnect(callback_id->Clone());
  base::Value callback_id_arg(callback_id->Clone());

  qr_code_service_remote_ = qrcode_generator::LaunchQRCodeGeneratorService();
  qr_code_service_remote_.set_disconnect_handler(
      base::BindOnce(&HuhiSyncHandler::OnCodeGeneratorResponse,
                     weak_ptr_factory_.GetWeakPtr(),
                     std::move(callback_id_disconnect), nullptr));
  qrcode_generator::mojom::QRCodeGeneratorService* generator =
      qr_code_service_remote_.get();

  qrcode_generator::mojom::GenerateQRCodeRequestPtr request =
      qrcode_generator::mojom::GenerateQRCodeRequest::New();
  request->data = sync_code_hex;
  request->should_render = true;
  request->render_dino = false;
  request->render_module_style =
      qrcode_generator::mojom::ModuleStyle::DEFAULT_SQUARES;
  request->render_locator_style =
      qrcode_generator::mojom::LocatorStyle::DEFAULT_SQUARE;

  generator->GenerateQRCode(
      std::move(request),
      base::BindOnce(&HuhiSyncHandler::OnCodeGeneratorResponse,
                     weak_ptr_factory_.GetWeakPtr(),
                     std::move(callback_id_arg)));
}

void HuhiSyncHandler::HandleSetSyncCode(const base::ListValue* args) {
  AllowJavascript();
  CHECK_EQ(2U, args->GetSize());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));
  const base::Value* sync_code;
  CHECK(args->Get(1, &sync_code));

  if (sync_code->GetString().empty()) {
    LOG(ERROR) << "No sync code parameter provided!";
    RejectJavascriptCallback(*callback_id, base::Value(false));
    return;
  }

  auto* sync_service = GetSyncService();
  if (!sync_service || !sync_service->SetSyncCode(sync_code->GetString())) {
    RejectJavascriptCallback(*callback_id, base::Value(false));
    return;
  }

  ResolveJavascriptCallback(*callback_id, base::Value(true));
}

void HuhiSyncHandler::HandleReset(const base::ListValue* args) {
  AllowJavascript();
  CHECK_EQ(1U, args->GetSize());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));

  auto* sync_service = GetSyncService();
  if (!sync_service) {
    ResolveJavascriptCallback(*callback_id, base::Value(true));
    return;
  }

  base::Value callback_id_arg(callback_id->Clone());
  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  huhi_sync::ResetSync(sync_service, device_info_sync_service,
                        base::BindOnce(&HuhiSyncHandler::OnResetDone,
                                       weak_ptr_factory_.GetWeakPtr(),
                                       std::move(callback_id_arg)));
}

void HuhiSyncHandler::HandleDeleteDevice(const base::ListValue* args) {
  AllowJavascript();
  CHECK_EQ(2U, args->GetSize());
  const base::Value* callback_id;
  CHECK(args->Get(0, &callback_id));
  const base::Value* device_id_value;
  CHECK(args->Get(1, &device_id_value));

  std::string device_guid = device_id_value->GetString();
  if (device_guid.empty()) {
    LOG(ERROR) << "No device id to remove!";
    RejectJavascriptCallback(*callback_id, base::Value(false));
    return;
  }

  auto* sync_service = GetSyncService();
  if (!sync_service) {
    ResolveJavascriptCallback(*callback_id, base::Value(false));
    return;
  }

  base::Value callback_id_arg(callback_id->Clone());
  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  huhi_sync::DeleteDevice(sync_service, device_info_sync_service, device_guid);
}

syncer::HuhiProfileSyncService* HuhiSyncHandler::GetSyncService() const {
  return ProfileSyncServiceFactory::IsSyncAllowed(profile_)
             ? static_cast<syncer::HuhiProfileSyncService*>(
                 ProfileSyncServiceFactory::GetForProfile(profile_))
             : nullptr;
}

syncer::DeviceInfoTracker* HuhiSyncHandler::GetDeviceInfoTracker() const {
  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  return device_info_sync_service->GetDeviceInfoTracker();
}

syncer::LocalDeviceInfoProvider* HuhiSyncHandler::GetLocalDeviceInfoProvider()
    const {
  auto* device_info_sync_service =
      DeviceInfoSyncServiceFactory::GetForProfile(profile_);
  return device_info_sync_service->GetLocalDeviceInfoProvider();
}

void HuhiSyncHandler::OnResetDone(base::Value callback_id) {
  ResolveJavascriptCallback(callback_id, base::Value(true));
}

base::Value HuhiSyncHandler::GetSyncDeviceList() {
  AllowJavascript();
  syncer::DeviceInfoTracker* tracker = GetDeviceInfoTracker();
  DCHECK(tracker);
  const syncer::DeviceInfo* local_device_info =
      GetLocalDeviceInfoProvider()->GetLocalDeviceInfo();

  base::Value device_list(base::Value::Type::LIST);

  for (const auto& device : tracker->GetAllHuhiDeviceInfo()) {
    auto device_value = base::Value::FromUniquePtrValue(device->ToValue());
    bool is_current_device =
        local_device_info ? local_device_info->guid() == device->guid() : false;
    device_value.SetBoolKey("isCurrentDevice", is_current_device);
    device_value.SetStringKey("guid", device->guid());
    device_value.SetBoolKey(
        "supportsSelfDelete",
        !is_current_device && device->is_self_delete_supported());

    device_list.Append(std::move(device_value));
  }

  return device_list;
}

void HuhiSyncHandler::OnCodeGeneratorResponse(
    base::Value callback_id,
    const qrcode_generator::mojom::GenerateQRCodeResponsePtr response) {
  if (!response || response->error_code !=
                       qrcode_generator::mojom::QRCodeGeneratorError::NONE) {
    VLOG(1) << "QR code generator failure: " << response->error_code;
    ResolveJavascriptCallback(callback_id, base::Value(false));
    return;
  }

  const std::string data_url = webui::GetBitmapDataUrl(response->bitmap);
  VLOG(1) << "QR code data url: " << data_url;

  qr_code_service_remote_.reset();
  ResolveJavascriptCallback(callback_id, base::Value(data_url));
}
