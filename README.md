# ipc_messenger

A simple message exchange example using boost library message_queue

The chanel is simplex, so only one direction is allowed sender -> receiver.
Channels are independent, so, for a full duplex architecture, just create more channels.