package ru.wohlsoft.helezhe;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button numChipsPlus = (Button) findViewById(R.id.hele);
        numChipsPlus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                String o = stringFromJNI();
                TextView cbl = (TextView) findViewById(R.id.woHeleZhe);
                cbl.setText(o);
            }
        });

        initLua();
    }

    public static native String stringFromJNI();
    public static native void initLua();

    static {
        System.loadLibrary("helezhe-jni");
    }
}
