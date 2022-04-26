/**
 * @file receiver.h
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 */

#pragma once

#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/scoped_ptr.hpp>
#include <iostream>
#include <mutex>
#include <ipc_types.h>


// TODO: What happens if sender reboots and re-generates the channel?

namespace ipc_messenger {
using namespace boost::interprocess;

/**
 * @brief Defines a receiver class
 * 
 */
class Receiver {
private:
  std::string ch_name;                 /**< Channel name */
  boost::scoped_ptr<message_queue> mq; /**< shared memory message queue */
  std::mutex mtx;                      /**< Mutex */
  bool opened;                         /**< The status of the channel */
  std::string rx_msg;                  /**< Received message */

public:
  /**
   * @brief Construct a new Receiver object
   * 
   * @param ch channel
   */
  Receiver(int ch);

  /**
   * @brief Opens the channel. Blocks the thread until success
   * 
   */
  void open();

  /**
   * @brief Tries to open the channel.
   * 
   * @return true if success
   * @return false if cannot open
   */
  bool try_open();

  /**
   * @brief Receives a message. Blocks the thread until success. 
   *        If the channel is not oppened, it will wait until.
   * 
   */
  void receive();

  /**
   * @brief Receives a message. Blocks the thread until success
   * 
   * @return true if success
   * @return false if the channel is not opened (returns inmediate)
   */
  bool receive_if_open();

  /**
   * @brief Receives a message.
   * 
   * @return true if success
   * @return false if no message available
   */
  bool try_receive();

  /**
   * @brief Get the message object
   * 
   * @return std::string 
   */
  std::string get_message() const;

  /**
   * @brief Gets if the channel is open
   * 
   * @return true if open
   * @return false otherwise
   */
  bool is_open();
}; // Receiver
}