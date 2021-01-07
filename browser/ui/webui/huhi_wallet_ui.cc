/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/webui/huhi_wallet_ui.h"

#include <memory>

#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/common/webui_url_constants.h"
#include "huhi/components/huhi_wallet/resources/grit/huhi_wallet_generated_map.h"
#include "components/grit/huhi_components_resources.h"
#include "content/public/browser/render_frame_host.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/browser/web_ui_data_source.h"
#include "content/public/browser/web_ui_message_handler.h"

namespace {

class WalletDOMHandler : public content::WebUIMessageHandler {
 public:
  WalletDOMHandler();
  ~WalletDOMHandler() override;

  // WebUIMessageHandler implementation.
  void RegisterMessages() override;

 private:
  DISALLOW_COPY_AND_ASSIGN(WalletDOMHandler);
};

WalletDOMHandler::WalletDOMHandler() {}

WalletDOMHandler::~WalletDOMHandler() {}

void WalletDOMHandler::RegisterMessages() {
}

}  // namespace

HuhiWalletUI::HuhiWalletUI(content::WebUI* web_ui, const std::string& name)
    : BasicUI(web_ui,
              name,
              kHuhiWalletGenerated,
              kHuhiWalletGeneratedSize,
              IDR_HUHI_WALLET_HTML,
              /*disable_trusted_types_csp=*/true) {
  web_ui->AddMessageHandler(std::make_unique<WalletDOMHandler>());
}

HuhiWalletUI::~HuhiWalletUI() {
}
