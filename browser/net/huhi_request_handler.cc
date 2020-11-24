/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/net/huhi_request_handler.h"

#include <algorithm>
#include <utility>

#include "base/metrics/histogram_macros.h"
#include "base/task/post_task.h"
#include "huhi/browser/net/huhi_ad_block_tp_network_delegate_helper.h"
#include "huhi/browser/net/huhi_common_static_redirect_network_delegate_helper.h"
#include "huhi/browser/net/huhi_httpse_network_delegate_helper.h"
#include "huhi/browser/net/huhi_site_hacks_network_delegate_helper.h"
#include "huhi/browser/net/huhi_stp_util.h"
#include "huhi/browser/translate/buildflags/buildflags.h"
#include "huhi/common/pref_names.h"
#include "huhi/components/huhi_referrals/buildflags/buildflags.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"
#include "chrome/browser/browser_process.h"
#include "components/prefs/pref_change_registrar.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_task_traits.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/common/url_constants.h"
#include "extensions/common/constants.h"
#include "net/base/net_errors.h"

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
#include "huhi/browser/net/huhi_referrals_network_delegate_helper.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/components/huhi_rewards/browser/net/network_delegate_helper.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
#include "huhi/browser/net/huhi_torrent_redirect_network_delegate_helper.h"
#endif

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
#include "huhi/browser/net/huhi_translate_redirect_network_delegate_helper.h"
#endif

static bool IsInternalScheme(std::shared_ptr<huhi::HuhiRequestInfo> ctx) {
  DCHECK(ctx);
  return ctx->request_url.SchemeIs(extensions::kExtensionScheme) ||
         ctx->request_url.SchemeIs(content::kChromeUIScheme);
}

HuhiRequestHandler::HuhiRequestHandler() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  SetupCallbacks();
  // Initialize the preference change registrar.
  InitPrefChangeRegistrar();
}

HuhiRequestHandler::~HuhiRequestHandler() = default;

void HuhiRequestHandler::SetupCallbacks() {
  huhi::OnBeforeURLRequestCallback callback =
      base::Bind(huhi::OnBeforeURLRequest_SiteHacksWork);
  before_url_request_callbacks_.push_back(callback);

  callback = base::Bind(huhi::OnBeforeURLRequest_AdBlockTPPreWork);
  before_url_request_callbacks_.push_back(callback);

  callback = base::Bind(huhi::OnBeforeURLRequest_HttpsePreFileWork);
  before_url_request_callbacks_.push_back(callback);

  callback = base::Bind(huhi::OnBeforeURLRequest_CommonStaticRedirectWork);
  before_url_request_callbacks_.push_back(callback);

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
  callback = base::Bind(huhi_rewards::OnBeforeURLRequest);
  before_url_request_callbacks_.push_back(callback);
#endif

#if BUILDFLAG(ENABLE_HUHI_TRANSLATE_GO)
  callback =
      base::BindRepeating(huhi::OnBeforeURLRequest_TranslateRedirectWork);
  before_url_request_callbacks_.push_back(callback);
#endif

  huhi::OnBeforeStartTransactionCallback start_transaction_callback =
      base::Bind(huhi::OnBeforeStartTransaction_SiteHacksWork);
  before_start_transaction_callbacks_.push_back(start_transaction_callback);

#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  start_transaction_callback =
      base::Bind(huhi::OnBeforeStartTransaction_ReferralsWork);
  before_start_transaction_callbacks_.push_back(start_transaction_callback);
#endif

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
  huhi::OnHeadersReceivedCallback headers_received_callback =
      base::Bind(webtorrent::OnHeadersReceived_TorrentRedirectWork);
  headers_received_callbacks_.push_back(headers_received_callback);
#endif
}

void HuhiRequestHandler::InitPrefChangeRegistrar() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
#if BUILDFLAG(ENABLE_HUHI_REFERRALS)
  PrefService* prefs = g_browser_process->local_state();
  pref_change_registrar_.reset(new PrefChangeRegistrar());
  pref_change_registrar_->Init(prefs);
  pref_change_registrar_->Add(
      kReferralHeaders,
      base::Bind(&HuhiRequestHandler::OnReferralHeadersChanged,
                 base::Unretained(this)));
  // Retrieve current referral headers, if any.
  OnReferralHeadersChanged();
#endif
}

void HuhiRequestHandler::OnReferralHeadersChanged() {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);
  if (const base::ListValue* referral_headers =
          g_browser_process->local_state()->GetList(kReferralHeaders)) {
    referral_headers_list_.reset(referral_headers->DeepCopy());
  }
}

bool HuhiRequestHandler::IsRequestIdentifierValid(
    uint64_t request_identifier) {
  return base::Contains(callbacks_, request_identifier);
}

int HuhiRequestHandler::OnBeforeURLRequest(
    std::shared_ptr<huhi::HuhiRequestInfo> ctx,
    net::CompletionOnceCallback callback,
    GURL* new_url) {
  if (before_url_request_callbacks_.empty() || IsInternalScheme(ctx)) {
    return net::OK;
  }
  SCOPED_UMA_HISTOGRAM_TIMER("Huhi.OnBeforeURLRequest_Handler");
  ctx->new_url = new_url;
  ctx->event_type = huhi::kOnBeforeRequest;
  callbacks_[ctx->request_identifier] = std::move(callback);
  RunNextCallback(ctx);
  return net::ERR_IO_PENDING;
}

