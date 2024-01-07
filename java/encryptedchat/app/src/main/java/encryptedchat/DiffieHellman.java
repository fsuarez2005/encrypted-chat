/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

/**
 *
 * @author franksuarez
 */
public class DiffieHellman {
    // https://en.wikipedia.org/wiki/Diffie%E2%80%93Hellman_key_exchange
    // sharedModulus (p)
    // sharedBase (g)
    // mySecret (a)
    // send other A = g^a mod p
    //      A = (sharedModulus^secret mod sharedBase)
    // get B = (sharedModulus^othersSecret mod sharedBase) from other
    // sharedSecret = B^A mod P
    //      othersSecret^mySecret mod sharedBase
    // other will compute sharedSecret with 
    //      A^B mod p
    // 
    
    int g;
    int n;
    int gxn; // server's g^x %n
    int gbn; // g^x % n from client
    int x; // private number
    
    int seed;
    
    public static void modularPower(int base, int exponent, int modulus) {}

    
    public void setupRandomGenerator() {}
    
    public void generatePrivate() {}
       
    
}
