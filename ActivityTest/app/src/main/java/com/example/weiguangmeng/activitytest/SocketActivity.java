package com.example.weiguangmeng.activitytest;

import android.os.Bundle;
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
        TextView tv = new TextView(this);
        tv.setText( stringFromJNI() );
        setContentView(tv);
    }

    /* A native method that is implemented by the
     * 'hello-jni' native library, which is packaged
     * with this application.
     */
    public native String stringFromJNI();


    static {
        System.loadLibrary("hello-jni");
    }
}
