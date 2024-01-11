/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import java.security.Provider;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 *
 * @author franksuarez
 */
public class CryptoTest {
    
    public CryptoTest() {
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
     * Test of setup method, of class Crypto.
     */
    @Test
    public void testSetup() throws Exception {
        System.out.println("setup");
        Crypto instance = new Crypto();
        instance.setup();
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of encrypt method, of class Crypto.
     */
    @Test
    public void testEncrypt() throws Exception {
        System.out.println("encrypt");
        byte[] message = "hello".getBytes();
        Crypto instance = new Crypto();
        instance.setup();
        
        byte[] expResult = null;
        byte[] result = instance.encrypt(message);
        
        System.out.printf("result: %s%n", result);
        
        //assertArrayEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of decrypt method, of class Crypto.
     */
    @Test
    public void testDecrypt() throws Exception {
        System.out.println("decrypt");
        byte[] message = null;
        Crypto instance = new Crypto();
        byte[] expResult = null;
        byte[] result = instance.decrypt(message);
        assertArrayEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of listProviders method, of class Crypto.
     */
    @Test
    public void testListProviders() {
        System.out.println("listProviders");
        Crypto.listProviders();
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of displayProviderInfo method, of class Crypto.
     */
    @Test
    public void testDisplayProviderInfo() {
        System.out.println("displayProviderInfo");
        Provider p = null;
        Crypto.displayProviderInfo(p);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
