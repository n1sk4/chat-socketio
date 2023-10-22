package com.niksazupcic.android_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.google.android.material.textfield.TextInputEditText;

public class MainActivity extends AppCompatActivity {

    Button joinButton;
    TextInputEditText userName, roomName;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        findViewsById();
        defineJoinButton();
    }

    private void findViewsById(){
        joinButton = findViewById(R.id.joinRoom_Button);
        userName = findViewById(R.id.userName_textInputEditText);
        roomName = findViewById(R.id.roomName_textInputEditText);
    }

    private void defineJoinButton(){
        joinButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                //Go to chat room if exists
            }
        });
    }
}