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
  std::this_thread::sleep_for(std::chrono::seconds(2));
  while (1)
  {
    string msg;
    cout << "Type message:";
    cin >> msg;
    c.sendMessage(roomCode, msg);
  }
  return 0;
}