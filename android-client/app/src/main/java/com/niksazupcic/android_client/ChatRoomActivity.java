package com.niksazupcic.android_client;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.Button;

import com.google.android.material.textfield.TextInputEditText;

public class ChatRoomActivity extends AppCompatActivity {

    Button sendButton;
    TextInputEditText message;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_chat_room);

        findViewsById();
    }

    private void findViewsById(){
        sendButton = findViewById(R.id.send_Button);
        message = findViewById(R.id.message_textInputEditText);
    }
}