/* Copyright (c) 2020 The Huhi Software Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Huhi Software
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

package org.chromium.chrome.browser.shields;

import android.animation.Animator;
import android.animation.Animator.AnimatorListener;
import android.animation.AnimatorListenerAdapter;
import android.animation.AnimatorSet;
import android.app.Activity;
import android.content.Context;
import android.content.ContextWrapper;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.Point;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.text.SpannableString;
import android.text.Spanned;
import android.text.method.LinkMovementMethod;
import android.text.style.ClickableSpan;
import android.text.style.ImageSpan;
import android.text.style.StyleSpan;
import android.view.ContextThemeWrapper;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.MotionEvent;
import android.view.Surface;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.TranslateAnimation;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.CompoundButton.OnCheckedChangeListener;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListPopupWindow;
import android.widget.PopupMenu;
import android.widget.PopupWindow;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Switch;
import android.widget.TextView;

import org.chromium.base.SysUtils;
import org.chromium.base.Log;
import org.chromium.base.task.AsyncTask;
import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiRewardsHelper;
import org.chromium.chrome.browser.HuhiRewardsNativeWorker;
import org.chromium.chrome.browser.night_mode.GlobalNightModeStateProviderHolder;
import org.chromium.chrome.browser.preferences.website.HuhiShieldsContentSettings;
import org.chromium.chrome.browser.profiles.Profile;
import org.chromium.chrome.browser.shields.HuhiShieldsMenuObserver;
import org.chromium.chrome.browser.shields.HuhiShieldsUtils;
import org.chromium.chrome.browser.tab.Tab;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

/**
 * Object responsible for handling the creation, showing, hiding of the HuhiShields menu.
 */
public class HuhiShieldsHandler implements HuhiRewardsHelper.LargeIconReadyCallback {

    private static class BlockersInfo {
        public BlockersInfo() {
            mAdsBlocked = 0;
            mTrackersBlocked = 0;
            mHTTPSUpgrades = 0;
            mScriptsBlocked = 0;
            mFingerprintsBlocked = 0;
        }

        public int mAdsBlocked;
        public int mTrackersBlocked;
        public int mHTTPSUpgrades;
        public int mScriptsBlocked;
        public int mFingerprintsBlocked;
    }

    private final Context mContext;
    private PopupWindow mPopupWindow;
    private AnimatorSet mMenuItemEnterAnimator;
    private HuhiShieldsMenuObserver mMenuObserver;
    private View mHardwareButtonMenuAnchor;
    private final Map<Integer, BlockersInfo> mTabsStat =
        Collections.synchronizedMap(new HashMap<Integer, BlockersInfo>());

    private Switch mHuhiShieldsBlockTrackersSwitch;
    private OnCheckedChangeListener mHuhiShieldsAdsTrackingChangeListener;
    private Switch mHuhiShieldsHTTPSEverywhereSwitch;
    private OnCheckedChangeListener mHuhiShieldsHTTPSEverywhereChangeListener;
    private Switch mHuhiShieldsBlockingScriptsSwitch;
    private OnCheckedChangeListener mHuhiShieldsBlockingScriptsChangeListener;

    private View mPopupView;
    private LinearLayout mMainLayout;
    private LinearLayout mSecondaryLayout;
    private LinearLayout mAboutLayout;
    private LinearLayout mToggleLayout;
    private LinearLayout mThankYouLayout;
    private LinearLayout mReportBrokenSiteLayout;
    private TextView mSiteBlockCounterText;
    private TextView mShieldsDownText;
    private TextView mSiteBrokenWarningText;
    private View mBottomDivider;
    private ImageView mToggleIcon;

    private HuhiRewardsNativeWorker mHuhiRewardsNativeWorker;
    private HuhiRewardsHelper mIconFetcher;

    private String mHost;
    private String mTitle;
    private int mTabId;
    private Profile mProfile;

    private static Context scanForActivity(Context cont) {
        if (cont == null)
            return null;
        else if (cont instanceof Activity)
            return cont;
        else if (cont instanceof ContextWrapper)
            return scanForActivity(((ContextWrapper)cont).getBaseContext());

        return cont;
    }

    /**
     * Constructs a HuhiShieldsHandler object.
     * @param context Context that is using the HuhiShieldsMenu.
     */
    public HuhiShieldsHandler(Context context) {
        mContext = scanForActivity(context);
        mHardwareButtonMenuAnchor = null;
        if (mContext != null) {
            mHardwareButtonMenuAnchor = ((Activity)mContext).findViewById(R.id.menu_anchor_stub);
        }
    }

