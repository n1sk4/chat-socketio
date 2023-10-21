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

## Screenshots
### User 1 creates a Chat room
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/93651be9-5465-47f8-8ea1-e35a450a6115 alt="drawing" width="500"/> \

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/1554b2f6-eba1-4e8c-bfc4-7951bca23026 alt="drawing" width="500"/>

### User 2 joins a Chat room
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/d9ae5d38-181c-4ba7-90d3-92b9c1fbce34 alt="drawing" width="500"/> \

<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/0991ad54-7a97-4983-a0e3-b0cb6df198ec alt="drawing" width="500"/>

### Chat and Exit
<img src=https://github.com/n1sk4/chat-socketio/assets/92214769/85645f99-21ae-4b7a-b830-f19dd6d8a41a alt="drawing" width="500"/>


# C++ Client
Createad a Socket.IO client using c++

The client only registers to the Server, then sends a single message and unregisters.


## Dependencies
Socket.IO library installed: [Installation instructions](https://github.com/socketio/socket.io-client-cpp/blob/master/README.md)

## Build using CMake
```
 mkdir build
 cd build
 cmake ..
 cmake --build . --target Client --config Release
```
