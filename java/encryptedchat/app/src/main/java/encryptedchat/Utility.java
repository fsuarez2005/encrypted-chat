/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

import java.util.ArrayList;


/**
 *
 * @author franksuarez
 */
public class Utility {
    public static byte[] repeat(byte[] data, int count) {
        int newSize = data.length * count;
        byte[] out = new byte[newSize];
        
        for(int n = 0; n < count; n++) {
            System.arraycopy(data, 0, out, data.length*n, data.length);
        }
        return out;
    }
    
    public static void isPrimitiveRootModuloN(int g, int n) {
        throw new UnsupportedOperationException();
    }
    
    public static ArrayList<Integer> generateCoprimeList(int value) {
        ArrayList<Integer> out = new ArrayList<>();
        
        for (int n = 2; n <= value - 1; n++) {
            if (isCoprime(n,value)){
                out.add(n);
            }
        }
        return out;
    }
    
    
    /** Returns true if two integers are coprime.
     * 
     * @param a
     * @param b
     * @return 
     */
    public static boolean isCoprime(int a, int b) {
        return Utility.greatestCommonDivisor(a, b) == 1;
    }
    
    // todo
    public static boolean primitiveRootModuloN(int g, int n) {
        boolean out = true;

        int nTotient = eulerTotient(n);
        ArrayList<Integer> factors = integerFactorization(nTotient);

        for(int index = 0; index < factors.size(); index++) {
            int gPower = (int) Math.pow((double)g, (double)nTotient/factors.get(index));
            int gPowerN = gPower % n;
            
            out = (gPowerN == 1);
           
        }
        
        return out;
    }
    
    public static boolean congruence(int a, int b, int modulo) {
        return (a % modulo == b % modulo);
    }
    
    
    /**
     * https://en.wikipedia.org/wiki/Trial_division
     * @param n
     * @return 
     */
    public static ArrayList<Integer> integerFactorization(int n) {
        ArrayList<Integer> a = new ArrayList<>();
        int f = 3;
        
        while (n % 2 == 0) {
            a.add(2);
            n /= 2;
        }
        while (f * f <= n) {
            if (n % f == 0) {
                a.add(f);
                n /= f;
            } else {
                f += 2;
            }
            
        }
        if (n != 1) {
            a.add(n);
        }
        return a;
    }

    
    /** Returns Greatest Common Divisor using Euclid's algorithm.
     * https://en.wikipedia.org/wiki/Euclidean_algorithm
     * @param a
     * @param b
     * @return 
     */
    public static int greatestCommonDivisor(int a, int b) {
        while (a != b) {
            if (a > b) {
                a = a - b;
            } else { // a < b
                b = b - a;
            }
        }
        return a;
    }
    
    
    /** Unoptimized prime checker.
     * 
     * @param value
     * @return 
     */
    public static boolean isPrime(int value) {
        boolean output = true;
        
        for (int n = 2; n <= Math.sqrt(value); n++) {
            if (value % n == 0) {
                output = false;
                break;
            }
        }
        
        return output;
    }
    
    /** Euler's Totient function.
     * 
     * 
     * 
     * @param value
     * @return
     * @see isCoprime
     * 
     */
    public static int eulerTotient(int value) {
        int count = 0;
        
        for(int index = 1; index < value; index++) {
            if (isCoprime(value, index)) {
                count++;
            }
            
        }
        return count;
    }
}
