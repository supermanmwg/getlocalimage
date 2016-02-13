package com.example.weiguangmeng.activitytest;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import com.example.weiguangmeng.activitytest.base.BaseActivity;

public class MainActivity extends BaseActivity {
    private static final String EXTRA_DATA = "extra_data";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewById(R.id.go_to_next).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startActivity(new Intent(MainActivity.this, SecondActivity.class));
            }
        });
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        logger.log("OnSaveInstance");
        outState.putString(EXTRA_DATA, "test");
    }

    @Override
    protected void onRestoreInstanceState(Bundle savedInstanceState) {
        super.onRestoreInstanceState(savedInstanceState);
        logger.log("onRestoreInstanceState" + ", Extra data is " + savedInstanceState.get(EXTRA_DATA));
    }
}
