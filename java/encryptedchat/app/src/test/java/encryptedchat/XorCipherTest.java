/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertEquals;
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
    
}
