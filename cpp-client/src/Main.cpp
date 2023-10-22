#include "..\include\Client.h"

int main() 
{
  cout << "Chat App" << endl;
  Client c("127.0.0.1", "5000");

  string userName, roomCode;
  cout << "Pick a name: ";
  cin >> userName;
  cout << "Select room: ";
  cin >> roomCode;
  c.joinRoom(roomCode, userName);
  cout << endl << "You joined room: " << roomCode << endl << endl << "Type message : ";
  while (1)
  {
    string msg;
    cin >> msg;
    c.sendMessage(roomCode, msg);
  }
  return 0;
}