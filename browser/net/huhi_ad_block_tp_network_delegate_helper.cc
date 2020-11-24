/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_ad_block_tp_network_delegate_helper.h"

#include <memory>
#include <string>

#include "base/base64url.h"
#include "base/strings/string_util.h"
#include "huhi/browser/huhi_browser_process_impl.h"
#include "huhi/browser/net/url_context.h"
#include "huhi/common/network_constants.h"
#include "huhi/components/huhi_shields/browser/ad_block_custom_filters_service.h"
#include "huhi/components/huhi_shields/browser/ad_block_regional_service_manager.h"
#include "huhi/components/huhi_shields/browser/ad_block_service.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_util.h"
#include "huhi/components/huhi_shields/browser/huhi_shields_web_contents_observer.h"
#include "huhi/components/huhi_shields/common/huhi_shield_constants.h"
#include "huhi/grit/huhi_generated_resources.h"
#include "content/public/browser/browser_thread.h"
#include "extensions/common/url_pattern.h"
#include "ui/base/resource/resource_bundle.h"

namespace huhi {

void ShouldBlockAdOnTaskRunner(std::shared_ptr<HuhiRequestInfo> ctx) {
  bool did_match_exception = false;
  std::string tab_host = ctx->tab_origin.host();
  if (!g_huhi_browser_process->ad_block_service()->ShouldStartRequest(
          ctx->request_url, ctx->resource_type, tab_host,
          &did_match_exception, &ctx->cancel_request_explicitly,
          &ctx->mock_data_url)) {
    ctx->blocked_by = kAdBlocked;
  } else if (!did_match_exception &&
             !g_huhi_browser_process->ad_block_regional_service_manager()
                  ->ShouldStartRequest(ctx->request_url, ctx->resource_type,
                                       tab_host, &did_match_exception,
                                       &ctx->cancel_request_explicitly,
                                       &ctx->mock_data_url)) {
    ctx->blocked_by = kAdBlocked;
  } else if (!did_match_exception &&
             !g_huhi_browser_process->ad_block_custom_filters_service()
                  ->ShouldStartRequest(ctx->request_url, ctx->resource_type,
                                       tab_host, &did_match_exception,
                                       &ctx->cancel_request_explicitly,
                                       &ctx->mock_data_url)) {
    ctx->blocked_by = kAdBlocked;
  }
}

void OnShouldBlockAdResult(const ResponseCallback& next_callback,
                           std::shared_ptr<HuhiRequestInfo> ctx) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (ctx->blocked_by == kAdBlocked) {
    huhi_shields::DispatchBlockedEvent(
        ctx->request_url,
        ctx->render_frame_id, ctx->render_process_id, ctx->frame_tree_node_id,
        huhi_shields::kAds);
  }
  next_callback.Run();
}

void OnBeforeURLRequestAdBlockTP(
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  // If the following info isn't available, then proper content settings can't
  // be looked up, so do nothing.
  if (ctx->tab_origin.is_empty() || !ctx->tab_origin.has_host() ||
      ctx->request_url.is_empty()) {
    return;
  }
  DCHECK_NE(ctx->request_identifier, 0UL);

  g_huhi_browser_process->ad_block_service()->GetTaskRunner()
      ->PostTaskAndReply(FROM_HERE,
                         base::BindOnce(&ShouldBlockAdOnTaskRunner, ctx),
                         base::BindOnce(&OnShouldBlockAdResult, next_callback,
                                        ctx));
}

int OnBeforeURLRequest_AdBlockTPPreWork(
    const ResponseCallback& next_callback,
    std::shared_ptr<HuhiRequestInfo> ctx) {

  if (ctx->request_url.is_empty()) {
    return net::OK;
  }

  // If the following info isn't available, then proper content settings can't
  // be looked up, so do nothing.
  if (ctx->tab_origin.is_empty() || !ctx->allow_huhi_shields ||
      ctx->allow_ads ||
      ctx->resource_type == HuhiRequestInfo::kInvalidResourceType) {
    return net::OK;
  }

  OnBeforeURLRequestAdBlockTP(next_callback, ctx);

  return net::ERR_IO_PENDING;
}

}  // namespace huhi
