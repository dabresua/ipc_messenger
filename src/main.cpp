#include <sender.h>
#include <receiver.h>

#include <boost/program_options.hpp>

using namespace ipc_messenger;
using namespace std;
namespace po = boost::program_options;

/**
 * @brief checks that multiple options are not specified at the same time
 * 
 * @param vm 
 * @param opt1 
 * @param opt2 
 */
void conflicting_options(const po::variables_map& vm, 
                         const char* opt1, const char* opt2)
{
  if (vm.count(opt1) && !vm[opt1].defaulted() 
      && vm.count(opt2) && !vm[opt2].defaulted())
    throw logic_error(string("Conflicting options '") 
                      + opt1 + "' and '" + opt2 + "'.");
}

int main(int argc, char *argv[])
{
  enum mode {sender, receiver};
  int channel = 0;
  bool mode = false;

  try {
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "print usage message")
    ("sender,s", po::value(&channel), "sets the sender channel")
    ("receiver,r", po::value(&channel), "sets the receiver channel")
    ;

    po::variables_map vm;
    store(po::parse_command_line(argc, argv, desc), vm);

    conflicting_options(vm, "sender", "receiver");

    if (vm.count("help")) {  
      cout << desc << "\n";
      return 0;
    }

    try {
      channel = vm["sender"].as<int>();
      mode = sender;
    } catch(exception &e) {}

    try {
      channel = vm["receiver"].as<int>();
      mode = receiver;
    } catch(exception &e) {}

  } catch(exception &e) {
    cerr << e.what() << endl;
    return -1;
  }

  cout << "channel " << channel << " mode " << mode << endl;

  if (mode == sender) {
    // Sender
    Sender snd(channel);
    string str;
    while (true)
    {
      cout << "Finish (f) or send a message" << endl;
      cin >> str;
      if (str == "f")
        break;
      LOG(snd) << str;
    }
  } else {
    // Receiver
    Receiver rx(channel);
    string str;
    bool b;
    while (true)
    {
      cout << "Finish (f), open (o), try to open (to), " <<
              "receive (r), receive if open (ro) or try to receive (tr)" << endl;
      cin >> str;
      if (str == "f")
        break;
      if (str == "r") {
        rx.receive();
        cout << rx.get_message() << endl;
      }
      if (str == "o")
        rx.open();
      if (str == "to") {
        b = rx.try_open();
        cout << (b ? "opened" : "not opened") << endl;
      }
      if (str == "tr") {
        b = rx.try_receive();
        if (b) {
          cout << rx.get_message() << endl;
        } else {
          cout << "No message" << endl;
        }
      }
      if (str == "ro") {
        b = rx.receive_if_open();
        if (b) {
          cout << rx.get_message() << endl;
        } else {
          cout << "No message" << endl;
        }
      }
    }
  }

  return 0;
}