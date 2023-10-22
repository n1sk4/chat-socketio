#include "..\include\Client.h"

using namespace std;

mutex g_Lock;
condition_variable_any g_Cond;

ConnectionListener::ConnectionListener(sio::client& h) :
  m_Handler(h), m_IsConnected(false)
{

}

void ConnectionListener::onConnected()
{
  g_Lock.lock();
  g_Cond.notify_all();
  m_IsConnected = true;
  g_Lock.unlock();
}

void ConnectionListener::onClose()
{
  cout << "Socket IO closed" << endl;
}

void ConnectionListener::onFail()
{
  cout << "Socket IO failed" << endl;
}

Client::Client(string hostIp, string hostPort) : 
  m_IpAddress(hostIp), m_Port(hostPort), m_Listener(m_Client)
{
  setupEvents();
  connect();
}

bool Client::connect()
{
  // Connect
  const string uri = "http://" + m_IpAddress + ":" + m_Port;
  m_Client.connect(uri);

  g_Lock.lock();
  if (!m_Listener.getConnectionStatus())
  {
    cout << "Waiting for connection..." << endl;
    g_Cond.wait(g_Lock);
  }

  g_Lock.unlock();
  cout << "Connected!" << endl;
  return true;
}

bool Client::send(string aId, sio::message::list aMessage)
{
  bool success = false;
  sio::message::list message = aMessage;

  g_Lock.lock();
  m_Client.socket()->emit(aId, message, [&](const sio::message::list& returnMessage)
    {
      try
      {
        g_Lock.lock();
        success = true; // TODO Implement Acknowledge
        g_Lock.unlock();
      }
      catch(...)
      {
        g_Cond.notify_all();
        g_Lock.unlock();
      }
    }
  );
  g_Cond.wait_for(g_Lock, std::chrono::milliseconds(1000));
  g_Lock.unlock();

  return success;
}

bool Client::joinRoom(string roomId, string userName)
{
  m_UserName = userName;

  sio::message::list messageList;
  auto data = sio::object_message::create();
  map < string, sio::message::ptr>& dataMap = data->get_map();
  dataMap["room"] = sio::string_message::create(roomId);
  dataMap["name"] = sio::string_message::create(userName);
  messageList.push(data);

  return send("join_room", messageList);
}

bool Client::sendMessage(string roomId, string message)
{
  sio::message::list messageList;
  auto data = sio::object_message::create();
  map < string, sio::message::ptr>& dataMap = data->get_map();
  dataMap["room"] = sio::string_message::create(roomId);
  dataMap["name"] = sio::string_message::create(m_UserName);
  dataMap["data"] = sio::string_message::create(message);
  dataMap["client"] = sio::string_message::create("cpp");
  messageList.push(data);

  return send("message", messageList);
}

void Client::setupEvents()
{
  // Setup listeners  
  m_Client.set_open_listener(bind(&ConnectionListener::onConnected, &m_Listener));
  m_Client.set_close_listener(bind(&ConnectionListener::onClose, &m_Listener));
  m_Client.set_fail_listener(bind(&ConnectionListener::onFail, &m_Listener));
  m_Client.socket()->on("server", sio::socket::event_listener_aux([&](string const& name, sio::message::ptr const& data, bool isAck, sio::message::list& ack_resp)
    {
      g_Lock.lock();
      cout << name << endl;
      cout << data->get_string() << endl;
      g_Lock.unlock();
    }));
  m_Client.socket()->on("message", sio::socket::event_listener_aux([&](string const& name, sio::message::ptr const& data, bool isAck, sio::message::list& ack_resp)
    {
      g_Lock.lock();
      cout << data->get_string() << endl;
      g_Lock.unlock();
    }));
}
