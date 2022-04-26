/**
 * @file sender.h
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 */

#ifndef SENDER_H_DEFINED
#define SENDER_H_DEFINED

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <sstream>
#include <mutex>
#include <ipc_types.h>

namespace ipc_messenger {

using namespace boost::interprocess;

/**
 * @brief Defines a sender class
 * 
 */
class Sender {
private:
  std::string ch_name;                 /**< Channel name */
  boost::scoped_ptr<message_queue> mq; /**< shared memory message queue */
  std::mutex mtx;                      /**< Mutex */

public:
  /**
   * @brief Construct a new Sender object
   * 
   * @param ch channel
   */
  Sender(int ch);

  /**
   * @brief Destroy the Sender object
   * 
   */
  ~Sender();

  /**
   * @brief Sends the message to the message queue
   * 
   * @param str message to be sent
   * @param prio message priority
   * @return true if was able to send
   * @return false otherwise
   */
  bool send(std::string str, int prio);
}; // Sender

class Logger : public std::ostream {
private:
  std::stringstream ss;
  Sender *snd;
  int prio;

public:
  /**
   * @brief Construct a new Logger object
   * 
   * @param snd sender object
   */
  Logger(Sender & snd, int prio);

  /**
   * @brief Destroy the Logger object
   *        Calls sender send function
   * 
   */
  ~Logger();

  /**
   * @brief returns the stringstream object
   * 
   * @return std::stringstream& 
   */
  std::stringstream &getSS()
  {
    return ss;
  }

  /**
   * @brief Returns the ostream
   *        It is imposible to stream something to an unnamed ostream
   *        This hack is required to avoid the problem
   * 
   * @return Logger& 
   */
  Logger &stream()
  {
    return *this;
  }
}; // Logger

/**
 * @brief Overloaded operator
 * 
 * @tparam T the type must be supported by @ref std::stringstream
 * @param log logger object
 * @param val value to log
 * @return Logger& 
 */
template<class T>
inline Logger& operator<<(Logger &log, const T &val) { 
  log.getSS() << val;
  return log;
}

} // ipc_messenger

/**
 * @brief logs a message
 * 
 * @param _sender sender object
 */
#define LOG(_sender) ipc_messenger::Logger(_sender, 0).stream()
//#define LOG(_sender, _prio) ipc_messenger::Logger(_sender, _prio).stream()

#endif /* SENDER_H_DEFINED */