    public void addStat(int tabId, String block_type, String subresource) {
        if (!mTabsStat.containsKey(tabId)) {
            mTabsStat.put(tabId, new BlockersInfo());
        }
        BlockersInfo blockersInfo = mTabsStat.get(tabId);
        if (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_ADS)) {
            blockersInfo.mAdsBlocked++;
        } else if (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_TRACKERS)) {
            blockersInfo.mTrackersBlocked++;
        } else if (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES)) {
            blockersInfo.mHTTPSUpgrades++;
        } else if (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_JAVASCRIPTS)) {
            blockersInfo.mScriptsBlocked++;
        } else if (block_type.equals(HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING)) {
            blockersInfo.mFingerprintsBlocked++;
        }
    }

    public void removeStat(int tabId) {
        if (!mTabsStat.containsKey(tabId)) {
            return;
        }
        mTabsStat.remove(tabId);
    }

    public void clearHuhiShieldsCount(int tabId) {
        mTabsStat.put(tabId, new BlockersInfo());
    }

    public void addObserver(HuhiShieldsMenuObserver menuObserver) {
        mMenuObserver = menuObserver;
    }

    public void show(View anchorView, Tab tab) {
        if (mHardwareButtonMenuAnchor == null) return;

        mHost = tab.getUrlString();
        mTitle = tab.getUrl().getHost();
        mTabId = tab.getId();
        mProfile = Profile.fromWebContents(tab.getWebContents());

        mHuhiRewardsNativeWorker = HuhiRewardsNativeWorker.getInstance();
        mIconFetcher = new HuhiRewardsHelper(tab);
        mPopupWindow = showPopupMenu(anchorView, false);

        updateValues(mTabId);
    }

    public PopupWindow showPopupMenu(View anchorView, boolean isTooltip) {
        int rotation = ((Activity)mContext).getWindowManager().getDefaultDisplay().getRotation();
        // This fixes the bug where the bottom of the menu starts at the top of
        // the keyboard, instead of overlapping the keyboard as it should.
        int displayHeight = mContext.getResources().getDisplayMetrics().heightPixels;
        int widthHeight = mContext.getResources().getDisplayMetrics().widthPixels;
        int currentDisplayWidth = widthHeight;

        // In appcompat 23.2.1, DisplayMetrics are not updated after rotation change. This is a
        // workaround for it. See crbug.com/599048.
        // TODO(ianwen): Remove the rotation check after we roll to 23.3.0.
        if (rotation == Surface.ROTATION_0 || rotation == Surface.ROTATION_180) {
            currentDisplayWidth = Math.min(displayHeight, widthHeight);
            displayHeight = Math.max(displayHeight, widthHeight);
        } else if (rotation == Surface.ROTATION_90 || rotation == Surface.ROTATION_270) {
            currentDisplayWidth = Math.max(displayHeight, widthHeight);
            displayHeight = Math.min(displayHeight, widthHeight);
        } else {
            assert false : "Rotation unexpected";
        }
        if (anchorView == null) {
            Rect rect = new Rect();
            ((Activity)mContext).getWindow().getDecorView().getWindowVisibleDisplayFrame(rect);
            int statusBarHeight = rect.top;
            mHardwareButtonMenuAnchor.setY((displayHeight - statusBarHeight));

            anchorView = mHardwareButtonMenuAnchor;
        }

        ContextThemeWrapper wrapper = new ContextThemeWrapper(mContext, R.style.OverflowMenuThemeOverlay);
        Point pt = new Point();
        ((Activity)mContext).getWindowManager().getDefaultDisplay().getSize(pt);
        // Get the height and width of the display.
        Rect appRect = new Rect();
        ((Activity)mContext).getWindow().getDecorView().getWindowVisibleDisplayFrame(appRect);

        // Use full size of window for abnormal appRect.
        if (appRect.left < 0 && appRect.top < 0) {
            appRect.left = 0;
            appRect.top = 0;
            appRect.right = ((Activity)mContext).getWindow().getDecorView().getWidth();
            appRect.bottom = ((Activity)mContext).getWindow().getDecorView().getHeight();
        }

        LayoutInflater inflater = (LayoutInflater) anchorView.getContext().getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        if (! isTooltip) {
            mPopupView = inflater.inflate(R.layout.huhi_shields_main_layout, null);
            setUpViews();
        } else {
            mPopupView = inflater.inflate(R.layout.huhi_shields_tooltip_layout, null);
        }

        //Specify the length and width through constants
        int width = (int)((mContext.getResources().getDisplayMetrics().widthPixels) * 0.75);
        int height = LinearLayout.LayoutParams.WRAP_CONTENT;

        //Make Inactive Items Outside Of PopupWindow
        boolean focusable = true;

        //Create a window with our parameters
        PopupWindow popupWindow = new PopupWindow(mPopupView, width, height, focusable);
        popupWindow.setBackgroundDrawable(new ColorDrawable(Color.WHITE));
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.LOLLIPOP) {
            popupWindow.setElevation(20);
        }
        // mPopup.setBackgroundDrawable(mContext.getResources().getDrawable(android.R.drawable.picture_frame));
        //Set the location of the window on the screen
        popupWindow.showAsDropDown(anchorView, 0, 0);
        popupWindow.setInputMethodMode(PopupWindow.INPUT_METHOD_NOT_NEEDED);
        popupWindow.setAnimationStyle(R.style.OverflowMenuAnim);

        // Turn off window animations for low end devices, and on Android M, which has built-in menu
        // animations.
        if (SysUtils.isLowEndDevice() || Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            popupWindow.setAnimationStyle(0);
        }

        Rect bgPadding = new Rect();
        popupWindow.getBackground().getPadding(bgPadding);

        int popupWidth = wrapper.getResources().getDimensionPixelSize(R.dimen.menu_width)
                         + bgPadding.left + bgPadding.right;

        popupWindow.setWidth(popupWidth);

        return popupWindow;
    }

    public void updateHost(String host) {
        mHost = host;
    }

    public void updateValues(int tabId) {
        if (!mTabsStat.containsKey(tabId)) {
            return;
        }
        BlockersInfo blockersInfo = mTabsStat.get(tabId);
        updateValues(blockersInfo.mAdsBlocked + blockersInfo.mTrackersBlocked,
                     blockersInfo.mHTTPSUpgrades, blockersInfo.mScriptsBlocked, blockersInfo.mFingerprintsBlocked);
    }

    public int getAdsBlockedCount(int tabId) {
        if (!mTabsStat.containsKey(tabId)) {
            return 0;
        }

        BlockersInfo blockersInfo = mTabsStat.get(tabId);
        return blockersInfo.mAdsBlocked;
    }

    public int getTackersBlockedCount(int tabId) {
        if (!mTabsStat.containsKey(tabId)) {
            return 0;
        }

        BlockersInfo blockersInfo = mTabsStat.get(tabId);
        return blockersInfo.mTrackersBlocked;
    }

    public void updateValues(int adsAndTrackers, int httpsUpgrades, int scriptsBlocked, int fingerprintsBlocked) {
        if (mContext == null) {
            return;
        }
        final int fadsAndTrackers = adsAndTrackers;
        final int fhttpsUpgrades = httpsUpgrades;
        final int fscriptsBlocked = scriptsBlocked;
        final int ffingerprintsBlocked = fingerprintsBlocked;
        ((Activity)mContext).runOnUiThread(new Runnable() {
            @Override
            public void run() {
                if (!isShowing()) {
                    return;
                }
                try {
                    mSiteBlockCounterText.setText(String.valueOf(fadsAndTrackers
                                                  + fhttpsUpgrades
                                                  + fscriptsBlocked
                                                  + ffingerprintsBlocked));
                } catch (NullPointerException exc) {
                    // It means that the Huhiry Panel was destroyed during the update, we just do nothing
                }
            }
        });
    }

    public boolean isShowing() {
        if (null == mPopupWindow) {
            return false;
        }

        return mPopupWindow.isShowing();
    }

    public void hideHuhiShieldsMenu() {
        if (isShowing()) {
            mPopupWindow.dismiss();
        }
    }

    private void initViews() {
        mMainLayout = mPopupView.findViewById(R.id.main_layout);
        mSecondaryLayout = mPopupView.findViewById(R.id.huhi_shields_secondary_layout_id);
        mAboutLayout = mPopupView.findViewById(R.id.huhi_shields_about_layout_id);
        mToggleLayout = mPopupView.findViewById(R.id.huhi_shields_toggle_layout_id);
        mSiteBlockCounterText = mPopupView.findViewById(R.id.site_block_count_text);
        mShieldsDownText = mPopupView.findViewById(R.id.shield_down_text);
        mSiteBrokenWarningText = mPopupView.findViewById(R.id.site_broken_warning_text);

        mReportBrokenSiteLayout = mPopupView.findViewById(R.id.huhi_shields_report_site_layout_id);
        mThankYouLayout = mPopupView.findViewById(R.id.huhi_shields_thank_you_layout_id);

        mBottomDivider = mToggleLayout.findViewById(R.id.bottom_divider);
        mToggleIcon = mToggleLayout.findViewById(R.id.toggle_favicon);
    }

    private void setUpMainLayout() {
        String favIconURL = mHuhiRewardsNativeWorker.GetPublisherFavIconURL(mTabId);
        Tab currentActiveTab = mIconFetcher.getTab();
        String url = currentActiveTab.getUrlString();
        final String favicon_url = (favIconURL.isEmpty()) ? url : favIconURL;
        mIconFetcher.retrieveLargeIcon(favicon_url, this);

        TextView mSiteText = mMainLayout.findViewById(R.id.site_text);
        mSiteText.setText(mTitle.replaceFirst("^(http[s]?://www\\.|http[s]?://|www\\.)", ""));

        Switch mShieldMainSwitch = mMainLayout.findViewById(R.id.site_switch);

        ClickableSpan mClickableSpan = new ClickableSpan() {
            @Override
            public void onClick(View widget) {
                mMainLayout.setVisibility(View.GONE);
                mAboutLayout.setVisibility(View.VISIBLE);
                setUpAboutLayout();
            }
        };

        TextView mSiteBlockText = mMainLayout.findViewById(R.id.site_block_text);
        mSiteBlockText.setMovementMethod(LinkMovementMethod.getInstance());
        String mBlockText = mContext.getResources().getString(R.string.ads_and_other_things_blocked) + "   ";
        SpannableString mSpannableString = new SpannableString(mBlockText);
        ImageSpan mImageSpan = new ImageSpan(mContext, R.drawable.ic_help);
        mSpannableString.setSpan(mImageSpan, mBlockText.length() - 1, mBlockText.length(), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        mSpannableString.setSpan(mClickableSpan, mSpannableString.getSpanStart(mImageSpan), mSpannableString.getSpanEnd(mImageSpan), Spanned.SPAN_EXCLUSIVE_EXCLUSIVE);
        mSiteBlockText.setText(mSpannableString);

        mToggleIcon.setColorFilter(mContext.getResources().getColor(R.color.shield_toggle_button_tint));
        mToggleLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                setToggleView(!mSecondaryLayout.isShown());
            }
        });

        setUpSecondaryLayout();

        setupMainSwitchClick(mShieldMainSwitch);
    }

    private void setToggleView(boolean shouldShow) {
        if (shouldShow) {
            mSecondaryLayout.setVisibility(View.VISIBLE);
            mBottomDivider.setVisibility(View.VISIBLE);
            mToggleIcon.setImageResource(R.drawable.ic_toggle_up);
        } else {
            mSecondaryLayout.setVisibility(View.GONE);
            mBottomDivider.setVisibility(View.GONE);
            mToggleIcon.setImageResource(R.drawable.ic_toggle_down);
        }
    }

    private void setUpSecondaryLayout() {
        TextView shieldsText = mSecondaryLayout.findViewById(R.id.huhi_shields_text);
        shieldsText.setText(mTitle.replaceFirst("^(http[s]?://www\\.|http[s]?://|www\\.)", ""));

        setUpSwitchLayouts();
        setUpCookiesLayout();
        setUpFingerprintingLayout();
    }

    private void setUpSwitchLayouts() {
        LinearLayout mBlockTrackersLayout = mSecondaryLayout.findViewById(R.id.huhi_shields_block_trackers_id);
        TextView mBlockTrackersText = mBlockTrackersLayout.findViewById(R.id.huhi_shields_switch_text);
        mHuhiShieldsBlockTrackersSwitch = mBlockTrackersLayout.findViewById(R.id.huhi_shields_switch);
        mBlockTrackersText.setText(R.string.huhi_shields_ads_and_trackers);
        setupAdsTrackingSwitchClick(mHuhiShieldsBlockTrackersSwitch);

        LinearLayout mUpgradeHttpsLayout = mSecondaryLayout.findViewById(R.id.huhi_shields_upgrade_https_id);
        TextView mUpgradeHttpsText = mUpgradeHttpsLayout.findViewById(R.id.huhi_shields_switch_text);
        mHuhiShieldsHTTPSEverywhereSwitch = mUpgradeHttpsLayout.findViewById(R.id.huhi_shields_switch);
        mUpgradeHttpsText.setText(R.string.huhi_shields_https_everywhere_switch);
        setupHTTPSEverywhereSwitchClick(mHuhiShieldsHTTPSEverywhereSwitch);

        LinearLayout mBlockScriptsLayout = mSecondaryLayout.findViewById(R.id.huhi_shields_block_scripts_id);
        TextView mBlockScriptsText = mBlockScriptsLayout.findViewById(R.id.huhi_shields_switch_text);
        mHuhiShieldsBlockingScriptsSwitch = mBlockScriptsLayout.findViewById(R.id.huhi_shields_switch);
        mBlockScriptsText.setText(R.string.huhi_shields_blocks_scripts_switch);
        setupBlockingScriptsSwitchClick(mHuhiShieldsBlockingScriptsSwitch);
    }

    private void setUpCookiesLayout() {
        LinearLayout mBlockCookiesLayout = mPopupView.findViewById(R.id.huhi_shields_block_cookies_layout_id);
        TextView mCookiesOptionTitle = mBlockCookiesLayout.findViewById(R.id.option_title);
        mCookiesOptionTitle.setText(R.string.block_cookies);
        TextView mCookiesOptionText = mBlockCookiesLayout.findViewById(R.id.option_text);
        mCookiesOptionText.setText(R.string.block_cookies_text);
        RadioButton mCookiesOption1 = mBlockCookiesLayout.findViewById(R.id.option1);
        mCookiesOption1.setText(R.string.block_cookies_option_1);
        RadioButton mCookiesOption2 = mBlockCookiesLayout.findViewById(R.id.option2);
        mCookiesOption2.setText(R.string.block_cross_site_cookies);
        RadioButton mCookiesOption3 = mBlockCookiesLayout.findViewById(R.id.option3);
        mCookiesOption3.setText(R.string.block_cookies_option_3);
        Button mCookiesDoneButton = mBlockCookiesLayout.findViewById(R.id.done_button);
        mCookiesDoneButton.setOnClickListener(mDoneClickListener);
        ImageView mCookiesBackButton = mBlockCookiesLayout.findViewById(R.id.back_button);
        mCookiesBackButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mBlockCookiesLayout.setVisibility(View.GONE);
                mMainLayout.setVisibility(View.VISIBLE);
            }
        });

        LinearLayout mCookiesLayout = mSecondaryLayout.findViewById(R.id.huhi_shields_cookies_layout_id);
        mCookiesLayout.setBackground(null);
        mCookiesLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mMainLayout.setVisibility(View.GONE);
                mBlockCookiesLayout.setVisibility(View.VISIBLE);
            }
        });
        ImageView mCookiesIcon = mCookiesLayout.findViewById(R.id.toggle_favicon);
        mCookiesIcon.setImageResource(R.drawable.ic_chevron_right);
        mCookiesIcon.setColorFilter(mContext.getResources().getColor(R.color.default_icon_color_tint_list));
        TextView mCookiesText = mCookiesLayout.findViewById(R.id.toggle_text);
        mCookiesText.setText(R.string.block_cookies);

        String settingOption = HuhiShieldsContentSettings.getShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_COOKIES);
        if (settingOption.equals(HuhiShieldsContentSettings.BLOCK_RESOURCE)) {
            mCookiesOption1.setChecked(true);
        } else if (settingOption.equals(HuhiShieldsContentSettings.BLOCK_THIRDPARTY_RESOURCE)) {
            mCookiesOption2.setChecked(true);
        } else if (settingOption.equals(HuhiShieldsContentSettings.ALLOW_RESOURCE)) {
            mCookiesOption3.setChecked(true);
        }

        RadioGroup mCookiesOptionGroup = mBlockCookiesLayout.findViewById(R.id.options_radio_group);
        mCookiesOptionGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton checkedRadioButton = (RadioButton)group.findViewById(checkedId);
                boolean isChecked = checkedRadioButton.isChecked();

                if (isChecked) {
                    if (checkedId == R.id.option1) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_COOKIES, HuhiShieldsContentSettings.BLOCK_RESOURCE, false);
                    } else if (checkedId == R.id.option2) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_COOKIES, HuhiShieldsContentSettings.BLOCK_THIRDPARTY_RESOURCE, false);
                    } else if (checkedId == R.id.option3) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_COOKIES, HuhiShieldsContentSettings.ALLOW_RESOURCE, false);
                    }
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, false);
                    }
                }
            }
        });
    }

    private void setUpFingerprintingLayout() {
        LinearLayout mBlockFingerPrintingLayout = mPopupView.findViewById(R.id.huhi_shields_block_fingerprinting_layout_id);
        TextView mFingerprintingOptionTitle = mBlockFingerPrintingLayout.findViewById(R.id.option_title);
        mFingerprintingOptionTitle.setText(R.string.block_fingerprinting);
        TextView mFingerprintingOptionText = mBlockFingerPrintingLayout.findViewById(R.id.option_text);
        mFingerprintingOptionText.setText(R.string.block_fingerprinting_text);
        RadioButton mFingerprintingOption1 = mBlockFingerPrintingLayout.findViewById(R.id.option1);
        mFingerprintingOption1.setText(R.string.block_fingerprinting_option_1);
        RadioButton mFingerprintingOption2 = mBlockFingerPrintingLayout.findViewById(R.id.option2);
        mFingerprintingOption2.setText(R.string.block_fingerprinting_option_2);
        RadioButton mFingerprintingOption3 = mBlockFingerPrintingLayout.findViewById(R.id.option3);
        mFingerprintingOption3.setText(R.string.block_fingerprinting_option_3);
        Button mFingerprintingDoneButton = mBlockFingerPrintingLayout.findViewById(R.id.done_button);
        mFingerprintingDoneButton.setOnClickListener(mDoneClickListener);
        ImageView mFingerprintingBackButton = mBlockFingerPrintingLayout.findViewById(R.id.back_button);
        mFingerprintingBackButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mBlockFingerPrintingLayout.setVisibility(View.GONE);
                mMainLayout.setVisibility(View.VISIBLE);
            }
        });

        LinearLayout mFingerPrintingLayout = mSecondaryLayout.findViewById(R.id.huhi_shields_fingerprinting_layout_id);
        mFingerPrintingLayout.setBackground(null);
        mFingerPrintingLayout.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mMainLayout.setVisibility(View.GONE);
                mBlockFingerPrintingLayout.setVisibility(View.VISIBLE);
            }
        });
        ImageView mFingerPrintingIcon = mFingerPrintingLayout.findViewById(R.id.toggle_favicon);
        mFingerPrintingIcon.setImageResource(R.drawable.ic_chevron_right);
        mFingerPrintingIcon.setColorFilter(mContext.getResources().getColor(R.color.default_icon_color_tint_list));
        TextView mFingerPrintingText = mFingerPrintingLayout.findViewById(R.id.toggle_text);
        mFingerPrintingText.setText(R.string.block_fingerprinting);

        String settingOption = HuhiShieldsContentSettings.getShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING);
        if (settingOption.equals(HuhiShieldsContentSettings.BLOCK_RESOURCE)) {
            mFingerprintingOption1.setChecked(true);
        } else if (settingOption.equals(HuhiShieldsContentSettings.DEFAULT)) {
            mFingerprintingOption2.setChecked(true);
        } else if (settingOption.equals(HuhiShieldsContentSettings.ALLOW_RESOURCE)) {
            mFingerprintingOption3.setChecked(true);
        }

        RadioGroup mFingerprintingOptionGroup = mBlockFingerPrintingLayout.findViewById(R.id.options_radio_group);
        mFingerprintingOptionGroup.setOnCheckedChangeListener(new RadioGroup.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(RadioGroup group, int checkedId) {
                RadioButton checkedRadioButton = (RadioButton)group.findViewById(checkedId);
                boolean isChecked = checkedRadioButton.isChecked();

                if (isChecked) {
                    if (checkedId == R.id.option1) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING, HuhiShieldsContentSettings.BLOCK_RESOURCE, false);
                    } else if (checkedId == R.id.option2) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING, HuhiShieldsContentSettings.DEFAULT, false);
                    } else if (checkedId == R.id.option3) {
                        HuhiShieldsContentSettings.setShieldsValue(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_FINGERPRINTING, HuhiShieldsContentSettings.ALLOW_RESOURCE, false);
                    }
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, false);
                    }
                }
            }
        });
    }

    private void setUpAboutLayout() {
        TextView mAboutText = mAboutLayout.findViewById(R.id.about_text);
        mAboutText.setVisibility(View.VISIBLE);
        TextView mOptionTitle = mAboutLayout.findViewById(R.id.option_title);
        mOptionTitle.setText(R.string.about_huhi_shields_text);
        TextView mOptionText = mAboutLayout.findViewById(R.id.option_text);
        mOptionText.setVisibility(View.GONE);
        RadioGroup mOptionGroup = mAboutLayout.findViewById(R.id.options_radio_group);
        mOptionGroup.setVisibility(View.GONE);
        Button mDoneButton = mAboutLayout.findViewById(R.id.done_button);
        mDoneButton.setOnClickListener(mDoneClickListener);
        ImageView mBackButton = mAboutLayout.findViewById(R.id.back_button);
        mBackButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mAboutLayout.setVisibility(View.GONE);
                mMainLayout.setVisibility(View.VISIBLE);
            }
        });
    }

    private void setUpReportBrokenSiteLayout() {
        TextView mReportSiteUrlText = mReportBrokenSiteLayout.findViewById(R.id.report_site_url);
        mReportSiteUrlText.setText(mTitle);

        Button mCancelButton = mReportBrokenSiteLayout.findViewById(R.id.btn_cancel);
        mCancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                hideHuhiShieldsMenu();
            }
        });

        Button mSubmitButton = mReportBrokenSiteLayout.findViewById(R.id.btn_submit);
        mSubmitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                HuhiShieldsUtils.HuhiShieldsWorkerTask mWorkerTask = new HuhiShieldsUtils.HuhiShieldsWorkerTask(mTitle);
                mWorkerTask.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR);
                mReportBrokenSiteLayout.setVisibility(View.GONE);
                mThankYouLayout.setVisibility(View.VISIBLE);
            }
        });
    }

    private void setUpMainSwitchLayout(boolean isChecked) {
        TextView mShieldDownText = mMainLayout.findViewById(R.id.shield_down_text);
        Button mReportBrokenSiteButton = mMainLayout.findViewById(R.id.btn_report_broken_site);
        mReportBrokenSiteButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                mMainLayout.setVisibility(View.GONE);
                mReportBrokenSiteLayout.setVisibility(View.VISIBLE);
                setUpReportBrokenSiteLayout();
            }
        });

        LinearLayout mSiteBlockLayout = mMainLayout.findViewById(R.id.site_block_layout);
        TextView mSiteBrokenWarningText = mMainLayout.findViewById(R.id.site_broken_warning_text);

        TextView mShieldsUpText = mMainLayout.findViewById(R.id.shield_up_text);
        String mHuhiShieldsText = mContext.getResources().getString(R.string.huhi_shields_onboarding_title);

        if (isChecked) {
            mShieldDownText.setVisibility(View.GONE);
            mReportBrokenSiteButton.setVisibility(View.GONE);

            mSiteBlockLayout.setVisibility(View.VISIBLE);
            mSiteBrokenWarningText.setVisibility(View.VISIBLE);
            mToggleLayout.setVisibility(View.VISIBLE);

            String mUpText = mContext.getResources().getString(R.string.up);
            SpannableString mSpanString = new SpannableString(mHuhiShieldsText + " " + mUpText);
            mSpanString.setSpan(new StyleSpan(Typeface.BOLD), mSpanString.length() - mUpText.length(), mSpanString.length(), 0);
            mShieldsUpText.setText(mSpanString);
        } else {
            mShieldDownText.setVisibility(View.VISIBLE);
            mReportBrokenSiteButton.setVisibility(View.VISIBLE);

            mSiteBlockLayout.setVisibility(View.GONE);
            mSiteBrokenWarningText.setVisibility(View.GONE);
            mToggleLayout.setVisibility(View.GONE);
            setToggleView(false);

            String mDownText = mContext.getResources().getString(R.string.down);
            SpannableString mSpanString = new SpannableString(mHuhiShieldsText + " " + mDownText);
            mSpanString.setSpan(new StyleSpan(Typeface.BOLD), mSpanString.length() - mDownText.length(), mSpanString.length(), 0);
            mShieldsUpText.setText(mSpanString);
        }
    }

    private void setUpViews() {
        boolean isNightMode = GlobalNightModeStateProviderHolder.getInstance().isInNightMode();

        initViews();

        setUpMainLayout();
    }

    private void setupAdsTrackingSwitchClick(Switch huhiShieldsAdsTrackingSwitch) {
        if (null == huhiShieldsAdsTrackingSwitch) {
            return;
        }
        setupAdsTrackingSwitch(huhiShieldsAdsTrackingSwitch, false);

        mHuhiShieldsAdsTrackingChangeListener = new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                if (0 != mHost.length()) {
                    HuhiShieldsContentSettings.setShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_ADS_TRACKERS, isChecked, false);
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, false);
                    }
                }
            }
        };

        huhiShieldsAdsTrackingSwitch.setOnCheckedChangeListener(mHuhiShieldsAdsTrackingChangeListener);
    }

    private void setupAdsTrackingSwitch(Switch huhiShieldsAdsTrackingSwitch, boolean fromTopSwitch) {
        if (null == huhiShieldsAdsTrackingSwitch) {
            return;
        }
        if (fromTopSwitch) {
            // Prevents to fire an event when top shields changed
            huhiShieldsAdsTrackingSwitch.setOnCheckedChangeListener(null);
        }
        if (0 != mHost.length()) {
            if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
                if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_ADS_TRACKERS)) {
                    huhiShieldsAdsTrackingSwitch.setChecked(true);
                } else {
                    huhiShieldsAdsTrackingSwitch.setChecked(false);
                }
                huhiShieldsAdsTrackingSwitch.setEnabled(true);
            } else {
                huhiShieldsAdsTrackingSwitch.setChecked(false);
                huhiShieldsAdsTrackingSwitch.setEnabled(false);
            }
        }
        if (fromTopSwitch) {
            huhiShieldsAdsTrackingSwitch.setOnCheckedChangeListener(mHuhiShieldsAdsTrackingChangeListener);
        }
    }

    private void setupHTTPSEverywhereSwitchClick(Switch huhiShieldsHTTPSEverywhereSwitch) {
        if (null == huhiShieldsHTTPSEverywhereSwitch) {
            return;
        }
        setupHTTPSEverywhereSwitch(huhiShieldsHTTPSEverywhereSwitch, false);

        mHuhiShieldsHTTPSEverywhereChangeListener = new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                if (0 != mHost.length()) {
                    HuhiShieldsContentSettings.setShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES, isChecked, false);
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, false);
                    }
                }
            }
        };

        huhiShieldsHTTPSEverywhereSwitch.setOnCheckedChangeListener(mHuhiShieldsHTTPSEverywhereChangeListener);
    }

    private void setupHTTPSEverywhereSwitch(Switch huhiShieldsHTTPSEverywhereSwitch, boolean fromTopSwitch) {
        if (null == huhiShieldsHTTPSEverywhereSwitch) {
            return;
        }
        if (fromTopSwitch) {
            // Prevents to fire an event when top shields changed
            huhiShieldsHTTPSEverywhereSwitch.setOnCheckedChangeListener(null);
        }
        if (0 != mHost.length()) {
            if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
                if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HTTP_UPGRADABLE_RESOURCES)) {
                    huhiShieldsHTTPSEverywhereSwitch.setChecked(true);
                } else {
                    huhiShieldsHTTPSEverywhereSwitch.setChecked(false);
                }
                huhiShieldsHTTPSEverywhereSwitch.setEnabled(true);
            } else {
                huhiShieldsHTTPSEverywhereSwitch.setChecked(false);
                huhiShieldsHTTPSEverywhereSwitch.setEnabled(false);
            }
        }
        if (fromTopSwitch) {
            huhiShieldsHTTPSEverywhereSwitch.setOnCheckedChangeListener(mHuhiShieldsHTTPSEverywhereChangeListener);
        }
    }

    private void setupBlockingScriptsSwitchClick(Switch huhiShieldsBlockingScriptsSwitch) {
        if (null == huhiShieldsBlockingScriptsSwitch) {
            return;
        }
        setupBlockingScriptsSwitch(huhiShieldsBlockingScriptsSwitch, false);

        mHuhiShieldsBlockingScriptsChangeListener = new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                if (0 != mHost.length()) {
                    HuhiShieldsContentSettings.setShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_JAVASCRIPTS, isChecked, false);
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, false);
                    }
                }
            }
        };

        huhiShieldsBlockingScriptsSwitch.setOnCheckedChangeListener(mHuhiShieldsBlockingScriptsChangeListener);
    }

    private void setupBlockingScriptsSwitch(Switch huhiShieldsBlockingScriptsSwitch, boolean fromTopSwitch) {
        if (null == huhiShieldsBlockingScriptsSwitch) {
            return;
        }
        if (fromTopSwitch) {
            // Prevents to fire an event when top shields changed
            huhiShieldsBlockingScriptsSwitch.setOnCheckedChangeListener(null);
        }
        if (0 != mHost.length()) {
            if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
                if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_JAVASCRIPTS)) {
                    huhiShieldsBlockingScriptsSwitch.setChecked(true);
                } else {
                    huhiShieldsBlockingScriptsSwitch.setChecked(false);
                }
                huhiShieldsBlockingScriptsSwitch.setEnabled(true);
            } else {
                huhiShieldsBlockingScriptsSwitch.setChecked(false);
                huhiShieldsBlockingScriptsSwitch.setEnabled(false);
            }
        }
        if (fromTopSwitch) {
            huhiShieldsBlockingScriptsSwitch.setOnCheckedChangeListener(mHuhiShieldsBlockingScriptsChangeListener);
        }
    }

    private void setupMainSwitchClick(Switch huhiShieldsSwitch) {
        if (null == huhiShieldsSwitch) {
            return;
        }
        if (0 != mHost.length()) {
            if (HuhiShieldsContentSettings.getShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS)) {
                huhiShieldsSwitch.setChecked(true);
                setUpMainSwitchLayout(true);
            } else {
                huhiShieldsSwitch.setChecked(false);
                setUpMainSwitchLayout(false);
            }
        }
        huhiShieldsSwitch.setOnCheckedChangeListener(new OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton buttonView,
                                         boolean isChecked) {
                if (0 != mHost.length()) {
                    HuhiShieldsContentSettings.setShields(mProfile, mHost, HuhiShieldsContentSettings.RESOURCE_IDENTIFIER_HUHI_SHIELDS, isChecked, false);
                    setupAdsTrackingSwitch(mHuhiShieldsBlockTrackersSwitch, true);
                    setupHTTPSEverywhereSwitch(mHuhiShieldsHTTPSEverywhereSwitch, true);
                    setupBlockingScriptsSwitch(mHuhiShieldsBlockingScriptsSwitch, true);
                    if (null != mMenuObserver) {
                        mMenuObserver.onMenuTopShieldsChanged(isChecked, true);
                    }
                }

                setUpMainSwitchLayout(isChecked);
            }
        });
    }

    @Override
    public void onLargeIconReady(Bitmap icon) {
        SetFavIcon(icon);
    }


    private void SetFavIcon(Bitmap bmp) {
        if (bmp != null) {
            ((Activity)mContext).runOnUiThread(
            new Runnable() {
                @Override
                public void run() {
                    ImageView iv = (ImageView) mPopupView.findViewById(R.id.site_favicon);
                    iv.setImageBitmap(HuhiRewardsHelper.getCircularBitmap(bmp));
                }
            });
        }
    }

    private View.OnClickListener mDoneClickListener = new View.OnClickListener() {
        @Override
        public void onClick(View view) {
            hideHuhiShieldsMenu();
        }
    };
}