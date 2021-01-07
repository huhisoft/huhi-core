/** Copyright (c) 2020 The Huhi Authors. All rights reserved.
  * This Source Code Form is subject to the terms of the Mozilla Public
  * License, v. 2.0. If a copy of the MPL was not distributed with this file,
  * You can obtain one at http://mozilla.org/MPL/2.0/.
  */

package org.chromium.chrome.browser;

import android.content.Intent;
import android.os.Bundle;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import androidx.appcompat.app.ActionBar;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;

import org.chromium.chrome.R;
import org.chromium.chrome.browser.HuhiRewardsBalance;
import org.chromium.chrome.browser.HuhiRewardsExternalWallet;
import org.chromium.chrome.browser.HuhiRewardsNativeWorker;
import org.chromium.chrome.browser.app.HuhiActivity;

public class HuhiRewardsUserWalletActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.user_wallet_activity);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        ActionBar ab = getSupportActionBar();
        ab.setDisplayHomeAsUpEnabled(true);
        ab.setDisplayShowTitleEnabled(false);

        SetUIControls();
    }

    private void SetUIControls() {
        Intent intent = getIntent();
        final int status = intent.getIntExtra(
                HuhiRewardsExternalWallet.STATUS, -1);
        TextView txtUserId = (TextView)findViewById(R.id.user_id);
        TextView txtUserStatus = (TextView)findViewById(R.id.user_status);
        Button btn1 = (Button)findViewById(R.id.user_wallet_btn1);
        Button btn2 = null;
        Button btnGotoUphold = (Button)findViewById(
                R.id.user_wallet_go_to_uphold);

        if (status < HuhiRewardsExternalWallet.NOT_CONNECTED ||
                status > HuhiRewardsExternalWallet.PENDING) {
            finish();
        }
        else if (status == HuhiRewardsExternalWallet.VERIFIED){
          //set 2nd button visible
          findViewById(R.id.user_wallet_btn2_separator).setVisibility(
                  View.VISIBLE);
          btn2 = (Button)findViewById(R.id.user_wallet_btn2);
          btn2.setVisibility(View.VISIBLE);

          //Buttons:
          //Add funds
          //Withdraw
          //Go to uphold
          //Disconnect
          btn1.setText(getResources().getString(
                  R.string.huhi_rewards_local_panel_add_funds));
          btn2.setText(getResources().getString(
                  R.string.user_wallet_withdraw_funds));
          txtUserStatus.setText(
                  HuhiRewardsExternalWallet.WalletStatusToString(status));

          SetBtnOpenUrlClickHandler(btn1,
                  intent.getStringExtra(HuhiRewardsExternalWallet.ADD_URL));
          SetBtnOpenUrlClickHandler(btn2,
                  intent.getStringExtra(HuhiRewardsExternalWallet.WITHDRAW_URL));
        }
        else {
          //CONNECTED or PENDING
          //Buttons:
          //Complete verification
          //Go to uphold
          //Disconnect
          btn1.setText(getResources().getString(
                  R.string.user_wallet_complete_verification));
          SetBtnOpenUrlClickHandler(btn1,
                  intent.getStringExtra(HuhiRewardsExternalWallet.VERIFY_URL));
        }

        SetBtnOpenUrlClickHandler(btnGotoUphold,
                  intent.getStringExtra(HuhiRewardsExternalWallet.ACCOUNT_URL));

        String userId = intent.getStringExtra(HuhiRewardsExternalWallet.USER_NAME);
        txtUserId.setText(userId);
        SetDisconnectBtnClickHandler();
    }

    private void SetBtnOpenUrlClickHandler(Button btn, String url) {
      btn.setOnClickListener( (View v) -> {
              Intent intent = new Intent();
              intent.putExtra(HuhiActivity.OPEN_URL, url);
              setResult(RESULT_OK, intent);
              finish();
      });
    }

    private void SetDisconnectBtnClickHandler() {
        Button btnDisconnect = (Button)findViewById(
                R.id.user_wallet_disconnect);
        btnDisconnect.setOnClickListener( (View v) -> {
            HuhiRewardsNativeWorker.getInstance().DisconnectWallet
                    (HuhiRewardsBalance.WALLET_UPHOLD);
            Intent intent = new Intent();
            setResult(RESULT_OK, intent);
            finish();
      });
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        if(item.getItemId()==android.R.id.home) {
            finish();
        }
        return super.onOptionsItemSelected(item);
    }
}
