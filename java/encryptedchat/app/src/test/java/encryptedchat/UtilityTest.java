/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit5TestClass.java to edit this template
 */
package encryptedchat;

import java.util.ArrayList;
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
     * Test of isPrimitiveRootModuloN method, of class Utility.
     */
    @Test
    public void testIsPrimitiveRootModuloN() {
        System.out.println("isPrimitiveRootModuloN");
        int g = 0;
        int n = 0;
        Utility.isPrimitiveRootModuloN(g, n);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of generateCoprimeList method, of class Utility.
     */
    @Test
    public void testGenerateCoprimeList() {
        System.out.println("generateCoprimeList");
        int value = 0;
        ArrayList<Integer> expResult = null;
        ArrayList<Integer> result = Utility.generateCoprimeList(value);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isCoprime method, of class Utility.
     */
    @Test
    public void testIsCoprime() {
        System.out.println("isCoprime");
        int a = 0;
        int b = 0;
        boolean expResult = false;
        boolean result = Utility.isCoprime(a, b);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of primitiveRootModuloN method, of class Utility.
     */
    @Test
    public void testPrimitiveRootModuloN() {
        System.out.println("primitiveRootModuloN");
        int g = 6;
        int n = 16;
        Utility.primitiveRootModuloN(g, n);
        // TODO review the generated test code and remove the default call to fail.
        //fail("The test case is a prototype.");
    }

    /**
     * Test of congruence method, of class Utility.
     */
    @Test
    public void testCongruence() {
        System.out.println("congruence");
        int a = 0;
        int b = 0;
        int modulo = 0;
        boolean expResult = false;
        boolean result = Utility.congruence(a, b, modulo);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of integerFactorization method, of class Utility.
     */
    @Test
    public void testIntegerFactorization() {
        System.out.println("integerFactorization");
        int n = 0;
        ArrayList<Integer> expResult = null;
        ArrayList<Integer> result = Utility.integerFactorization(n);
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
        int a = 0;
        int b = 0;
        int expResult = 0;
        int result = Utility.greatestCommonDivisor(a, b);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of isPrime method, of class Utility.
     */
    @Test
    public void testIsPrime() {
        System.out.println("isPrime");
        int value = 0;
        boolean expResult = false;
        boolean result = Utility.isPrime(value);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }

    /**
     * Test of eulerTotient method, of class Utility.
     */
    @Test
    public void testEulerTotient() {
        System.out.println("eulerTotient");
        int value = 0;
        int expResult = 0;
        int result = Utility.eulerTotient(value);
        assertEquals(expResult, result);
        // TODO review the generated test code and remove the default call to fail.
        fail("The test case is a prototype.");
    }
    
}
