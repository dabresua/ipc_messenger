# ipc_messenger

A simple message exchange example using boost library message_queue

The chanel is simplex, so only one direction is allowed sender -> receiver.

Channels are independent and can endure reboots. Avoid making the receiver be in receive state while the sender reboots, becose it get stuck.
