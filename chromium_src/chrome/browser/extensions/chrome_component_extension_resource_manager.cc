/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "chrome/browser/extensions/chrome_component_extension_resource_manager.h"

#include "huhi/components/huhi_extension/grit/huhi_extension_generated_map.h"
#include "huhi/components/huhi_extension/grit/huhi_extension_resources_map.h"
#include "huhi/components/huhi_rewards/browser/buildflags/buildflags.h"
#include "huhi/components/huhi_webtorrent/browser/buildflags/buildflags.h"

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
#include "huhi/components/huhi_webtorrent/grit/huhi_webtorrent_generated_map.h"
#include "huhi/components/huhi_webtorrent/grit/huhi_webtorrent_resources_map.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#include "huhi/components/huhi_rewards/resources/extension/grit/huhi_rewards_extension_resources_map.h"
#include "huhi/components/huhi_rewards/resources/extension/grit/huhi_rewards_panel_generated_map.h"
#endif

#if BUILDFLAG(HUHI_REWARDS_ENABLED)
#define HUHI_REWARDS_EXTENSION_RESOURCES                           \
  AddComponentResourceEntries(kHuhiRewardsExtensionResources,      \
                              kHuhiRewardsExtensionResourcesSize); \
  AddComponentResourceEntries(kHuhiRewardsPanelGenerated,          \
                              kHuhiRewardsPanelGeneratedSize);
#else
#define HUHI_REWARDS_EXTENSION_RESOURCES
#endif

#if BUILDFLAG(ENABLE_HUHI_WEBTORRENT)
#define HUHI_WEBTORRENT_RESOURCES                            \
  AddComponentResourceEntries(kHuhiWebtorrentResources,      \
                              kHuhiWebtorrentResourcesSize); \
  AddComponentResourceEntries(kHuhiWebtorrentGenerated,      \
                              kHuhiWebtorrentGeneratedSize);
#else
#define HUHI_WEBTORRENT_RESOURCES
#endif

#define HUHI_CHROME_COMPONENT_EXTENSION_RESOURCE_MANAGER_DATA_DATA  \
  AddComponentResourceEntries(kHuhiExtension, kHuhiExtensionSize); \
  AddComponentResourceEntries(kHuhiExtensionGenerated,              \
                              kHuhiExtensionGeneratedSize);         \
  HUHI_REWARDS_EXTENSION_RESOURCES                                  \
  HUHI_WEBTORRENT_RESOURCES

#include "../../../../../chrome/browser/extensions/chrome_component_extension_resource_manager.cc"
#undef HUHI_CHROME_COMPONENT_EXTENSION_RESOURCE_MANAGER_DATA_DATA
