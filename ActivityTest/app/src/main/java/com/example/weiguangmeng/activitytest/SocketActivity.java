package com.example.weiguangmeng.activitytest;

import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.example.weiguangmeng.activitytest.base.BaseActivity;

/**
 * Created by weiguangmeng on 16/2/13.
 */
public class SocketActivity extends BaseActivity{

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        setContentView(R.layout.socket);

        findViewById(R.id.server).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        setServerSocket();
                    }
                }).start();
            }
        });

        findViewById(R.id.client).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        setClientSocket();
                    }
                }).start();
            }
        });
    }

    /* A native method that is implemented by the
     * 'hello-jni' native library, which is packaged
     * with this application.
     */
    public native String stringFromJNI();

    public native void setClientSocket();

    public native void setServerSocket();

    static {
        System.loadLibrary("hello-jni");
    }
}
