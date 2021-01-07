// Copyright (c) 2020 The Huhi Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.


#include "huhi/browser/extensions/api/huhi_action_api.h"

#include <memory>
#include <string>
#include <utility>

#include "base/no_destructor.h"
#include "components/keyed_service/core/dependency_manager.h"
#include "components/keyed_service/core/keyed_service_factory.h"
#include "chrome/browser/extensions/api/tabs/tabs_constants.h"
#include "chrome/browser/extensions/api/tabs/windows_util.h"
#include "chrome/browser/extensions/chrome_extension_function_details.h"
#include "chrome/browser/extensions/window_controller.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/ui/browser.h"
#include "extensions/browser/extension_function.h"

namespace {

class HuhiActionAPIDependencyManager : public DependencyManager {
 public:
  static HuhiActionAPIDependencyManager* GetInstance() {
    static base::NoDestructor<HuhiActionAPIDependencyManager> factory;
    return factory.get();
  }
  HuhiActionAPIDependencyManager() {}
  ~HuhiActionAPIDependencyManager() override {}

#ifndef NDEBUG
void DumpContextDependencies(void* context) const override {}
#endif  // NDEBUG

 private:
  DISALLOW_COPY_AND_ASSIGN(HuhiActionAPIDependencyManager);
};

class HuhiActionAPIFactory : public KeyedServiceFactory {
 public:
  HuhiActionAPIFactory() : KeyedServiceFactory("HuhiActionAPI",
      HuhiActionAPIDependencyManager::GetInstance(), SIMPLE) { }

  extensions::HuhiActionAPI* GetHuhiActionAPI(Browser* context) {
    return static_cast<extensions::HuhiActionAPI*>(
          GetServiceForContext(context, true));
  }

 private:
  // KeyedServiceFactory:
  std::unique_ptr<KeyedService> BuildServiceInstanceFor(
      void* context) const final {
    return base::WrapUnique(new extensions::HuhiActionAPI());
  }
  bool IsOffTheRecord(void* context) const final {
    return static_cast<Browser*>(context)
        ->profile()->IsOffTheRecord();
  }
  void* GetContextToUse(void* context) const final {
    return context;
  }
  void CreateServiceNow(void* context) final {
    KeyedServiceFactory::GetServiceForContext(context, true);
  }
  DISALLOW_COPY_AND_ASSIGN(HuhiActionAPIFactory);
};

static HuhiActionAPIFactory* GetFactoryInstance() {
  static base::NoDestructor<HuhiActionAPIFactory> instance;
  return instance.get();
}

}  // namespace

namespace extensions {
//
// HuhiActionAPI::Observer
//
HuhiActionAPI::Observer::Observer() { }

HuhiActionAPI::Observer::~Observer() { }

//
// HuhiActionAPI
//
// static
HuhiActionAPI* HuhiActionAPI::Get(Browser* context) {
  return GetFactoryInstance()->GetHuhiActionAPI(context);
}

// static
bool HuhiActionAPI::ShowActionUI(
      ExtensionFunction* extension_function,
      const std::string& extension_id,
      std::unique_ptr<int> window_id_param,
      std::unique_ptr<std::string> ui_relative_path_param,
      std::string* error) {
  // Which browser should we send the action to
  Browser* browser = nullptr;
  // If the windowId is specified, find it. Otherwise get the active
  // window for the profile.
  if (!window_id_param.get()) {
    browser = ChromeExtensionFunctionDetails(extension_function)
        .GetCurrentBrowser();
    if (!browser) {
      *error = tabs_constants::kNoCurrentWindowError;
      return false;
    }
  } else {
    int window_id = *window_id_param;
    std::string get_browser_error;
    if (!windows_util::GetBrowserFromWindowID(
            extension_function,
            window_id,
            WindowController::GetAllWindowFilter(),
            &browser,
            &get_browser_error)) {
      *error = get_browser_error;
      return false;
    }
  }
  return ShowActionUI(browser, extension_id, std::move(ui_relative_path_param),
      error);
}

// static
bool HuhiActionAPI::ShowActionUI(
        Browser* browser,
        const std::string& extension_id,
        std::unique_ptr<std::string> ui_relative_path_param,
        std::string* error) {
  bool did_notify = HuhiActionAPI::Get(browser)->NotifyObservers(extension_id,
      std::move(ui_relative_path_param));
  if (!did_notify) {
    *error = "No toolbar is registered to observe HuhiActionUI "
              "calls for this window";
    return false;
  }
  return true;
}

HuhiActionAPI::HuhiActionAPI() {}

HuhiActionAPI::~HuhiActionAPI() {
}

void HuhiActionAPI::AddObserver(Observer* observer) {
  observers_.AddObserver(observer);
}

void HuhiActionAPI::RemoveObserver(Observer* observer) {
  observers_.RemoveObserver(observer);
}

bool HuhiActionAPI::NotifyObservers(const std::string& extension_id,
      std::unique_ptr<std::string> ui_relative_path_param) {
  bool did_notify = false;
  for (auto& observer : observers_) {
    observer.OnHuhiActionShouldTrigger(extension_id,
        std::move(ui_relative_path_param));
    did_notify = true;
  }
  return did_notify;
}
}  // namespace extensions
