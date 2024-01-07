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
    
    // todo
    public void primitiveRootModuloN(double g, double n) {
        
        for (double k = 1; k <= n; k++) {
            double gk = java.lang.Math.pow(g, k);
            
            System.out.printf("gk = %f%n",gk);
        }
        
        
    }
    
    
    /**
     * https://en.wikipedia.org/wiki/Trial_division
     * @param n
     * @return 
     */
    public static ArrayList<Integer> integerFactorizationFast(int n) {
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
    
    /**
     * https://en.wikipedia.org/wiki/Trial_division
     * @param n
     * @return 
     */
    public static ArrayList<Integer> integerFactorization(int n) {
        ArrayList<Integer> a = new ArrayList<>();
        int f = 2;
        
        while (n > 1) {
            if (n % f == 0) {
                a.add(f);
                n /= f;
                
            } else {
                
                f += 1;
            }
            
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
}
