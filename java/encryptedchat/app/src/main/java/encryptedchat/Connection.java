/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author franksuarez
 */
public class Connection {
    Socket clientSocket;
    // reference to containing server
    ChatServer parent;
    BufferedReader in;
    PrintWriter out;
    
    boolean autoFlushOutput;
    
    
    boolean closed = false;
    
    int elapsed;
    boolean loggedIn;
    int numMessages;
    boolean connected;
    String username;
    String prompt;
    String usernamePrompt;
    boolean showPrompt;

    DiffieHellman diffie;
    XorCipher cipher;
    
    public Connection() {}

    public Connection(Socket clientSocket) {
        this.clientSocket = clientSocket;
    }
    
    public void setup() {
        try {
            createReader();
        } catch (IOException ex) {
            Logger.getLogger(Connection.class.getName()).log(Level.SEVERE, "Unable to create reader.", ex);
        }
     
        try {
            createWriter();
        } catch (IOException ex) {
            Logger.getLogger(Connection.class.getName()).log(Level.SEVERE, "Unable to create writer.", ex);
        }
        
    }
    
    public ChatServer getParent() {
        return parent;
    }

    public void setParent(ChatServer parent) {
        this.parent = parent;
    }
    
    private void createWriter() throws IOException {
        this.out = new PrintWriter(this.clientSocket.getOutputStream(),true);
    }
    private void createReader() throws IOException {
        this.in = new BufferedReader(new InputStreamReader(this.clientSocket.getInputStream()));
    }
    
    public void close() throws IOException {
        this.closed = true;
        this.clientSocket.close();
    }
    
    // TODO
    public void send(String msg) {
        out.print(msg);
        out.flush();
    }
    
    // TODO
    public char[] recv(int size) {
        return null;
    }
    
    // TODO
    public String readLine() {
        
        return "";
    }
    
    
}