int HuhiRequestHandler::OnBeforeStartTransaction(
    std::shared_ptr<huhi::HuhiRequestInfo> ctx,
    net::CompletionOnceCallback callback,
    net::HttpRequestHeaders* headers) {
  if (before_start_transaction_callbacks_.empty() || IsInternalScheme(ctx)) {
    return net::OK;
  }
  ctx->event_type = huhi::kOnBeforeStartTransaction;
  ctx->headers = headers;
  ctx->referral_headers_list = referral_headers_list_.get();
  callbacks_[ctx->request_identifier] = std::move(callback);
  RunNextCallback(ctx);
  return net::ERR_IO_PENDING;
}

int HuhiRequestHandler::OnHeadersReceived(
    std::shared_ptr<huhi::HuhiRequestInfo> ctx,
    net::CompletionOnceCallback callback,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    GURL* allowed_unsafe_redirect_url) {
  if (!ctx->tab_origin.is_empty()) {
    huhi::RemoveTrackableSecurityHeadersForThirdParty(
        ctx->request_url, url::Origin::Create(ctx->tab_origin),
        original_response_headers, override_response_headers);
  }

  if (headers_received_callbacks_.empty() &&
      !ctx->request_url.SchemeIs(content::kChromeUIScheme)) {
    // Extension scheme not excluded since huhi_webtorrent needs it.
    return net::OK;
  }

  callbacks_[ctx->request_identifier] = std::move(callback);
  ctx->event_type = huhi::kOnHeadersReceived;
  ctx->original_response_headers = original_response_headers;
  ctx->override_response_headers = override_response_headers;
  ctx->allowed_unsafe_redirect_url = allowed_unsafe_redirect_url;

  RunNextCallback(ctx);
  return net::ERR_IO_PENDING;
}

void HuhiRequestHandler::OnURLRequestDestroyed(
    std::shared_ptr<huhi::HuhiRequestInfo> ctx) {
  if (base::Contains(callbacks_, ctx->request_identifier)) {
    callbacks_.erase(ctx->request_identifier);
  }
}

void HuhiRequestHandler::RunCallbackForRequestIdentifier(
    uint64_t request_identifier,
    int rv) {
  std::map<uint64_t, net::CompletionOnceCallback>::iterator it =
      callbacks_.find(request_identifier);
  // We intentionally do the async call to maintain the proper flow
  // of URLLoader callbacks.
  base::PostTask(FROM_HERE, {content::BrowserThread::UI},
                 base::BindOnce(std::move(it->second), rv));
}

// TODO(iefremov): Merge all callback containers into one and run only one loop
// instead of many (issues/5574).
void HuhiRequestHandler::RunNextCallback(
    std::shared_ptr<huhi::HuhiRequestInfo> ctx) {
  DCHECK_CURRENTLY_ON(content::BrowserThread::UI);

  if (!base::Contains(callbacks_, ctx->request_identifier)) {
    return;
  }

  // Continue processing callbacks until we hit one that returns PENDING
  int rv = net::OK;

  if (ctx->event_type == huhi::kOnBeforeRequest) {
    while (before_url_request_callbacks_.size() !=
           ctx->next_url_request_index) {
      huhi::OnBeforeURLRequestCallback callback =
          before_url_request_callbacks_[ctx->next_url_request_index++];
      huhi::ResponseCallback next_callback = base::Bind(
          &HuhiRequestHandler::RunNextCallback,
          weak_factory_.GetWeakPtr(),
          ctx);
      rv = callback.Run(next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  } else if (ctx->event_type == huhi::kOnBeforeStartTransaction) {
    while (before_start_transaction_callbacks_.size() !=
           ctx->next_url_request_index) {
      huhi::OnBeforeStartTransactionCallback callback =
          before_start_transaction_callbacks_[ctx->next_url_request_index++];
      huhi::ResponseCallback next_callback = base::Bind(
          &HuhiRequestHandler::RunNextCallback,
          weak_factory_.GetWeakPtr(),
          ctx);
      rv = callback.Run(ctx->headers, next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  } else if (ctx->event_type == huhi::kOnHeadersReceived) {
    while (headers_received_callbacks_.size() != ctx->next_url_request_index) {
      huhi::OnHeadersReceivedCallback callback =
          headers_received_callbacks_[ctx->next_url_request_index++];
      huhi::ResponseCallback next_callback = base::Bind(
          &HuhiRequestHandler::RunNextCallback,
          weak_factory_.GetWeakPtr(),
          ctx);
      rv = callback.Run(ctx->original_response_headers,
                        ctx->override_response_headers,
                        ctx->allowed_unsafe_redirect_url, next_callback, ctx);
      if (rv == net::ERR_IO_PENDING) {
        return;
      }
      if (rv != net::OK) {
        break;
      }
    }
  }

  if (rv != net::OK) {
    RunCallbackForRequestIdentifier(ctx->request_identifier, rv);
    return;
  }

  if (ctx->event_type == huhi::kOnBeforeRequest) {
    if (!ctx->new_url_spec.empty() &&
        (ctx->new_url_spec != ctx->request_url.spec()) &&
        IsRequestIdentifierValid(ctx->request_identifier)) {
      *ctx->new_url = GURL(ctx->new_url_spec);
    }
    if (ctx->blocked_by == huhi::kAdBlocked) {
      if (ctx->cancel_request_explicitly) {
        RunCallbackForRequestIdentifier(ctx->request_identifier,
                                        net::ERR_ABORTED);
        return;
      }
    }
  }
  RunCallbackForRequestIdentifier(ctx->request_identifier, rv);
}
