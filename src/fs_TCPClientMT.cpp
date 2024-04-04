using namespace std;

#include "fs_TCPClientMT.h"


/// parses command line options and sets options in Options object
void
parse_opts(int argc, char * const argv[], Options & o) {
  // -p port
  // -h hostname
  // -u username

  // reset getopt index
  optind = 1;

  int opt;
  while((opt = getopt(argc,argv,"h:p:u:")) != -1) {
    switch (opt) {
    case '?': // unknown
      break;
    case 'p': // port
      o.port = atoi(optarg);
      break;
    case 'u':
      o.username = string(optarg);
      break;
    case 'h':
      o.hostname = string(optarg);
      break;
    default:
      break;
    }
  }
}

namespace fs {

  void socketreader::run() {
    string data;

    while (true) {
      try {
	// decrypt
	(*parent) >> data;
      } catch (SOCKET_EXCEPTION_E e) {
	switch (e) {
	case SOCKET_ERROR:
	  cerr << "SOCKET_ERROR" << endl;
	  exit(1);
	  break;
	case SOCKET_NODATA:
	  return;
	  break;
	default:
	  break;
	}
      }
      cout << data;
      cout.flush();
    }
  }

  void client::setup() {
    stringstream port_string;
    port_string << port;

    address = socket_address(host,port_string.str());

    conn = socket(AF_INET,SOCK_STREAM,0);
  }

  void client::handshake() {
    string input;
    int64_t g,n,gxn;
    diffie_hellman diffie(g,n);

    conn >> g; // get diffie g

    conn >> n; // get diffie n
 
    conn >> gxn;     // wait for g^A % n

    // send g^B % n
    diffie.calculate_gxn();
    conn << diffie.get_gxn();

    diffie.set_other_gxn(gxn);

    char key = diffie.get_key();
    xor_c.set_key(key);

    // send username
    (*this) << username;
  }

  void client::get_user_input() {
    string input;

    do {
      // user hit CTRL-D
      if (cin.eof()) { 
	conn.close();
	break;
      }

      getline(cin,input);
      input += "\n"; // getline discards \n

      try {
	(*this) << input;
      } catch (exception & e) {
	cerr << "Error writing" << endl;
	// can't write any more
	// exit gracefully
	break;
      }
    } while (input != "DONE\n");
  }

  void client::connect(string host, short port, string username) {
    this->host = host;
    this->port = port;
    this->username = username;

    setup();

    conn.connect( address );

    socketreader r;
    r.parent = this;
    r.start();

    try {
      handshake();
    } catch (SOCKET_EXCEPTION_E e) {
      cerr << "Error in handshake." << endl;
      return;
    }

    //cerr << "get_user_input()" << endl;
    try {
      get_user_input();
    } catch (SOCKET_EXCEPTION_E e) {
      cerr << "Error getting user input." << endl;
      return;
    }

    // wait for report from server
    r.join();

    conn.close();
    cerr << "Connection is closed." << endl;
  }

  client& client::operator<<(const string & data) {
    xor_c.new_message();
    xor_c << data;

    conn << xor_c.get_string();

    return *this;
  }

  client& client::operator>>(string & var) {
    string input;
    conn >> input;

    xor_c.new_message();
    xor_c << input;

    var.assign(xor_c.get_string());

    return *this;
  }
} // namespace fs
// ----------------------------------------------------------------
int main(int argc, char * argv[]) {
  // prints banner
  printf("%s, %s <%s>\n\n",PROGRAM_NAME,AUTHOR,EMAIL);

  // get command line options
  Options o;
  parse_opts(argc,argv,o);

  if (o.username.empty()) {
    // username is not on command line
    // ask for it

    cout << "Enter Username: ";
    getline (cin,o.username);
  }

  fs::client c;
  c.connect(o.hostname,o.port,o.username);

  return 0;
}
