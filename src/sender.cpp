/**
 * @file sender.cpp
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 */

#include <sender.h>

using namespace ipc_messenger;

Sender::Sender(int ch) : mtx()
{
  ch_name = get_channel_name(ch);
  // Erase previous message queue
  message_queue::remove(ch_name.c_str());
  // Create a message_queue.  
  mq.reset(new message_queue(create_only, ch_name.c_str(), msg_num, 
           sizeof(message_t)));
  //mq.reset(new message_queue(open_or_create, ch_name.c_str(), msg_num, 
  //       sizeof(message_t)));
}

Sender::~Sender()
{
  message_queue::remove(ch_name.c_str());
}

bool Sender::send(std::string str, int prio)
{
  std::lock_guard<std::mutex> lk(mtx);
  message_t msg;
  snprintf(msg, str.size() + 1 > msg_size ? msg_size : str.size() + 1, 
          "%s", str.c_str());
  printf("Sending %s\n", msg);
  return mq->try_send(msg, sizeof(msg), prio);
}

Logger::Logger(Sender & snd, int prio) : ss()
{
  this->snd = &snd;
  this->prio = prio;
}

Logger::~Logger()
{
  snd->send(ss.str(), prio);
}