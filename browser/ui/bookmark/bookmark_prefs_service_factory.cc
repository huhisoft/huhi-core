/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "huhi/browser/ui/bookmark/bookmark_prefs_service_factory.h"

#include "huhi/browser/ui/bookmark/bookmark_prefs_service.h"
#include "huhi/common/pref_names.h"
#include "chrome/browser/profiles/incognito_helpers.h"
#include "chrome/browser/profiles/profile.h"
#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/pref_registry/pref_registry_syncable.h"

// static
BookmarkPrefsService* BookmarkPrefsServiceFactory::GetForBrowserContext(
    content::BrowserContext* context) {
  return static_cast<BookmarkPrefsService*>(
      GetInstance()->GetServiceForBrowserContext(context, true));
}

// static
BookmarkPrefsServiceFactory* BookmarkPrefsServiceFactory::GetInstance() {
  return base::Singleton<BookmarkPrefsServiceFactory>::get();
}

BookmarkPrefsServiceFactory::BookmarkPrefsServiceFactory()
    : BrowserContextKeyedServiceFactory(
          "BookmarkPrefsService",
          BrowserContextDependencyManager::GetInstance()) {}

BookmarkPrefsServiceFactory::~BookmarkPrefsServiceFactory() {}

KeyedService* BookmarkPrefsServiceFactory::BuildServiceInstanceFor(
    content::BrowserContext* context) const {
  return new BookmarkPrefsService(Profile::FromBrowserContext(context));
}

content::BrowserContext* BookmarkPrefsServiceFactory::GetBrowserContextToUse(
    content::BrowserContext* context) const {
  return chrome::GetBrowserContextRedirectedInIncognito(context);
}

bool BookmarkPrefsServiceFactory::ServiceIsCreatedWithBrowserContext() const {
  return true;
}

void BookmarkPrefsServiceFactory::RegisterProfilePrefs(
    user_prefs::PrefRegistrySyncable* registry) {
  registry->RegisterBooleanPref(kAlwaysShowBookmarkBarOnNTP, true);
}
