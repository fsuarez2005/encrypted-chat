/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import java.util.HashSet;
import java.util.Set;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author franksuarez
 */
public class ChatServerTest {
    
    public ChatServerTest() {
    }
    
    @BeforeAll
    public static void setUpClass() {
    }
    
    @AfterAll
    public static void tearDownClass() {
    }
    
    @BeforeEach
    public void setUp() {
    }
    
    @AfterEach
    public void tearDown() {
    }

    /**
     * Test of setup method, of class ChatServer.
     */
    @Test
    public void testSetup() {
        System.out.println("setup");
        ChatServer instance = new ChatServer();
        instance.setup();
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of removeChatLog method, of class ChatServer.
     */
    @Test
    public void testRemoveChatLog() {
        System.out.println("removeChatLog");
        ChatServer instance = new ChatServer();
        instance.removeChatLog();
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of start method, of class ChatServer.
     */
    @Test
    public void testStart() {
        System.out.println("start");
        ChatServer instance = new ChatServer();
        instance.setPort(8080);
        
        
        instance.start();
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of broadcaseMessage method, of class ChatServer.
     */
    @Test
    public void testBroadcaseMessage() {
        System.out.println("broadcaseMessage");
        Connection c = null;
        String msg = "";
        ChatServer instance = new ChatServer();
        instance.broadcaseMessage(c, msg);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of logMessage method, of class ChatServer.
     */
    @Test
    public void testLogMessage() {
        System.out.println("logMessage");
        String msg = "";
        ChatServer instance = new ChatServer();
        instance.logMessage(msg);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of sendChatLog method, of class ChatServer.
     */
    @Test
    public void testSendChatLog() {
        System.out.println("sendChatLog");
        Connection c = null;
        ChatServer instance = new ChatServer();
        instance.sendChatLog(c);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of callbackClientDone method, of class ChatServer.
     */
    @Test
    public void testCallbackClientDone() {
        System.out.println("callbackClientDone");
        int connectionId = 0;
        ChatServer instance = new ChatServer();
        instance.callbackClientDone(connectionId);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
