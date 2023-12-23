/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

/**
 *
 * @author franksuarez
 */
public class XorCipherTest {
    
    public XorCipherTest() {
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
     * Test of transformInt method, of class XorCipher.
     */
    @Test
    public void testTransformInt() {
        System.out.println("transformInt");
        
        int n = Integer.parseUnsignedInt("1010", 2);
        int key = Integer.parseUnsignedInt("1001", 2);
        int expResult = Integer.parseUnsignedInt("11", 2);
        int result = XorCipher.transformInt(n, key);
        
        System.out.printf("n\t= %16s%n",Integer.toBinaryString(n));
        System.out.printf("key\t= %16s%n",Integer.toBinaryString(key));
        System.out.printf("result\t= %16s%n",Integer.toBinaryString(result));
        assertEquals(expResult, result);
    }

    /**
     * Test of transformByte method, of class XorCipher.
     */
    @Test
    public void testTransformByte() {
        System.out.println("transformByte");
        byte n = Byte.parseByte("00011010",2);
        byte key = Byte.parseByte("00101001",2);
        byte expResult = Byte.parseByte("110011", 2);
        byte result = XorCipher.transformByte(n, key);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of transformChar method, of class XorCipher.
     */
    @Test
    public void testTransformChar() {
        System.out.println("transformChar");
        char c = ' ';
        char key = ' ';
        char expResult = ' ';
        char result = XorCipher.transformChar(c, key);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of repeatedKey method, of class XorCipher.
     */
    @Test
    public void testRepeatedKey() {
        System.out.println("repeatedKey");
        String key = "fox";
        int messageLength = 10;
        String expResult = "foxfoxfoxf";
        String result = XorCipher.repeatedKey(key, messageLength);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of repeatKeyBytes method, of class XorCipher.
     */
    @Test
    public void testRepeatKeyBytes() {
        System.out.println("repeatKeyBytes");
        byte[] key = {'a','b','c','d','e'};
        int messageLength = 5*5;
        byte[] result = XorCipher.repeatKeyBytes(key, messageLength);
        System.out.printf("%s%n",new String(result));
        
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }
    
    
    @Test
    public void ctestRepeatKeyByteString() {
        System.out.println("repeatKeyBytes");
        String keyString = "hello";
        byte[] keyBytes = keyString.getBytes();
        System.out.printf("num bytes = %d%n",keyBytes.length);
        int messageLength = keyString.length()*5+2;
        byte[] result = XorCipher.repeatKeyBytes(keyString.getBytes(), messageLength);
        System.out.printf("%s%n",new String(result));
        
    }

    
}
