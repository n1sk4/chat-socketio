#pragma once
#include <functional>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include "sio_client.h"

using namespace std;

class Client
{
public:
  Client(string hostIp, string hostPort);

private:
  bool connect();
  bool disconnect();
  bool sendUserName();
  bool sendRoomName();
  bool sendMessage();

  void setupEvents();

  sio::client m_Client;
  string m_IpAddress;
  string m_Port;
};

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