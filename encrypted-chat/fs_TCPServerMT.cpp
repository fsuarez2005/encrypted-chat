
using namespace std;

#include "fs_TCPServerMT.h"

/// parses command line options and sets options in Options object
void
parse_opts(int argc, char * const argv[], Options & o) {
  // -p port
  stringstream s;
  // reset getopt index
  optind = 1;

  int opt;
  while((opt = getopt(argc,argv,"p:g:n:")) != -1) {
    switch (opt) {
    case '?': // unknown
      exit(1);
      break;

    case 'p': // port
      // clears stringstream buffer
      s.clear();
      s.str(string());

      s << optarg;
      s >> o.port;
      break;

    case 'g': // diffie-hellman g
      // convert string to long long

      // clears stringstream buffer
      s.clear();
      s.str(string());

      s << optarg;
      s >> o.g;
      break;

    case 'n': // diffie-hellman n
      // convert string to long long
      
      // clears stringstream buffer
      s.clear();
      s.str(string());

      s << optarg;
      s >> o.n;
      break;

    default:
      break;
    }
  }
}

namespace fs {
  // connection implementation
  connection::connection() :
    logged_in(false),
    messages(0),
    connected(false),
    prompt("Enter message: "),
    show_prompt(false)
  {}
  // -----------------------------------------
  connection::~connection() {
    connected = false;
    client_socket.close();
  }
  // -----------------------------------------
  void connection::process_messages() {
    string output_msg;
    string input;

    do {
      if (show_prompt) {
	(*this) << prompt;
      }

      (*this) >> input;

      if (input == "DONE\n") {
	break;
      }

      output_msg = username + ": ";
      output_msg += input;

      parent->log_message(output_msg);
      parent->broadcast_message(this,output_msg);
      cout << "Message: " << output_msg;

      messages++;
    } while (true);

  }
  // -----------------------------------------
  void connection::send_report() {
    // hours::minutes::seconds::milliseconds  
    stringstream outstring;

    outstring.fill('0');
    outstring << setw(2) << elapsed.get_hours() << "::" <<
      setw(2) << elapsed.get_minutes() << "::" << 
      setw(2) << elapsed.get_seconds() << "::" << 
      setw(3) << elapsed.get_milliseconds() << "\n";

    string report_string = outstring.str();

    // sends report
    (*this) << report_string;
  }
  // -----------------------------------------
  void connection::handshake() {
    // check doxygen documentation for a Message Sequence Chart
    // the handshake.
    cout << "handshake()" << endl;
    string input;

    diffie.set_g(parent->opts.g);
    diffie.set_n(parent->opts.n);
    diffie.calculate_gxn();


    client_socket << diffie.get_g(); // send g
    client_socket << diffie.get_n(); // send n
    client_socket << diffie.get_gxn(); // send g^A % n

    // wait for g^B % n from client
    int64_t client_gxn;
    client_socket >> client_gxn;

    // create key g^(AB) % n
    diffie.set_other_gxn(client_gxn);

    char key = diffie.get_key();
    xor_c.set_key(key);

    printf("key: %08X\n",diffie.get_full_key());


    // warn about g and n that would make key == 0.
    // if key == 0, data is not encrypted.
    if (key == 0) {
      cerr << "WARNING: poor choices for g and n. key is 0." << endl;
    }

    // use the encryption for this connection
    (*this) >> username;

    logged_in = true;

    // send chat log
    parent->send_chatlog(this);

    string login_message = username;
    login_message += " has logged in.\n";
    parent->broadcast_message(this,login_message);
    parent->log_message(login_message);
  }
  // -----------------------------------------
  void connection::run() {
    connected = true;

    elapsed.start();

    try {
      handshake();
    } catch (SOCKET_EXCEPTION_E e) {
      cerr << "Error in handshake." << endl;

      client_socket.close();

      parent->client_done(this->id());
      return;
    }

    if (! logged_in) {
      parent->client_done(this->id());
      connected = false;
      return;
    }

    try {
      process_messages();
    } catch (SOCKET_EXCEPTION_E e) {
      cerr << "Error processing messages." << endl;
      client_socket.close();

      parent->client_done(this->id());
      return;
    }

    elapsed.stop();    

    try {
      send_report();
    } catch (SOCKET_EXCEPTION_E e) {
      cerr << "Error sending report." << endl;
      client_socket.close();

      parent->client_done(this->id());
      return;
    }

    client_socket.close();

    string logout_message = username;
    logout_message += " has left.\n";

    parent->broadcast_message(this,logout_message);
    parent->log_message(logout_message);

    // tells server we are finished
    parent->client_done(this->id());
    logged_in = false;
    connected = false;
  }
  // -----------------------------------------
  /// returns connection id
  long connection::id() {
    return (long) get_thread_id();
  }
  // =========================================
  // server implementation
  server::server() {
    server_socket = socket(AF_INET,SOCK_STREAM,0);
  }
  // -----------------------------------------
  server::server(Options & o) :
    opts(o),
    port(o.port),
    diffie_g(o.g),
    diffie_n(o.n)
  {
    server_socket = socket(AF_INET,SOCK_STREAM,0);
  }
  // -----------------------------------------
  void server::setup() {
    server_socket.option(SOL_SOCKET, SO_REUSEADDR, true);
    server_socket.bind(port);
    server_socket.listen(BACKLOG);
  }
  // -----------------------------------------
  void server::start() {
    setup();
    connection * current_connection;

    printf("Server is listening on port %d\n",port);
    while (true) {
      socket conn = server_socket.accept();

      // deleted in connection_list destructor
      current_connection = new connection;
      current_connection->parent = this;
      current_connection->client_socket = conn;

      // start thread
      current_connection->start();
      
      connection_list[ current_connection->id() ] = current_connection;
    }
  }
  // -----------------------------------------
  void server::broadcast_message(connection * me,string msg) {
    for (map< long,connection * >::iterator it = connection_list.begin();
	 it != connection_list.end();
	 it++ ) {

      // it->first:      connection->id()
      // it->second:     connection *

      if (! it->second->logged_in) {
	// user is not logged in
      } else if ( (me != NULL) && (it->first == me->id()) ) {
	// Don't want to sent it myself
      } else {
	try {
	  // send encrypted
	  (* (it->second)) << msg;
	} catch (SOCKET_EXCEPTION_E e) {
	  cerr << "Could not broadcast message." << endl;
	}
      }
    }
  }

