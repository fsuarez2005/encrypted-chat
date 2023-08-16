using namespace std;

#include "fs_socket.h"

namespace fs {
  socket_address::socket_address() {}

  socket_address::socket_address(string hostname, string service) {

    struct addrinfo * result_address;

    // get struct sockaddr from hostname and service
    if ((errno = getaddrinfo(hostname.c_str(),service.c_str(),NULL,&result_address)) < 0) {
      printf("%s\n",gai_strerror(errno));
      exit(1);
    }
    // copy family
    address.sa_family = result_address->ai_addr->sa_family;
    // copy address data
    memcpy(&(address.sa_data),
	   result_address->ai_addr->sa_data,
	   sizeof(char)*sizeof(address.sa_data)); 

    freeaddrinfo(result_address);
  }
 
  socket_address::~socket_address() {}

  const struct sockaddr* socket_address::get_sockaddr() {
    return &address;
  }
  
  socklen_t socket_address::get_address_length() {
    return sizeof(address);
  }

  // ======================================================
  socket::socket() {}

  socket::socket(int domain,int type, int protocol) {
    s_fd = ::socket(domain, type, protocol);
  }

  socket::socket(int socket_fd) {
    this->s_fd = socket_fd;
  }
  socket::~socket() {}

  void socket::listen(int backlog) {
    if (::listen(s_fd,backlog) < 0) {
      perror("listen" __LINESTR__ );
      exit(1);
    }
  }

  void socket::bind(int port) {
    // XXX check for errors
    memset((char *) &(uSocket_address.sockaddr_in), 0, sizeof(uSocket_address.sockaddr_in));
    // XXX may be different type of socket
    uSocket_address.sockaddr_in.sin_family = AF_INET;
    uSocket_address.sockaddr_in.sin_addr.s_addr = INADDR_ANY;
    // XXX check for errors
    uSocket_address.sockaddr_in.sin_port = htons(port);
   
    // registers the service
    if ((::bind(s_fd,&(uSocket_address.sockaddr), sizeof(uSocket_address.sockaddr))) < 0) {
      perror(__FILE__ ": line " __LINESTR__ ": bind" );
      exit(1);
    }
  }

  socket socket::accept() {
    struct sockaddr client_socket_address;
    
    socklen_t addrlen = sizeof(struct sockaddr);
    int sock_fd;
    if ((sock_fd = ::accept(s_fd,&client_socket_address,&addrlen)) < 0) {
      perror("accept"  __LINESTR__ );
      exit(1);
    }
    return socket(sock_fd);
  }

  /// \todo clean up
  void socket::option(int level,int optname,bool optval_bool) {
    // int setsockopt(int sockfd,
    // 		   int level,
    // 		   int optname,
    // 		   const void *optval,
    // 		   socklen_t optlen);

    int optval = 0;
    if (optval_bool) {
      optval = 1;
    }

    socklen_t optlen = sizeof(optval);

     // \todo port to win32
    setsockopt(s_fd,level,optname,(const void *)&optval,optlen);
  }
  // ----------------------------------------
  // higher level IO functions
  void socket::write(string data) {
    synchronized {
      int chars_sent = ::send(s_fd,data.c_str(),data.size(),0);
      // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
      if ( chars_sent < 0 ) {
      	perror("send" __LINESTR__  );
      	throw SOCKET_ERROR;
      }
    }
  }

  void socket::write(char * data, size_t len) {
    synchronized {
      // ssize_t send(int sockfd, const void *buf, size_t len, int flags);
      if ( send(s_fd,data,len,0) < 0 ) {
	perror("send" __LINESTR__  );
	throw SOCKET_ERROR;
      }
    }
  }

  void socket::write(char data) {
    write((char*) &data,1);
  }

  void socket::write(int data) {
    int corrected_data = htonl(data);
    write((char *) &corrected_data,sizeof(int));
   
  }

