/** \file fs_socket.h
 ** \brief wrapper class around pthreads
 **/

#pragma once
#ifndef FS_SOCKET_H
#define FS_SOCKET_H



#include <iostream>
#include <exception>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <unistd.h>
#include <errno.h>

#include <sys/types.h>

#include <arpa/inet.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>

using namespace std;

#include "endian.h"
#include "fs_lock.h"
#include "fs_macros.h"

namespace fs {
  /// exception for socket errors
  enum SOCKET_EXCEPTION_E {
    SOCKET_ERROR,
    SOCKET_CLOSED,
    SOCKET_NODATA
  };

  /// easily convert between socket address structs
  union address_union {
    struct sockaddr sockaddr; 
    struct sockaddr_in sockaddr_in;
  };
  // ----------------------------------------------
  /// wrapper around sockaddr
  class socket_address {
  private:
    struct sockaddr address;
    socklen_t address_length;
    std::string hostname;
    std::string service;
    short port;
  public:
    socket_address();
    socket_address(std::string hostname, std::string service);
    socket_address(std::string hostname, short port);
    ~socket_address();
    /// returns a value useful for connect()
    const struct sockaddr* get_sockaddr();
    socklen_t get_address_length();
  };
  // -------------------------------------------------
  /// a simple class wrapper for sockets
  ///
  /// \todo Add readline function
  /// \todo Finish option function
  class socket {
  private:
    short port;
    int s_fd; /// socket file descriptor
    socket_address address2;
    union address_union uSocket_address;
    struct sockaddr_in in_address;
    socklen_t socket_address_len;
    void setup_socket_address();
  public:
    socket();
    socket(int domain,int type, int protocol);
    socket(int socket_fd);
    ~socket();

    /// connects using a socket_address
    void connect(socket_address & addr);

    /// connects using a hostname and port
    void connect(string hostname,short port);

    /// sets to listen mode
    void listen(int backlog);

    /// binds to a port
    void bind(int port);

    /// returns a client connection socket
    socket accept();

    /// sets a socket option
    void option(int level,int optname,bool optval_bool);

    // ----------------------------------------
    /// sends a string to the socket
    void write(string data);

    /// sends a char array to the socket
    void write(char * data, size_t len);

    /// sends a char to the socket
    void write(char data);

    /// sends an int to the socket in network order
    void write(int data);

    // reads data from the socket and returns it as a string
    //string readline();

    /// reads data from the socket and returns it as a string
    string read();

    /// reads len number of bytes from the socket and returns it as a string
    string read(size_t len);

    
    socket & operator<<(string data);
    socket & operator<<(char data);
    socket & operator<<(int data);
    socket & operator<<(int64_t data);

    socket & operator>>(int64_t & var);
    // TODO: void operator>>(char & var);
    // TODO: void operator>>(int & var);

    socket & operator>>(string & var);

    // ----------------------------------------
    /// returns socket file descriptor
    int socket_fd();

    /// sets socket file descriptor
    void socket_fd(int s_fd);

    /// closes the socket
    void close();
  };
}
#endif // FS_SOCKET_H
