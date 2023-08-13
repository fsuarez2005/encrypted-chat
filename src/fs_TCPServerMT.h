/** \file fs_TCPServerMT.h
 ** \brief Multithreaded Chat Server
 **/

using namespace std;

#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <pthread.h>

#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <exception>

#include "fs_thread.h"
#include "fs_socket.h"
#include "fs_timer.h"
#include "fs_lock.h"
#include "fs_macros.h"
#include "fs_diffie.h"
#include "fs_xor.h"

#define PROGRAM_NAME "TCPServerMT"

#define DEFAULT_G 1
#define DEFAULT_N 1

// ==============================================================
/// organizes command line options in an object
class Options {
public:
  int port; /// port number
  int64_t g;
  int64_t n;

 Options() : 
  port(DEFAULT_PORT),
  g(DEFAULT_G),
  n(DEFAULT_N)  
 {}
};

namespace fs {
  class connection;
  class server;

  /// thread for each connection
  class connection : public thread {
  public:
    connection();
    ~connection ();
    socket client_socket;
    server * parent;   ///< allows access to server
    
    chrono elapsed; ///< elapsed time
    bool logged_in;

    int messages;  ///< number of messages
    bool connected;  ///< connected to client

    string username;  ///< client's username

    string prompt; ///< prompt for messages
    string username_prompt; ///< prompt asking for username
    bool show_prompt; ///< false if quiet

    diffie_hellman diffie;
    xor_cipher xor_c;

    /// returns id used for connection list
    long id();

    /// method to run for each connection
    void run();

    /// processes messages from client
    void process_messages();

    /// sets up a connection with client
    void handshake();

    /// sends end report after client is done sending messages
    void send_report();


    connection & operator<<(const string & data) {
      xor_c.new_message();
      xor_c << data;

      client_socket.write(xor_c.get_string());

      return *this;
    }

    connection& operator>>(string & var) {
      string data = client_socket.read();
      xor_c.new_message();
      xor_c << data;

      var.assign(xor_c.get_string());
      return *this;
    }
  };
  // ---------------------------------------------------------------------------
  /// Multithreaded Chat Server
  class server {
  private:
    map< long, connection * > connection_list; ///< list of connection objects
    short port;
    socket server_socket;

    int64_t diffie_g;
    int64_t diffie_n;

    /// sets up server socket
    void setup();

    /// removes the chat log
    void remove_chatlog();

    fstream chatlog;
  public:
    Options opts;

    server();
    server(short port);
    server(Options &);

    /// starts the server
    void start();

    /// sends a message to every connection except for the specified 
    /** If me != NULL, do not send to client me. 
     ** If me == NULL, send to every client.
     **/
    void broadcast_message(connection * me,string msg);

    /// logs message to chat file
    void log_message(string msg);

    /// sends the client the whole chat log
    void send_chatlog(connection * me);

    /// callback when connection is finished
    void client_done(long connection_id);
  };
  // ---------------------------------------------------------------------------

} // namespace fs

// protocol diagram, see Doxygen documentation
/*! \mainpage
    Client-Server Protocol

    \msc
    Server,Client;
    --- [label="handshake"];
    Server->Client [label="Diffie-Hellman g (int64_t)"];
    Server->Client [label="Diffie-Hellman n (int64_t)"];
    Server->Client [label="Diffie-Hellman g^A mod n (int64_t)"];
    Server<-Client [label="Diffie-Hellman g^B mod n (int64_t)"];
    --- [label="Encrypted Communication"];
    Server<-Client [label="username"];
    --- [label="Ready for messages"];
    Server<-Client [label="chat message"];
    |||;
    Server->Client [label="chat messages from other users"];
    ...;
    Server box Client [label="chat session"];
    ...;
    Server<-Client [label="\"DONE\""];
    Server->Client [label="Elapsed Time Report"];
    \endmsc

 */
