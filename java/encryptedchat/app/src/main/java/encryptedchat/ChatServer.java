/** Chat Server Class.
 *
 */
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
package encryptedchat;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Multi-Threaded Chat Server.
 *
 * @author franksuarez
 */
public class ChatServer {
    private static final Logger logger = Logger.getLogger(ChatServer.class.getName());
    
    boolean run = true;
    ServerOptions options;
    ServerSocket listenSocket;
    
    protected void processConnection(Socket s) {
        // create Connection object
        // create Thread for connection
        
        Connection clientConnection = new Connection();
        
        ConnectionHandler handler = new ConnectionHandler();
        handler.setConnection(clientConnection);
        
        Thread t = new Thread(handler);
        t.start();
    }
    
    protected Socket listenForConnection() {
        Socket connSocket = null;
        try {
            connSocket = listenSocket.accept();
        } catch (IOException ex) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        logger.log(Level.INFO, "Received connection.");
        
        return connSocket;
    }
    
    protected void serverLoop() {
        Socket currentClient;
        while (run) {
            currentClient = listenForConnection();
            processConnection(currentClient);
            
            try {
                currentClient.close();
            } catch (IOException ex) {
                // cannot close socket for some reason (?)
                
                Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    public ChatServer() {}

    public void setServerOptions(ServerOptions options) {
        this.options = options;
    }
    public ServerOptions getServerOptions() {
        return this.options;
    }
    
    /**
     * Initializes server.
     */
    protected void setup() {
        // use default options
        options = new ServerOptions();
        
        
        logger.log(Level.INFO,String.format("Chat Server listening on %s:%s.",options.ipAddress,options.listenPort));
        
        try {
            listenSocket = new ServerSocket(options.listenPort);
            listenSocket.setReuseAddress(options.reuseAddres);
        } catch (IOException ex) {
            Logger.getLogger(ChatServer.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    protected void tearDown() {}

    public void start() {
        setup();

        serverLoop();

        tearDown();
    }
}
