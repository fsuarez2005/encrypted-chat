/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author franksuarez
 */
public class ConnectionHandler implements Runnable {
    private static final Logger logger = Logger.getLogger(ConnectionHandler.class.getName());
    
    private Connection clientConnection;

    public Connection getConnection() {
        return clientConnection;
    }

    public void setConnection(Connection clientConnection) {
        this.clientConnection = clientConnection;
    }
    
    
    
    public ConnectionHandler() {}
    
    
    
    
    @Override
    public void run() {
        logger.log(Level.INFO, "hello");
        clientConnection.send("hi");
        //throw new UnsupportedOperationException("Not supported yet."); // Generated from nbfs://nbhost/SystemFileSystem/Templates/Classes/Code/GeneratedMethodBody
    }

    
    
    
    
}