  void server::send_chatlog(connection * me) {
    stringstream msg;
    string buffer;

    synchronized {
      msg << CHATLOG_HEADER << "\n";
      fstream log ( CHATLOG_FILENAME,ios::in | ios::binary);
      while (log.good()) {
	getline(log,buffer);
	msg << buffer << "\n";
      }
      msg << CHATLOG_FOOTER << "\n";

      // send encrypted
      (*me) << msg.str();

      log.close();
    }
  }

  void server::log_message(string msg) {
    // see fs_lock.h for synchronized macro
    synchronized {
      fstream log ( CHATLOG_FILENAME,ios::out | ios::app | ios::binary);
      log << msg;
      log.flush();
      log.close();
    }
  }

  void server::remove_chatlog() {
    if (::remove( CHATLOG_FILENAME ) < 0) {
      // ignore errors
    }
  }

  void server::client_done(long connection_id) {
    connection_list.erase(connection_id);
    if (connection_list.empty()) {
      remove_chatlog();
    }
  }
} // namespace fs

int main(int argc,char * const argv[]) {
  // prints banner
  printf("%s, %s <%s>\n\n",PROGRAM_NAME,AUTHOR,EMAIL);

  Options o;
  parse_opts(argc,argv,o);

  fs::server s(o);
  s.start();
  
  return 0;
}

