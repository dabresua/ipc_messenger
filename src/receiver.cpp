/**
 * @file receiver.cpp
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 */

#include <receiver.h>
#include <thread>

using namespace ipc_messenger;

Receiver::Receiver(int ch) : mtx(), opened(false)
{
  ch_name = get_channel_name(ch);
}

void Receiver::open()
{
  do {
    bool b = try_open();
    if (!b)
      std::this_thread::sleep_for(retry_time);
  } while (!opened);
  std::cout << "Channel opened!!!" << std::endl;
}

bool Receiver::try_open()
{
  try {
    mq.reset(new message_queue(open_only, ch_name.c_str()));
    opened = true;
  } catch(interprocess_exception &ex) {
    opened = false;
  }
  return opened;
}

void Receiver::receive()
{
  open();
  unsigned int priority;
  message_queue::size_type recvd_size;
  message_t msg;

  mq->receive(msg, sizeof(msg), recvd_size, priority);
  rx_msg = std::string(msg);
}

bool Receiver::receive_if_open()
{
  if (!try_open())
    return false;
  unsigned int priority;
  message_queue::size_type recvd_size;
  message_t msg;

  mq->receive(msg, sizeof(msg), recvd_size, priority);
  rx_msg = std::string(msg);
  return true;
}

bool Receiver::try_receive()
{
  if (!try_open())
    return false;
  unsigned int priority;
  message_queue::size_type recvd_size;
  message_t msg;

  bool ret = mq->try_receive(msg, sizeof(msg), recvd_size, priority);
  if (ret)
    rx_msg = std::string(msg);
  return ret;
}

std::string Receiver::get_message() const
{
  return rx_msg;
}

bool Receiver::is_open()
{
  return opened;
}