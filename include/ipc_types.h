/**
 * @file ipc_types.h
 * @author Daniel Bretón (d.breton.suarez@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-26
 * 
 */

#pragma once

#include <string>
#include <chrono>

namespace ipc_messenger {

// Defines the message max size
const int msg_size = 1024;

// Defines a message type
typedef char message_t[msg_size];

// Defines the message buffer size
const int msg_num = 10;

// Defines the channel base name
static const char channel_base[] = "ipc_messenger_";

// Defines the time between re-tries to open the channel
static const std::chrono::duration retry_time = std::chrono::milliseconds(500);

/**
 * @brief Get the channel name given channel number
 * 
 * @param ch channel number
 * @return char* channel full name
 */
static inline std::string get_channel_name(int ch)
{
  std::string str(channel_base);
  str += ch;
  return str;
}

} // ipc_messenger