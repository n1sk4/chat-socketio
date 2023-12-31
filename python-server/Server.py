from flask import Flask, render_template, request, session, redirect, url_for
from flask_socketio import join_room, leave_room, send, SocketIO
import random
from string import ascii_uppercase
import json

app = Flask(__name__)
app.config["SECRET_KEY"] = "hjhjsdahhds"
socketio = SocketIO(app)

rooms = {}

def generate_unique_code(length):
    while True:
        code = ""
        for _ in range(length):
            code += random.choice(ascii_uppercase)
        
        if code not in rooms:
            break
    
    return code

@app.route("/", methods=["POST", "GET"])
def home():
    session.clear()
    if request.method == "POST":
        name = request.form.get("name")
        code = request.form.get("code")
        join = request.form.get("join", False)
        create = request.form.get("create", False)
        room_name = request.form.get("room_name")

        if not name:
            return render_template("home.html", error="Please enter a name.", rooms=rooms, code=code, name=name, room_name=room_name)

        if join != False and not code:
            return render_template("home.html", error="Please enter a room code.", rooms=rooms, code=code, name=name, room_name=room_name)
        
        room = code
        if create != False:
            if not room_name:
              room = generate_unique_code(4)
            else:
              room = room_name

            rooms[room] = {"members": 0, "messages": []}
        elif code not in rooms:
            return render_template("home.html", error="Room does not exist.", rooms=rooms, code=code, name=name, room_name=room_name)
        
        session["room"] = room
        session["name"] = name
        return redirect(url_for("room"))

    return render_template("home.html", rooms=rooms)

@app.route("/room")
def room():
    room = session.get("room")
    if room is None or session.get("name") is None or room not in rooms:
        return redirect(url_for("home"))

    return render_template("room.html", code=room, messages=rooms[room]["messages"])

@socketio.on("message")
def message(data):
    client = False
    if 'client' in data:
        client = True

    if client:
        room = data["room"]
        name = data["name"]
    else:
        room = session.get("room")
        name = session.get("name")

    message = data["data"]

    if room not in rooms:
        return 
        
    content = {
        "name": name,
        "message": message
    }
    
    send(content, to=room)
    rooms[room]["messages"].append(content)
    if not client:
        send_to_cpp_client(content)

    print(f"{name} said: {data['data']}")

@socketio.on("connect")
def connect():
    room = session.get("room")
    name = session.get("name")
    if not room or not name:
        return
    if room not in rooms:
        leave_room(room)
        return
    
    join_room(room)
    send({"name": name, "message": "has entered the room"}, to=room)
    rooms[room]["members"] += 1
    print(f"{name} joined room {room}")

@socketio.on("disconnect")
def disconnect():
    room = session.get("room")
    name = session.get("name")
    leave_room(room)

    if room in rooms:
        rooms[room]["members"] -= 1
        if rooms[room]["members"] <= 0:
            del rooms[room]
    
    send({"name": name, "message": "has left the room"}, to=room)
    print(f"{name} has left the room {room}")

@socketio.on("join_room")
def join_room_cpp_client(data):
    print(f"Data: {data}")
    if not data:
        print("No data aquired")
    
    room = data.get("room")
    name = data.get("name")

    if not room or not name:
        return
    if room not in rooms:
        leave_room(room)
        return
    
    join_room(room)
    send({"name": name, "message": "has entered the room"}, to=room)
    rooms[room]["members"] += 1
    print(f"{name} joined room {room}")

def send_to_cpp_client(content):
    socketio.emit("messsage", content)

if __name__ == "__main__":
    socketio.run(app, debug=True)