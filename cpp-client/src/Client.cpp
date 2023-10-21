#include "..\include\Client.h"

using namespace std;

mutex g_Lock;
condition_variable_any g_Cond;

Client::Client(string hostIp, string hostPort) : 
  m_IpAddress(hostIp), m_Port(hostPort)
{
  // Setup listeners
  ConnectionListener l(m_Client);
  
  m_Client.set_open_listener(bind(&ConnectionListener::onConnected, &l));
  m_Client.set_close_listener(bind(&ConnectionListener::onClose, &l));
  m_Client.set_fail_listener(bind(&ConnectionListener::onFail, &l));
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
      cout << "Message recieved" << endl;
      cout << name << endl;
      cout << data->get_string() << endl;
      g_Lock.unlock();
    }));

  // Connect
  const string uri = "http://" + m_IpAddress + ":" + m_Port;
  cout << uri << endl;
  m_Client.connect(uri);

  g_Lock.lock();
  if (!l.getConnectionStatus())
  {
    cout << "Waiting for connection..." << endl;
    g_Cond.wait(g_Lock);
  }

  g_Lock.unlock();
  cout << "Connected!" << endl;

  sio::message::list message = "Hello World";
  m_Client.socket()->emit("hello", message);

  m_Client.close();
  m_Client.clear_con_listeners();
}


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
  exit(0);
}

void ConnectionListener::onFail()
{
  cout << "Socket IO failed" << endl;
  exit(0);
}