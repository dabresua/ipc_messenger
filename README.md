# ipc_messenger

A simple message exchange example using boost library message_queue

The chanel is simplex, so only one direction is allowed sender -> receiver.

Channels are independent and can endure reboots. Avoid making the receiver be in receive state while the sender reboots, becose it get stuck.

## How to use it

Show the help

```bash
danielbreton@2022-EMEA-0022 ~/workspace/ipc_messenger (master)$ ./output/main -h
Allowed options:
  -h [ --help ]         print usage message
  -s [ --sender ] arg   sets the sender channel
  -r [ --receiver ] arg sets the receiver channel

```

Start a server in the channel 20

```bash
danielbreton@2022-EMEA-0022 ~/workspace/ipc_messenger (master)$ ./output/main -s 20
channel 20 mode 0
Finish (f) or send a message
```

In a different terminal, start a receiver in the channel 20 and open that channel

```bash
danielbreton@2022-EMEA-0022 ~/workspace/ipc_messenger (master)$ ./output/main -r 20
channel 20 mode 1
Finish (f), open (o), try to open (to), receive (r), receive if open (ro) or try to receive (tr)
o
Channel opened!!!
```
