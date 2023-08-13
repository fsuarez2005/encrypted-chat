Frank Suarez 
E00650570 
COSC 439 
Project 3

TCP Chat Client and Multithreaded Chat Server with Encryption

------------------------------------------------------------------------------
>>> INTRODUCTION

The TCP Client and Server consists of two programs, the client and the
server. Bitwise encryption is used with a key exchanged with Diffie-Hellman.

The server listens for clients on a socket. Encryption information is enchanged
during the handshake according to the chat protocol (see PROTOCOL). After that
all data is bitwise encrypted. A log of previous messages will be sent to
users. The server relays messages from users to every other user. A user signals
the server that it is done by sending "DONE". The server will reply with the
elapsed time. If this is the last client on the server, the chat log is removed.

------------------------------------------------------------------------------
>>> COMPILING

make is used to make compiling this software easier. The following will compile
the software:

     make -f fs_Makefile all

------------------------------------------------------------------------------
>>> RUNNING

The server can be run using the following command line options. ( Optional
options are in brackets. )

The server:

    ./fs_TCPServerMT [-p PORT] [-g DIFFIE-HELLMAN-G] [-n DIFFIE-HELLMAN-N]

PORT is the port number that the server will listen on.

DIFFIE-HELLMAN-G (see ENCRYPTION)

DIFFIE-HELLMAN-N (see ENCRYPTION)

The client:

    ./fs_TCPClientMT [-h HOSTNAME] [-p PORT] [-u USERNAME]

HOSTNAME is the hostname to connect to. PORT is the port number to connect
to. USERNAME is the username to send to the server.

------------------------------------------------------------------------------
>>> FUTURE IMPROVEMENTS

* Continue porting the code to Windows.

* Convert the xor encryption and Diffie-Hellman to a multi-precision integer
  type.

* Organize the code use more appropriate namespace names.

------------------------------------------------------------------------------
>>> ENCRYPTION

Encryption is done using a private, one byte key bitwise encryption. During the
handshake, the server will send g, n, and g^A mod n to the client. The client will
respond with its g^B mod n.

g: a common base

n: a common modulus

A: private random number for server

B: private random number for client

The key is the least-significant byte of (g^A mod n)*(g^B mod n).

------------------------------------------------------------------------------
>>> DEPENDECIES

The server relies on POSIX pthreads, semaphores, and other Linux system calls.

------------------------------------------------------------------------------
>>> DEVELOPMENT TIME

Elapsed development time was about 15 hours.

------------------------------------------------------------------------------
>>> EXTRA DOCUMENTATION

File documention has been written in Doxygen. A Doxygen configuration file is
needed.

PROTOCOL

A Message Sequence Chart for the protocol is included as Doxygen on the main page.

