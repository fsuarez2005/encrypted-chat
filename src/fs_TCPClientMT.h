/** \file fs_TCPClientMT.h
 ** \brief chat client
 **/

using namespace std;

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

#include <stdint.h>
#include <netinet/tcp.h>

#include <string>
#include <exception>
#include <iostream>
#include <sstream>

#include "fs_macros.h"
#include "fs_socket.h"
#include "fs_thread.h"
#include "fs_diffie.h"
#include "fs_xor.h"

#define PROGRAM_NAME "TCPClientMT"
// ----------------------------------------------------------------
/// organize command line options 
class Options {
public:
  int port;
  string hostname;
  string username;
  
  Options() : 
    port(DEFAULT_PORT),
    hostname(string(DEFAULT_HOSTNAME))
  {}
};
// ----------------------------------------------------------------
namespace fs {
  class client;

  /// thread to read and print any data from socket.
  /** incoming data will interfere with user prompt
   ** on client side.
   **
   ** there should be a better way to check for 
   ** incoming data and wait for user input
   **/
  class socketreader : public thread {
  private:
    bool run_loop;
  public:
    client * parent;

    void run();
  };
  // -----------------------------------
  /// chat client
  class client {
  private:
    string host;
    short port;      
    string username;

    xor_cipher xor_c;

    socket conn;
    socket_address address;

    /// sets up client socket address
    void setup();

  public:
    friend class socketreader;

    /// connects the client to host with port and username
    void connect(string host, short port, string username);

    /// sets up login and encryption
    void handshake();

    /// reads user input 
    void get_user_input();

    /// encrypts and sends some data to the server
    client& operator<<(const string & data);

    /// read and decrypts some data from the server
    client& operator>>(string & var);
  };
} // namespace fs