  /// reads as many chars as possible
  /// \todo check if this blocks
  string socket::read() {
    // returned string
    string data = "";

    // temp string to append to data
    string buffer_string;

    char * inbuffer;
    int chars_recvd;

    synchronized {
      inbuffer = new char[BUFFER_SIZE];

      do {
	chars_recvd = recv(s_fd,inbuffer,BUFFER_SIZE-1, 0);
	if (chars_recvd < 0) {
	  // error in socket
	  // disconnect client
	  
	  perror("recv: error: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_ERROR;

	} else if (chars_recvd == 0) {
	  // client shutdown in okay manner
	  //perror("recv: no data: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_NODATA;

	}

	buffer_string.assign(inbuffer,chars_recvd);
      
	// appends buffer to string
	data += buffer_string;
      } while (chars_recvd == (BUFFER_SIZE - 1)); // continue until we have a partial buffer

      delete[] inbuffer;
    }
    return data;
  }

  /// reads a maximum of len chars
  string socket::read(size_t len) {
    // returned string
    string data = "";

    // temp string to append to data
    string buffer_string;

    char * inbuffer;
    int chars_recvd;

    size_t recv_loops = len / (BUFFER_SIZE - 1);
    size_t last_loop = len % (BUFFER_SIZE - 1);

    synchronized {
      inbuffer = new char[BUFFER_SIZE];
      // recv for recv_loops times
      for (size_t n = 0; n < recv_loops; n++) {
	chars_recvd = recv(s_fd,inbuffer,BUFFER_SIZE-1, 0);
	if (chars_recvd < 0) {
	  // error in socket
	  // disconnect client
	  perror("recv: error: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_ERROR;

	} else if (chars_recvd == 0) {
	  // client shutdown in okay manner
	  //perror("recv: no data: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_NODATA;
	}

	buffer_string.assign(inbuffer,chars_recvd);
      
	// appends buffer to string
	data += buffer_string;
      }

      // recv for last loop
      if (last_loop > 0) {
	chars_recvd = recv(s_fd,inbuffer,last_loop, 0);
	if (chars_recvd < 0) {
	  // error in socket
	  // disconnect client

	  perror("recv: error: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_ERROR;

	} else if (chars_recvd == 0) {
	  // client shutdown in okay manner

	  //perror("recv: no data: " __FILE__ ": line " __LINESTR__ );
	  throw SOCKET_NODATA;

	}
      }

      buffer_string.assign(inbuffer,chars_recvd);
      
      // appends buffer to string
      data += buffer_string;

      delete[] inbuffer;
    }

    return data;
  }

  // send 
  socket& socket::operator<<(string data) {
    write(data);
    return *this;
  }

  socket& socket::operator<<(char data) {
    write(data);
    return *this;
  }

  socket& socket::operator<<(int64_t var) {
    union convertor {
      int64_t val;
      char array[sizeof(int64_t)];
    } x;

    x.val = be64toh(var);

    string buffer;
    buffer.assign(x.array,sizeof(int64_t));

    write(buffer);
    return *this;
  }

  // recv
  socket& socket::operator>>(int64_t & var) {
    union convertor {
      int64_t val;
      char array[sizeof(int64_t)];
    } x;

    string buffer = read(sizeof(int64_t));

    //cout << "buffer: " << buffer << endl;
    memcpy(x.array,buffer.c_str(),sizeof(int64_t));

    // network is big endian
    var = be64toh(x.val);
    return *this;
  }

  socket& socket::operator>>(string & var) {
    var = read();
    return *this;
  }

  // ----------------------------------------
    
  // returns socket file descriptor
  // throws err_socket
  int socket::socket_fd() {
    return s_fd;
  }

  // sets socket file descriptor
  // throws err_socket
  void socket::socket_fd(int s_fd ) {
    this->s_fd = s_fd;
  }

  void socket::close() {
    if (::close(s_fd) < 0) {
      perror(NULL);
      throw SOCKET_ERROR;
    }
  }

  void socket::connect (socket_address & address) {
    int connect(int sockfd, const struct sockaddr *addr,
		socklen_t addrlen);

    const struct sockaddr * addr = address.get_sockaddr();
    socklen_t addrlen = address.get_address_length();

    if( ::connect(s_fd,addr,addrlen) < 0) {
      perror("connect(): ");
      //throw SOCKET_ERROR;
      exit(1);
    }

  }

} // namespace fs

