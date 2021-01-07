/* Copyright (c) 2020 The Huhi Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.toolbar.top;

import android.animation.Animator;
import android.animation.ObjectAnimator;
import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.PorterDuff;
import android.graphics.drawable.Drawable;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.TextPaint;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.text.style.ForegroundColorSpan;
import android.util.AttributeSet;
import android.util.Pair;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.view.Window;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.PopupWindow;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.widget.AppCompatImageView;

import org.chromium.base.ApiCompatibilityUtils;
import org.chromium.base.ContextUtils;
import org.chromium.base.Log;
import org.chromium.base.MathUtils;
import org.chromium.base.ThreadUtils;
import org.chromium.base.task.AsyncTask;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiAdsNativeHelper;
import org.chromium.chrome.browser.HuhiFeatureList;
import org.chromium.chrome.browser.HuhiRelaunchUtils;
import org.chromium.chrome.browser.HuhiRewardsHelper;
import org.chromium.chrome.browser.HuhiRewardsNativeWorker;
import org.chromium.chrome.browser.HuhiRewardsObserver;
import org.chromium.chrome.browser.HuhiRewardsPanelPopup;
import org.chromium.chrome.browser.app.HuhiActivity;
import org.chromium.chrome.browser.huhi_stats.HuhiStatsUtil;
import org.chromium.chrome.browser.customtabs.CustomTabActivity;
import org.chromium.chrome.browser.customtabs.features.toolbar.CustomTabToolbar;
import org.chromium.chrome.browser.dialogs.HuhiAdsSignupDialog;
import org.chromium.chrome.browser.flags.ChromeFeatureList;
import org.chromium.chrome.browser.local_database.HuhiStatsTable;
import org.chromium.chrome.browser.local_database.DatabaseHelper;
import org.chromium.chrome.browser.local_database.SavedBandwidthTable;
import org.chromium.chrome.browser.notifications.retention.RetentionNotificationUtil;
import org.chromium.chrome.browser.ntp.HuhiNewTabPageLayout;
import org.chromium.chrome.browser.ntp.NewTabPage;
import org.chromium.chrome.browser.onboarding.OnboardingPrefManager;
import org.chromium.chrome.browser.onboarding.SearchActivity;
import org.chromium.chrome.browser.preferences.HuhiPref;
import org.chromium.chrome.browser.preferences.HuhiPrefServiceBridge;
import org.chromium.chrome.browser.preferences.website.HuhiShieldsContentSettings;
import org.chromium.chrome.browser.preferences.website.HuhiShieldsContentSettingsObserver;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.settings.AppearancePreferences;
import org.chromium.chrome.browser.settings.HuhiSearchEngineUtils;
import org.chromium.chrome.browser.shields.HuhiShieldsHandler;
import org.chromium.chrome.browser.shields.HuhiShieldsMenuObserver;
import org.chromium.chrome.browser.tab.Tab;
import org.chromium.chrome.browser.tab.TabImpl;
import org.chromium.chrome.browser.tab.TabSelectionType;
import org.chromium.chrome.browser.tabmodel.TabModelSelector;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorTabModelObserver;
import org.chromium.chrome.browser.tabmodel.TabModelSelectorTabObserver;
import org.chromium.chrome.browser.toolbar.HomeButton;
import org.chromium.chrome.browser.toolbar.ToolbarColors;
import org.chromium.chrome.browser.toolbar.ToolbarDataProvider;
import org.chromium.chrome.browser.toolbar.ToolbarTabController;
import org.chromium.chrome.browser.toolbar.bottom.BottomToolbarVariationManager;
import org.chromium.chrome.browser.toolbar.menu_button.HuhiMenuButtonCoordinator;
import org.chromium.chrome.browser.toolbar.menu_button.MenuButtonCoordinator;
import org.chromium.chrome.browser.toolbar.top.ToolbarLayout;
import org.chromium.chrome.browser.util.PackageUtils;
import org.chromium.components.browser_ui.styles.ChromeColors;
import org.chromium.components.embedder_support.util.UrlUtilities;
import org.chromium.components.url_formatter.UrlFormatter;
import org.chromium.components.user_prefs.UserPrefs;
import org.chromium.content_public.browser.NavigationHandle;
import org.chromium.ui.UiUtils;
import org.chromium.ui.interpolators.BakedBezierInterpolator;
import org.chromium.ui.widget.Toast;

import java.net.URL;
import java.util.Calendar;
import java.util.Date;
import java.util.List;

public abstract class HuhiToolbarLayout extends ToolbarLayout implements OnClickListener,
  View.OnLongClickListener,
  HuhiRewardsObserver,
  HuhiRewardsNativeWorker.PublisherObserver {
  public static final String PREF_HIDE_HUHI_REWARDS_ICON = "hide_huhi_rewards_icon";

  private static final long MB_10 = 10000000;
  private static final long MINUTES_10 = 10 * 60 * 1000;

  private DatabaseHelper mDatabaseHelper = DatabaseHelper.getInstance();

  private ImageButton mHuhiShieldsButton;
  private ImageButton mHuhiRewardsButton;
  private HomeButton mHomeButton;
  private FrameLayout mShieldsLayout;
  private FrameLayout mRewardsLayout;
  private HuhiShieldsHandler mHuhiShieldsHandler;
  private TabModelSelectorTabObserver mTabModelSelectorTabObserver;
  private TabModelSelectorTabModelObserver mTabModelSelectorTabModelObserver;
  private HuhiRewardsNativeWorker mHuhiRewardsNativeWorker;
  private HuhiRewardsPanelPopup mRewardsPopup;
  private HuhiShieldsContentSettings mHuhiShieldsContentSettings;
  private HuhiShieldsContentSettingsObserver mHuhiShieldsContentSettingsObserver;
  private TextView mHuhiRewardsNotificationsCount;
  private ImageView mHuhiRewardsOnboardingIcon;
  private boolean mShieldsLayoutIsColorBackground;
  private int mCurrentToolbarColor;

  private boolean mIsPublisherVerified;
  private boolean mIsNotificationPosted;
  private boolean mIsInitialNotificationPosted; // initial red circle notification

  private PopupWindow mShieldsTooltipPopupWindow;

  private boolean mIsBottomToolbarVisible;

  public HuhiToolbarLayout(Context context, AttributeSet attrs) {
    super(context, attrs);
  }

  @Override
  void destroy() {
    if (mHuhiShieldsContentSettings != null) {
      mHuhiShieldsContentSettings.removeObserver(mHuhiShieldsContentSettingsObserver);
    }
    super.destroy();

    if (mHuhiRewardsNativeWorker != null) {
      mHuhiRewardsNativeWorker.RemoveObserver(this);
      mHuhiRewardsNativeWorker.RemovePublisherObserver(this);
    }
  }

  @Override
  protected void onFinishInflate() {
    super.onFinishInflate();

    if (this instanceof ToolbarTablet) {
      ImageButton forwardButton = findViewById(R.id.forward_button);
      if (forwardButton != null) {
        final Drawable forwardButtonDrawable = UiUtils.getTintedDrawable(
            getContext(), R.drawable.btn_right_tablet, R.color.default_icon_color_tint_list);
        forwardButton.setImageDrawable(forwardButtonDrawable);
      }
    }

    mShieldsLayout = (FrameLayout) findViewById(R.id.huhi_shields_button_layout);
    mRewardsLayout = (FrameLayout) findViewById(R.id.huhi_rewards_button_layout);
    mHuhiRewardsNotificationsCount = (TextView) findViewById(R.id.br_notifications_count);
    mHuhiRewardsOnboardingIcon = findViewById(R.id.br_rewards_onboarding_icon);
    mHuhiShieldsButton = (ImageButton) findViewById(R.id.huhi_shields_button);
    mHuhiRewardsButton = (ImageButton) findViewById(R.id.huhi_rewards_button);
    mHomeButton = (HomeButton) findViewById(R.id.home_button);

    if (mHomeButton != null) {
      mHomeButton.setOnLongClickListener(this);
    }

    if (mHuhiShieldsButton != null) {
      mHuhiShieldsButton.setClickable(true);
      mHuhiShieldsButton.setOnClickListener(this);
      mHuhiShieldsButton.setOnLongClickListener(this);
    }

    if (mHuhiRewardsButton != null) {
      mHuhiRewardsButton.setClickable(true);
      mHuhiRewardsButton.setOnClickListener(this);
      mHuhiRewardsButton.setOnLongClickListener(this);
    }

    mHuhiShieldsHandler = new HuhiShieldsHandler(getContext());
    mHuhiShieldsHandler.addObserver(new HuhiShieldsMenuObserver() {
      @Override
      public void onMenuTopShieldsChanged(boolean isOn, boolean isTopShield) {
        Tab currentTab = getToolbarDataProvider().getTab();
        if (currentTab == null) {
          return;
        }
        if (isTopShield) {
          updateHuhiShieldsButtonState(currentTab);
        }
        if (currentTab.isLoading()) {
          currentTab.stopLoading();
        }
        currentTab.reloadIgnoringCache();
        if (null != mHuhiShieldsHandler) {
          // Clean the Huhiry Panel
          mHuhiShieldsHandler.updateValues(0, 0, 0, 0);
        }
      }
    });
    mHuhiShieldsContentSettingsObserver = new HuhiShieldsContentSettingsObserver() {
      @Override
      public void blockEvent(int tabId, String block_type, String subresource) {
        mHuhiShieldsHandler.addStat(tabId, block_type, subresource);
        Tab currentTab = getToolbarDataProvider().getTab();
        if (currentTab == null || currentTab.getId() != tabId) {
          return;
        }
        mHuhiShieldsHandler.updateValues(tabId);
        if (!isIncognito()
            && OnboardingPrefManager.getInstance().isHuhiStatsEnabled()
            && (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_ADS)
                || block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_TRACKERS))) {
          addStatsToDb(block_type, subresource, currentTab.getUrlString());
        }
        if (!OnboardingPrefManager.getInstance().hasShieldsTooltipShown()
            && PackageUtils.isFirstInstall(getContext())) {
          mShieldsTooltipPopupWindow = mHuhiShieldsHandler.showPopupMenu(mHuhiShieldsButton, true);
          OnboardingPrefManager.getInstance().setShieldsTooltipShown(true);
          mShieldsTooltipPopupWindow.getContentView().setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
              mShieldsTooltipPopupWindow.dismiss();
              mShieldsTooltipPopupWindow = null;
              showShieldsMenu(mHuhiShieldsButton);
            }
          });
        }
      }

      @Override
      public void savedBandwidth(long savings) {
        if (!isIncognito()
            && OnboardingPrefManager.getInstance().isHuhiStatsEnabled()) {
          addSavedBandwidthToDb(savings);
        }
      }
    };
    // Initially show shields off image. Shields button state will be updated when tab is
    // shown and loading state is changed.
    updateHuhiShieldsButtonState(null);
    if (this instanceof ToolbarPhone) {
        if (getMenuButtonCoordinator() != null && isMenuButtonOnBottom()) {
            getMenuButtonCoordinator().setVisibility(false);
        }
    }
  }

  @Override
  protected void onNativeLibraryReady() {
    super.onNativeLibraryReady();
    mHuhiShieldsContentSettings = HuhiShieldsContentSettings.getInstance();
    mHuhiShieldsContentSettings.addObserver(mHuhiShieldsContentSettingsObserver);

    SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
    if (ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS)
        && !HuhiPrefServiceBridge.getInstance().getSafetynetCheckFailed()
        && !sharedPreferences.getBoolean(
          AppearancePreferences.PREF_HIDE_HUHI_REWARDS_ICON, false)
        && mRewardsLayout != null) {
      mRewardsLayout.setVisibility(View.VISIBLE);
    }
    if (mShieldsLayout != null) {
      updateShieldsLayoutBackground(!(mRewardsLayout != null && mRewardsLayout.getVisibility() == View.VISIBLE));
      mShieldsLayout.setVisibility(View.VISIBLE);
    }
    mHuhiRewardsNativeWorker = HuhiRewardsNativeWorker.getInstance();
    if (mHuhiRewardsNativeWorker != null) {
      mHuhiRewardsNativeWorker.AddObserver(this);
      mHuhiRewardsNativeWorker.AddPublisherObserver(this);
      mHuhiRewardsNativeWorker.TriggerOnNotifyFrontTabUrlChanged();
      mHuhiRewardsNativeWorker.GetAllNotifications();
    }
  }

  @Override
  public void setTabModelSelector(TabModelSelector selector) {
    // We might miss events before calling setTabModelSelector, so we need
    // to proactively update the shields button state here, otherwise shields
    // might sometimes show as disabled while it is actually enabled.
    updateHuhiShieldsButtonState(getToolbarDataProvider().getTab());
    mTabModelSelectorTabObserver = new TabModelSelectorTabObserver(selector) {
      @Override
      public void onShown(Tab tab, @TabSelectionType int type) {
        // Update shields button state when visible tab is changed.
        updateHuhiShieldsButtonState(tab);
      }

      @Override
      public void onPageLoadStarted(Tab tab, String url) {
        if (getToolbarDataProvider().getTab() == tab) {
          updateHuhiShieldsButtonState(tab);
        }
        mHuhiShieldsHandler.clearHuhiShieldsCount(tab.getId());
        dismissShieldsTooltip();
      }

      @Override
      public void onPageLoadFinished(final Tab tab, String url) {
        if (getToolbarDataProvider().getTab() == tab) {
          mHuhiShieldsHandler.updateHost(url);
          updateHuhiShieldsButtonState(tab);

          Profile mProfile = Profile.getLastUsedRegularProfile();
          long trackersBlockedCount = HuhiPrefServiceBridge.getInstance().getTrackersBlockedCount(mProfile);
          long adsBlockedCount = HuhiPrefServiceBridge.getInstance().getAdsBlockedCount(mProfile);
          long dataSaved = HuhiPrefServiceBridge.getInstance().getDataSaved(mProfile);
          long estimatedMillisecondsSaved =
                  (trackersBlockedCount + adsBlockedCount) * HuhiStatsUtil.MILLISECONDS_PER_ITEM;

          if (!OnboardingPrefManager.getInstance().isAdsTrackersNotificationStarted()
              && (trackersBlockedCount + adsBlockedCount) > 250
              && PackageUtils.isFirstInstall(getContext())) {
            RetentionNotificationUtil.scheduleNotification(getContext(), RetentionNotificationUtil.HUHI_STATS_ADS_TRACKERS);
            OnboardingPrefManager.getInstance().setAdsTrackersNotificationStarted(true);
          }

          if (!OnboardingPrefManager.getInstance().isDataSavedNotificationStarted()
              && dataSaved > MB_10
              && PackageUtils.isFirstInstall(getContext())) {
            RetentionNotificationUtil.scheduleNotification(getContext(), RetentionNotificationUtil.HUHI_STATS_DATA);
            OnboardingPrefManager.getInstance().setDataSavedNotificationStarted(true);
          }

          if (!OnboardingPrefManager.getInstance().isTimeSavedNotificationStarted()
              && estimatedMillisecondsSaved > MINUTES_10
              && PackageUtils.isFirstInstall(getContext())) {
            RetentionNotificationUtil.scheduleNotification(getContext(), RetentionNotificationUtil.HUHI_STATS_TIME);
            OnboardingPrefManager.getInstance().setTimeSavedNotificationStarted(true);
          }
        }
      }

      @Override
      public void onDidFinishNavigation(Tab tab, NavigationHandle navigation) {
        if (getToolbarDataProvider().getTab() == tab && mHuhiRewardsNativeWorker != null
            && !tab.isIncognito()) {
          mHuhiRewardsNativeWorker.OnNotifyFrontTabUrlChanged(tab.getId(), tab.getUrlString());
        }
        if (PackageUtils.isFirstInstall(getContext()) && tab.getUrlString() != null
                && (tab.getUrlString().equals(HuhiActivity.REWARDS_SETTINGS_URL)
                        || tab.getUrlString().equals(HuhiActivity.HUHI_REWARDS_SETTINGS_URL))
                && !HuhiAdsNativeHelper.nativeIsHuhiAdsEnabled(
                        Profile.getLastUsedRegularProfile())
                && HuhiRewardsHelper.shouldShowHuhiRewardsOnboardingModal()
                && ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS)) {
            showHuhiRewardsOnboardingModal();
            HuhiRewardsHelper.updateHuhiRewardsAppOpenCount();
            HuhiRewardsHelper.setShowHuhiRewardsOnboardingModal(false);
        }
      }

      @Override
      public void onDestroyed(Tab tab) {
        mHuhiShieldsHandler.removeStat(tab.getId());
      }
    };

    mTabModelSelectorTabModelObserver = new TabModelSelectorTabModelObserver(selector) {
      @Override
      public void didSelectTab(Tab tab, @TabSelectionType int type, int lastId) {
        if (getToolbarDataProvider().getTab() == tab &&
            mHuhiRewardsNativeWorker != null &&
            !tab.isIncognito()) {
          mHuhiRewardsNativeWorker.OnNotifyFrontTabUrlChanged(tab.getId(), tab.getUrlString());
        }
      }
    };
  }

  public void dismissShieldsTooltip() {
    if (mShieldsTooltipPopupWindow != null) {
      mShieldsTooltipPopupWindow.dismiss();
    }
  }

  private void showHuhiRewardsOnboardingModal() {
      Context context = getContext();
      final Dialog dialog = new Dialog(context);
      dialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
      dialog.setCancelable(false);
      dialog.setContentView(R.layout.huhi_rewards_onboarding_modal);
      dialog.getWindow().setBackgroundDrawableResource(android.R.color.transparent);

      View huhiRewardsOnboardingModalView =
              dialog.findViewById(R.id.huhi_rewards_onboarding_modal_layout);
      huhiRewardsOnboardingModalView.setBackgroundColor(
              context.getResources().getColor(android.R.color.white));
      huhiRewardsOnboardingModalView.setVisibility(View.VISIBLE);

      String tosText =
              String.format(context.getResources().getString(R.string.huhi_rewards_tos_text),
                      context.getResources().getString(R.string.terms_of_service),
                      context.getResources().getString(R.string.privacy_policy));
      int termsOfServiceIndex =
              tosText.indexOf(context.getResources().getString(R.string.terms_of_service));
      Spanned tosTextSpanned = HuhiRewardsHelper.spannedFromHtmlString(tosText);
      SpannableString tosTextSS = new SpannableString(tosTextSpanned.toString());

      ClickableSpan tosClickableSpan = new ClickableSpan() {
          @Override
          public void onClick(@NonNull View textView) {
              CustomTabActivity.showInfoPage(context, HuhiActivity.HUHI_TERMS_PAGE);
          }
          @Override
          public void updateDrawState(@NonNull TextPaint ds) {
              super.updateDrawState(ds);
              ds.setUnderlineText(false);
          }
      };

      tosTextSS.setSpan(tosClickableSpan, termsOfServiceIndex,
              termsOfServiceIndex
                      + context.getResources().getString(R.string.terms_of_service).length(),
              Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
      tosTextSS.setSpan(new ForegroundColorSpan(context.getResources().getColor(
                                R.color.huhi_rewards_modal_theme_color)),
              termsOfServiceIndex,
              termsOfServiceIndex
                      + context.getResources().getString(R.string.terms_of_service).length(),
              Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);

      ClickableSpan privacyProtectionClickableSpan = new ClickableSpan() {
          @Override
          public void onClick(@NonNull View textView) {
              CustomTabActivity.showInfoPage(context, HuhiActivity.HUHI_PRIVACY_POLICY);
          }
          @Override
          public void updateDrawState(@NonNull TextPaint ds) {
              super.updateDrawState(ds);
              ds.setUnderlineText(false);
          }
      };

      int privacyPolicyIndex =
              tosText.indexOf(context.getResources().getString(R.string.privacy_policy));
      tosTextSS.setSpan(privacyProtectionClickableSpan, privacyPolicyIndex,
              privacyPolicyIndex
                      + context.getResources().getString(R.string.privacy_policy).length(),
              Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
      tosTextSS.setSpan(new ForegroundColorSpan(context.getResources().getColor(
                                R.color.huhi_rewards_modal_theme_color)),
              privacyPolicyIndex,
              privacyPolicyIndex
                      + context.getResources().getString(R.string.privacy_policy).length(),
              Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);

      TextView tosAndPpText = huhiRewardsOnboardingModalView.findViewById(R.id.tos_pp_text);
      tosAndPpText.setMovementMethod(LinkMovementMethod.getInstance());
      tosAndPpText.setText(tosTextSS);

      TextView takeQuickTourButton =
              huhiRewardsOnboardingModalView.findViewById(R.id.take_quick_tour_button);
      takeQuickTourButton.setOnClickListener((new View.OnClickListener() {
          @Override
          public void onClick(View v) {
              HuhiRewardsHelper.setShowHuhiRewardsOnboardingOnce(true);
              HuhiActivity.getHuhiActivity().openRewardsPanel();
              dialog.dismiss();
          }
      }));
      Button btnHuhiRewards = huhiRewardsOnboardingModalView.findViewById(R.id.btn_huhi_rewards);
      btnHuhiRewards.setOnClickListener((new View.OnClickListener() {
          @Override
          public void onClick(View v) {
              HuhiAdsNativeHelper.nativeSetAdsEnabled(Profile.getLastUsedRegularProfile());
              HuhiRewardsNativeWorker.getInstance().SetAutoContributeEnabled(true);
              dialog.dismiss();
          }
      }));
      AppCompatImageView modalCloseButton =
              huhiRewardsOnboardingModalView.findViewById(R.id.modal_close);
      modalCloseButton.setOnClickListener((new View.OnClickListener() {
          @Override
          public void onClick(View v) {
              dialog.dismiss();
          }
      }));

      dialog.show();
  }

  private void addSavedBandwidthToDb(long savings) {
    new AsyncTask<Void>() {
      @Override
      protected Void doInBackground() {
        try {
          SavedBandwidthTable savedBandwidthTable = new SavedBandwidthTable(savings, HuhiStatsUtil.getCalculatedDate("yyyy-MM-dd", 0));
          long rowId = mDatabaseHelper.insertSavedBandwidth(savedBandwidthTable);
        } catch (Exception e) {
          // Do nothing if url is invalid.
          // Just return w/o showing shields popup.
          return null;
        }
        return null;
      }
      @Override
      protected void onPostExecute(Void result) {
        assert ThreadUtils.runningOnUiThread();
        if (isCancelled()) return;
      }
    } .executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
  }

  private void addStatsToDb(String statType, String statSite, String url) {
    new AsyncTask<Void>() {
      @Override
      protected Void doInBackground() {
        try {
          URL urlObject = new URL(url);
          URL siteObject = new URL(statSite);
          HuhiStatsTable huhiStatsTable = new HuhiStatsTable(url, urlObject.getHost(), statType, statSite, siteObject.getHost(), HuhiStatsUtil.getCalculatedDate("yyyy-MM-dd", 0));
          long rowId = mDatabaseHelper.insertStats(huhiStatsTable);
        } catch (Exception e) {
          // Do nothing if url is invalid.
          // Just return w/o showing shields popup.
          return null;
        }
        return null;
      }
      @Override
      protected void onPostExecute(Void result) {
        assert ThreadUtils.runningOnUiThread();
        if (isCancelled()) return;
      }
    } .executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
  }

  public void hideRewardsOnboardingIcon() {
    if (mHuhiRewardsOnboardingIcon != null) {
      mHuhiRewardsOnboardingIcon.setVisibility(View.GONE);
    }
    if (mHuhiRewardsNotificationsCount != null) {
      mHuhiRewardsNotificationsCount.setVisibility(View.GONE);
    }
    SharedPreferences sharedPref = ContextUtils.getAppSharedPreferences();
    SharedPreferences.Editor editor = sharedPref.edit();
    editor.putBoolean(HuhiRewardsPanelPopup.PREF_WAS_TOOLBAR_BAT_LOGO_BUTTON_PRESSED, true);
    editor.apply();
  }

  @Override
  public void onClick(View v) {
    if (mHuhiShieldsHandler == null) {
      assert false;
      return;
    }
    if (mHuhiShieldsButton == v && mHuhiShieldsButton != null) {
      showShieldsMenu(mHuhiShieldsButton);
    } else if (mHuhiRewardsButton == v && mHuhiRewardsButton != null) {
      // Context context = getContext();
      // if (checkForRewardsOnboarding()) {
      //   OnboardingPrefManager.getInstance().showOnboarding(context);
      //   hideRewardsOnboardingIcon();
      // } else {
      //   if (null != mRewardsPopup) {
      //     return;
      //   }
      //   mRewardsPopup = new HuhiRewardsPanelPopup(v);
      //   mRewardsPopup.showLikePopDownMenu();
      // }
      if (null != mRewardsPopup) {
        return;
      }
      hideRewardsOnboardingIcon();
      OnboardingPrefManager.getInstance().setOnboardingShown(true);
      mRewardsPopup = new HuhiRewardsPanelPopup(v);
      mRewardsPopup.showLikePopDownMenu();
      if (mHuhiRewardsNotificationsCount.isShown()) {
        SharedPreferences sharedPref = ContextUtils.getAppSharedPreferences();
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putBoolean(HuhiRewardsPanelPopup.PREF_WAS_TOOLBAR_BAT_LOGO_BUTTON_PRESSED, true);
        editor.apply();
        mHuhiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
        mIsInitialNotificationPosted = false;
      }
    }
  }

  private boolean checkForRewardsOnboarding() {
    return PackageUtils.isFirstInstall(getContext())
           && !HuhiAdsNativeHelper.nativeIsHuhiAdsEnabled(Profile.getLastUsedRegularProfile())
           && ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS)
           && !OnboardingPrefManager.getInstance().isOnboardingShown();
  }

  private void showShieldsMenu(View mHuhiShieldsButton) {
    Tab currentTab = getToolbarDataProvider().getTab();
    if (currentTab == null) {
      return;
    }
    try {
      URL url = new URL(currentTab.getUrlString());
      // Don't show shields popup if protocol is not valid for shields.
      if (!isValidProtocolForShields(url.getProtocol())) {
        return;
      }
      mHuhiShieldsHandler.show(mHuhiShieldsButton, currentTab);
    } catch (Exception e) {
      // Do nothing if url is invalid.
      // Just return w/o showing shields popup.
      return;
    }
  }

  @Override
  public boolean onLongClick(View v) {
    // Use null as the default description since Toast.showAnchoredToast
    // will return false if it is null.
    String description = null;
    Context context = getContext();
    Resources resources = context.getResources();

    if (v == mHuhiShieldsButton) {
      description = resources.getString(R.string.accessibility_toolbar_btn_huhi_shields);
    } else if (v == mHuhiRewardsButton) {
      description = resources.getString(R.string.accessibility_toolbar_btn_huhi_rewards);
    } else if (v == mHomeButton) {
      description = resources.getString(R.string.accessibility_toolbar_btn_home);
    }

    return Toast.showAnchoredToast(context, v, description);
  }

  @Override
  public void onUrlFocusChange(boolean hasFocus) {
    Context context = getContext();
    if (hasFocus
        && PackageUtils.isFirstInstall(context)
        && !OnboardingPrefManager.getInstance().hasSearchEngineOnboardingShown()
        && !HuhiSearchEngineUtils.getDSEShortName(true).equals(OnboardingPrefManager.DUCKDUCKGO)) {
      Intent searchActivityIntent = new Intent(context, SearchActivity.class);
      context.startActivity(searchActivityIntent);
    }
    super.onUrlFocusChange(hasFocus);
  }

  public void populateUrlAnimatorSet(boolean hasFocus, int urlFocusToolbarButtonsDuration,
                                     int urlClearFocusTabStackDelayMs, int urlFocusToolbarButtonsTranslationXDP,
                                     List<Animator> animators) {
    if (mHuhiShieldsButton != null) {
      Animator animator;
      if (hasFocus) {
        float density = getContext().getResources().getDisplayMetrics().density;
        boolean isRtl = getLayoutDirection() == LAYOUT_DIRECTION_RTL;
        float toolbarButtonTranslationX =
          MathUtils.flipSignIf(urlFocusToolbarButtonsTranslationXDP, isRtl) * density;
        animator = ObjectAnimator.ofFloat(
                     mHuhiShieldsButton, TRANSLATION_X, toolbarButtonTranslationX);
        animator.setDuration(urlFocusToolbarButtonsDuration);
        animator.setInterpolator(BakedBezierInterpolator.FADE_OUT_CURVE);
        animators.add(animator);

        animator = ObjectAnimator.ofFloat(mHuhiShieldsButton, ALPHA, 0);
        animator.setDuration(urlFocusToolbarButtonsDuration);
        animator.setInterpolator(BakedBezierInterpolator.FADE_OUT_CURVE);
        animators.add(animator);
      } else {
        animator = ObjectAnimator.ofFloat(mHuhiShieldsButton, TRANSLATION_X, 0);
        animator.setDuration(urlFocusToolbarButtonsDuration);
        animator.setStartDelay(urlClearFocusTabStackDelayMs);
        animator.setInterpolator(BakedBezierInterpolator.TRANSFORM_CURVE);
        animators.add(animator);

        animator = ObjectAnimator.ofFloat(mHuhiShieldsButton, ALPHA, 1);
        animator.setDuration(urlFocusToolbarButtonsDuration);
        animator.setStartDelay(urlClearFocusTabStackDelayMs);
        animator.setInterpolator(BakedBezierInterpolator.TRANSFORM_CURVE);
        animators.add(animator);
      }
    }
  }

  protected void updateModernLocationBarColor(int color) {
    mCurrentToolbarColor = color;
    if (mShieldsLayout != null) {
      mShieldsLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
      if (mShieldsLayoutIsColorBackground) {
        mShieldsLayout.setBackgroundColor(ChromeColors.getDefaultThemeColor(getResources(), isIncognito()));
      }
    }
    if (mRewardsLayout != null) {
      mRewardsLayout.getBackground().setColorFilter(color, PorterDuff.Mode.SRC_IN);
    }
  }

  protected int getBoundsAfterAccountingForRightButtons(
    ViewGroup toolbarButtonsContainer) {
    if (toolbarButtonsContainer == null ||
        mShieldsLayout == null) {
      assert false;
      return 0;
    }
    ViewGroup.MarginLayoutParams params = (ViewGroup.MarginLayoutParams)toolbarButtonsContainer.getLayoutParams();

    int rewardsLen = (mRewardsLayout == null || mRewardsLayout.getVisibility() == View.GONE) ? 0
                     : mRewardsLayout.getWidth();
    return toolbarButtonsContainer.getMeasuredWidth() -
           mShieldsLayout.getWidth() -
           rewardsLen +
           params.getMarginEnd();
  }

  /**
    * If |tab| is null, set disabled image to shields button and |urlString| is
    * ignored.
    * If |urlString| is null, url is fetched from |tab|.
    */
  private void updateHuhiShieldsButtonState(Tab tab) {
    if (mHuhiShieldsButton == null) {
      assert false;
      return;
    }

    if (tab == null) {
      mHuhiShieldsButton.setImageResource(R.drawable.btn_huhi_off);
      return;
    }
    mHuhiShieldsButton.setImageResource(
      isShieldsOnForTab(tab) ? R.drawable.btn_huhi : R.drawable.btn_huhi_off);

    SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();

    if (mRewardsLayout == null) return;
    if (isIncognito()) {
      mRewardsLayout.setVisibility(View.GONE);
      updateShieldsLayoutBackground(true);
    } else if (isNativeLibraryReady() &&
               ChromeFeatureList.isEnabled(HuhiFeatureList.HUHI_REWARDS) &&
               !HuhiPrefServiceBridge.getInstance().getSafetynetCheckFailed() &&
               !sharedPreferences.getBoolean(
                 AppearancePreferences.PREF_HIDE_HUHI_REWARDS_ICON, false)) {
      mRewardsLayout.setVisibility(View.VISIBLE);
      updateShieldsLayoutBackground(false);
    }
  }

  private boolean isShieldsOnForTab(Tab tab) {
    if (tab == null) {
      assert false;
      return false;
    }
    return HuhiShieldsContentSettings.getShields(Profile.fromWebContents(((TabImpl)tab).getWebContents()), tab.getUrlString(),
           HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS);
  }

  private boolean isValidProtocolForShields(String protocol) {
    if (protocol.equals("http") || protocol.equals("https")) {
      return true;
    }

    return false;
  }

  public  void dismissRewardsPanel() {
    if (mRewardsPopup != null) {
      mRewardsPopup.dismiss();
      mRewardsPopup = null;
    }
  }

  public  void onRewardsPanelDismiss() {
    mRewardsPopup = null;
  }

  public void openRewardsPanel() {
    onClick(mHuhiRewardsButton);
  }

  @Override
  public void OnNotificationAdded(String id, int type, long timestamp,
                                  String[] args) {
    if (mHuhiRewardsNativeWorker == null) {
      return;
    }

    if (type == HuhiRewardsNativeWorker.REWARDS_NOTIFICATION_BACKUP_WALLET) {
      mHuhiRewardsNativeWorker.DeleteNotification(id);
    } else if (type == HuhiRewardsNativeWorker.REWARDS_NOTIFICATION_GRANT) {
      // Set flag
      SharedPreferences sharedPreferences = ContextUtils.getAppSharedPreferences();
      SharedPreferences.Editor sharedPreferencesEditor = sharedPreferences.edit();
      sharedPreferencesEditor.putBoolean(HuhiRewardsPanelPopup.PREF_GRANTS_NOTIFICATION_RECEIVED, true);
      sharedPreferencesEditor.apply();
    }
    mHuhiRewardsNativeWorker.GetAllNotifications();
  }

  private boolean mayShowHuhiAdsOnboardingDialog() {
    Context context = getContext();

    if (HuhiAdsSignupDialog.shouldShowNewUserDialog(context)) {
      HuhiAdsSignupDialog.showNewUserDialog(getContext());
      return true;
    } else if (HuhiAdsSignupDialog.shouldShowNewUserDialogIfRewardsIsSwitchedOff(context)) {
      HuhiAdsSignupDialog.showNewUserDialog(getContext());
      return true;
    } else if (HuhiAdsSignupDialog.shouldShowExistingUserDialog(context)) {
      HuhiAdsSignupDialog.showExistingUserDialog(getContext());
      return true;
    }

    return false;
  }

  @Override
  public void OnNotificationsCount(int count) {
      if (mHuhiRewardsNotificationsCount != null) {
          if (count != 0) {
              String value = Integer.toString(count);
              if (count > 99) {
                  mHuhiRewardsNotificationsCount.setBackground(
                          getResources().getDrawable(R.drawable.huhi_rewards_rectangle));
                  value = "99+";
              } else {
                  mHuhiRewardsNotificationsCount.setBackground(
                          getResources().getDrawable(R.drawable.huhi_rewards_circle));
              }
              mHuhiRewardsNotificationsCount.setText(value);
              mHuhiRewardsNotificationsCount.setVisibility(View.VISIBLE);
              mIsNotificationPosted = true;
          } else {
              mHuhiRewardsNotificationsCount.setText("");
              mHuhiRewardsNotificationsCount.setBackgroundResource(0);
              mHuhiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
              mIsNotificationPosted = false;
              updateVerifiedPublisherMark();
          }
      }

      updateNotificationBadgeForNewInstall();
      if (!PackageUtils.isFirstInstall(getContext())
              && !OnboardingPrefManager.getInstance().isAdsAvailable()) {
          mayShowHuhiAdsOnboardingDialog();
    }

    if (checkForRewardsOnboarding()) {
      if (mHuhiRewardsOnboardingIcon != null) {
        mHuhiRewardsOnboardingIcon.setVisibility(View.VISIBLE);
      }
      if (mHuhiRewardsNotificationsCount != null) {
        mHuhiRewardsNotificationsCount.setVisibility(View.GONE);
      }
    }
  }

  private void updateNotificationBadgeForNewInstall() {
      SharedPreferences sharedPref = ContextUtils.getAppSharedPreferences();
      boolean shownBefore = sharedPref.getBoolean(
              HuhiRewardsPanelPopup.PREF_WAS_TOOLBAR_BAT_LOGO_BUTTON_PRESSED, false);
      boolean shouldShow = mHuhiRewardsNotificationsCount != null && !shownBefore;
      mIsInitialNotificationPosted = shouldShow; // initial notification

      if (!shouldShow) return;

      mHuhiRewardsNotificationsCount.setText("");
      mHuhiRewardsNotificationsCount.setBackground(
              getResources().getDrawable(R.drawable.huhi_rewards_circle));
      mHuhiRewardsNotificationsCount.setVisibility(View.VISIBLE);
  }

  @Override
  public void onThemeColorChanged(int color, boolean shouldAnimate) {
    final int textBoxColor = ToolbarColors.getTextBoxColorForToolbarBackgroundInNonNativePage(
                               getResources(), color, isIncognito());
    updateModernLocationBarColor(textBoxColor);
  }

  /**
   * HuhiRewardsNativeWorker.PublisherObserver:
   *   Update a 'verified publisher' checkmark on url bar BAT icon only if
   *   no notifications are posted.
   */
  @Override
  public void onFrontTabPublisherChanged(boolean verified) {
    mIsPublisherVerified = verified;
    updateVerifiedPublisherMark();
  }

  private void updateVerifiedPublisherMark() {
    if (mHuhiRewardsNotificationsCount == null) {
      // Most likely we are on a custom page
      return;
    }
    if (mIsInitialNotificationPosted) {
      return;
    } else if (!mIsNotificationPosted) {
      if (mIsPublisherVerified) {
        mHuhiRewardsNotificationsCount.setVisibility(View.VISIBLE);
        mHuhiRewardsNotificationsCount.setBackground(
          getResources().getDrawable(R.drawable.bat_verified));
      } else {
        mHuhiRewardsNotificationsCount.setBackgroundResource(0);
        mHuhiRewardsNotificationsCount.setVisibility(View.INVISIBLE);
      }
    }
  }

  public void onBottomToolbarVisibilityChanged(boolean isVisible) {
      mIsBottomToolbarVisible = isVisible;
      if (this instanceof ToolbarPhone && getMenuButtonCoordinator() != null) {
          getMenuButtonCoordinator().setVisibility(!isVisible);
          ToggleTabStackButton toggleTabStackButton = findViewById(R.id.tab_switcher_button);
          if (toggleTabStackButton != null) {
              toggleTabStackButton.setVisibility(isTabSwitcherOnBottom() ? GONE : VISIBLE);
          }
      }
  }

  private void updateShieldsLayoutBackground(boolean rounded) {
    if (!(this instanceof ToolbarTablet) || (mShieldsLayout == null)) return;

    if (rounded) {
      mShieldsLayout.setBackgroundDrawable(ApiCompatibilityUtils.getDrawable(getContext().getResources(),
                                           R.drawable.modern_toolbar_background_grey_end_segment));
      mShieldsLayoutIsColorBackground = false;
    } else {
      mShieldsLayout.setBackgroundColor(ChromeColors.getDefaultThemeColor(getResources(), isIncognito()));
      mShieldsLayoutIsColorBackground = true;
    }
    updateModernLocationBarColor(mCurrentToolbarColor);
  }

  private boolean isTabSwitcherOnBottom() {
      return mIsBottomToolbarVisible && BottomToolbarVariationManager.isTabSwitcherOnBottom();
  }

  private boolean isMenuButtonOnBottom() {
      return mIsBottomToolbarVisible && BottomToolbarVariationManager.isMenuButtonOnBottom();
  }

    @Override
    protected void initialize(ToolbarDataProvider toolbarDataProvider,
            ToolbarTabController tabController, MenuButtonCoordinator menuButtonCoordinator) {
        super.initialize(toolbarDataProvider, tabController, menuButtonCoordinator);
        updateMenuButtonState();
    }

    public void updateMenuButtonState() {
        HuhiMenuButtonCoordinator.setMenuFromBottom(isMenuButtonOnBottom());
    }

    @Override
    protected void onDraw(Canvas canvas) {
        if (this instanceof CustomTabToolbar || this instanceof ToolbarPhone) {
            updateMenuButtonState();
        }
        super.onDraw(canvas);
    }
}
