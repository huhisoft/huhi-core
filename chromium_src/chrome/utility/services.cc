/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "build/build_config.h"
#include "huhi/components/ipfs/browser/buildflags/buildflags.h"

#if !defined(OS_ANDROID)
#include "huhi/utility/importer/huhi_profile_import_impl.h"
#endif

#if BUILDFLAG(IPFS_ENABLED)
#include "huhi/components/services/ipfs/ipfs_service_impl.h"
#include "huhi/components/services/ipfs/public/mojom/ipfs_service.mojom.h"
#endif

namespace {

#if !defined(OS_ANDROID)
auto RunHuhiProfileImporter(
    mojo::PendingReceiver<huhi::mojom::ProfileImport> receiver) {
  return std::make_unique<HuhiProfileImportImpl>(std::move(receiver));
}
#endif

#if BUILDFLAG(IPFS_ENABLED)
auto RunIpfsService(mojo::PendingReceiver<ipfs::mojom::IpfsService> receiver) {
  return std::make_unique<ipfs::IpfsServiceImpl>(std::move(receiver));
}
#endif

}  // namespace

#if defined(OS_ANDROID)
#define HUHI_PROFILE_IMPORTER
#else
#define HUHI_PROFILE_IMPORTER \
    RunHuhiProfileImporter,
#endif

#if BUILDFLAG(IPFS_ENABLED)
#define HUHI_IPFS_SERVICE \
  RunIpfsService,
#else
#define HUHI_IPFS_SERVICE
#endif

#define HUHI_GET_MAIN_THREAD_SERVICE_FACTORY \
    HUHI_PROFILE_IMPORTER \
    HUHI_IPFS_SERVICE

#include "../../../../chrome/utility/services.cc"

#undef HUHI_GET_MAIN_THREAD_SERVICE_FACTORY
#undef HUHI_PROFILE_IMPORTER
#undef HUHI_IPFS_SERVICE
