/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import java.util.*;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import static org.junit.jupiter.api.Assertions.assertArrayEquals;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.fail;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;


/**
 *
 * @author franksuarez
 */
public class UtilityTest {
    
    public UtilityTest() {
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
     * Test of repeat method, of class Utility.
     */
    @Test
    public void testRepeat() {
        System.out.println("repeat");
        byte[] data = null;
        int count = 0;
        byte[] expResult = null;
        byte[] result = Utility.repeat(data, count);
        assertArrayEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of primitiveRootModuloN method, of class Utility.
     */
    @Test
    public void testPrimitiveRootModuloN() {
        System.out.println("primitiveRootModuloN");
        double g = 0.0;
        double n = 0.0;
        Utility instance = new Utility();
        instance.primitiveRootModuloN(g, n);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

   

    /**
     * Test of isPrime method, of class Utility.
     */
    @Test
    public void testIsPrime() {
        System.out.println("isPrime");
        int value = 111;
        boolean expResult = true;
        boolean result = Utility.isPrime(value);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of integerFactorization method, of class Utility.
     */
    @Test
    public void testIntegerFactorization() {
        System.out.println("integerFactorization");
        int n = 100090908;
        //ArrayList<Integer> expResult = new ArrayList<>(Arrays.asList(2,5));
        ArrayList<Integer> result = Utility.integerFactorization(n);
        System.out.println(result);

        //assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of integerFactorizationFast method, of class Utility.
     */
    @Test
    public void testIntegerFactorizationFast() {
        System.out.println("integerFactorizationFast");
        int n = 0;
        ArrayList<Integer> expResult = null;
        ArrayList<Integer> result = Utility.integerFactorizationFast(n);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of greatestCommonDivisor method, of class Utility.
     */
    @Test
    public void testGreatestCommonDivisor() {
        System.out.println("greatestCommonDivisor");
        int a = 10;
        int b = 100;
        int expResult = 10;
        int result = Utility.greatestCommonDivisor(a, b);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }



    
}
