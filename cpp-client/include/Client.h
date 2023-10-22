#pragma once
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include "sio_client.h"

using namespace std;

class ConnectionListener
{
public:
  ConnectionListener(sio::client& h);
  void onConnected();
  void onClose();
  void onFail();
  bool getConnectionStatus()
  {
    return m_IsConnected;
  }

private:
  sio::client& m_Handler;
  bool m_IsConnected = false;
};

class Client
{
public:
  Client(string hostIp, string hostPort);

  bool connect();
  bool disconnect();
  bool send(string id, sio::message::list message);
  bool joinRoom(string roomId, string userName);
  bool sendMessage(string roomId, string message);

private:
  void setupEvents();

  sio::client m_Client;
  string m_IpAddress;
  string m_Port;
  string m_UserName;

  ConnectionListener m_Listener;
};
