/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/common/network_constants.h"

const char kHuhiProxyPattern[] = "https://*.hnq.vn/*";
const char kHuhiSoftwareProxyPattern[] = "https://*.huhisoftware.com/*";

const char kHuhiUsageStandardPath[] = "/1/usage/huhi-core";
const char kHuhiUsageThresholdPath[] = "/1/usage/huhi-core-threshold";

const char kHuhiReferralsServer[] = "updates.hnq.vn";
const char kHuhiReferralsHeadersPath[] = "/promo/custom-headers";
const char kHuhiReferralsInitPath[] = "/promo/initialize/nonua";
const char kHuhiReferralsActivityPath[] = "/promo/activity";

const char kHuhiSafeBrowsingFileCheckProxy[] = "sb-ssl.hnq.vn";
const char kHuhiRedirectorProxy[] = "redirector.hnq.vn";
const char kHuhiClients4Proxy[] = "clients4.hnq.vn";
const char kHuhiStaticProxy[] = "static1.hnq.vn";

const char kAutofillPrefix[] = "https://www.gstatic.com/autofill/*";
const char kClients4Prefix[] = "*://clients4.google.com/";
const char kCRXDownloadPrefix[] =
    "*://clients2.googleusercontent.com/crx/blobs/*crx*";
const char kEmptyDataURI[] = "data:text/plain,";
const char kEmptyImageDataURI[] =
    "data:image/gif;base64,R0lGODlhAQABAIAAAAAAAP///"
    "yH5BAEAAAAALAAAAAABAAEAAAIBRAA7";
const char kJSDataURLPrefix[] = "data:application/javascript;base64,";
const char kGeoLocationsPattern[] =
    "https://www.googleapis.com/geolocation/v1/geolocate?key=*";
const char kSafeBrowsingPrefix[] = "https://safebrowsing.googleapis.com/";
const char kSafeBrowsingFileCheckPrefix[] =
    "https://sb-ssl.google.com/safebrowsing/clientreport/download";
const char kCRLSetPrefix1[] =
    "*://dl.google.com/release2/chrome_component/*crl-set*";
const char kCRLSetPrefix2[] =
    "*://*.gvt1.com/edgedl/release2/chrome_component/*";
const char kCRLSetPrefix3[] =
    "*://www.google.com/dl/release2/chrome_component/*crl-set*";
const char kCRLSetPrefix4[] =
    "*://storage.googleapis.com/update-delta/hfnkpimlhhgieaddgfemjhofmfblmnib"
    "/*crxd";
const char kChromeCastPrefix[] =
    "*://*.gvt1.com/edgedl/chromewebstore/*pkedcjkdefgpdelpbcmbmeomcjbeemfm*";

const char kWidevineGvt1Prefix[] =
    "*://*.gvt1.com/*oimompecagnajdejgnnjijobebaeigek*";
const char kWidevineGoogleDlPrefix[] =
    "*://dl.google.com/*oimompecagnajdejgnnjijobebaeigek*";

const char kUserAgentHeader[] = "User-Agent";
const char kHuhiPartnerHeader[] = "X-Huhi-Partner";
const char kHuhiServicesKeyHeader[] = "HuhiServiceKey";

const char kBittorrentMimeType[] = "application/x-bittorrent";
const char kOctetStreamMimeType[] = "application/octet-stream";

const char kSecGpcHeader[] = "Sec-GPC";
