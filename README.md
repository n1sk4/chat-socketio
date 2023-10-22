# chat-socketio
Chat App with Socket.IO

# Python Server
Createad a Socket.IO server using Flask

## Dependencies
Python 3.11 installed

Using VS Code:
```
 pip install Flask
 pip install flask-socketio
```
## Start Virtual Environment

```
  py -3 -m venv .venv
  .venv\Scripts\activate
```

## Screenshots
### User 1 creates a Chat room
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/93651be9-5465-47f8-8ea1-e35a450a6115 alt="drawing" width="500"/>\

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/1554b2f6-eba1-4e8c-bfc4-7951bca23026 alt="drawing" width="500"/>

### User 2 joins a Chat room
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/d9ae5d38-181c-4ba7-90d3-92b9c1fbce34 alt="drawing" width="500"/>\

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/0991ad54-7a97-4983-a0e3-b0cb6df198ec alt="drawing" width="500"/>

### Chat and Exit
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/85645f99-21ae-4b7a-b830-f19dd6d8a41a alt="drawing" width="500"/>


# C++ Client
Createad a Socket.IO client using c++

The client registers to the Python server. Then we're prompted to state the User name and Room ID.
If the Room ID is available, we join the room and we can chat.

## Dependencies
Socket.IO library installed: [Installation instructions](https://github.com/socketio/socket.io-client-cpp/blob/master/README.md)

## Build using CMake
```
 mkdir build
 cd build
 cmake ..
 cmake --build . --target Client --config Release
```

## Screenshots
### User 1 creates a Chat room

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/efabfa72-8f6e-4f6c-8164-7c1963d8db17 alt="drawing" width="500"/>\

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/8265a813-0f13-45ec-83ae-b88dfcfae321 alt="drawing" width="500"/>

### User 2 joins the Chat room

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/459af6d4-38a0-43a1-85a3-f361b603eabd alt="drawing" width="500"/>

### User 2 sends a message

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/83a17086-b132-4ac6-86bb-6527fb523c18 alt="drawing" width="500"/>


# Android Client
Createad a Socket.IO client using Android Native (Java)

The client registers to the Python server. Then we're prompted to state the User name and Room ID.
If the Room ID is available, we join the room and we can chat.

## Dependencies
Socket.IO instructions: [Socket.IO Java client](https://socketio.github.io/socket.io-client-java/android.html)\
Socket.IO Java Client: [Socket.IO Installation](https://socketio.github.io/socket.io-client-java/installation.html)\
Socket.IO Java Client Remote GIT: [socket.io-client-java](https://github.com/socketio/socket.io-client-java)

Maven:
Add the following dependency to your pom.xml
```
<dependencies>
  <dependency>
    <groupId>io.socket</groupId>
    <artifactId>socket.io-client</artifactId>
    <version>2.1.0</version>
  </dependency>
</dependencies>
}
```

Gradle:
Add the following dependency to your build.gradle
```
implementation ('io.socket:socket.io-client:2.1.0') {
  // excluding org.json which is provided by Android
  exclude group: 'org.json', module: 'json'
}
```

## Build using Android Studio

## Screenshots


