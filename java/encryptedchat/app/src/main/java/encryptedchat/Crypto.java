/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

import java.security.InvalidKeyException;
import java.security.KeyPair;
import java.security.KeyPairGenerator;
import java.security.NoSuchAlgorithmException;
import java.security.PrivateKey;
import java.security.Provider;
import java.security.PublicKey;
import java.security.Security;
import java.util.Set;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;

/** Top-level class for cryptography.
 *
 * @author franksuarez
 */
public class Crypto {
    KeyPairGenerator keygen;
    PublicKey pubkey;
    PrivateKey privkey;
    
    Cipher ciph;
    
    // DiffieHellman
    
    // Cipher
    
    private static final String ALGORITHM = "DiffieHellman";
    private static final String CIPHER = "AES/CBC/PKCS5Padding";
    
    private static final int KEYSIZE = 512;
    
    // =========================================================================
    
    public static void listProviders() {
        Provider[] providers = Security.getProviders();
        
        for(Provider p : providers) {
            //System.out.printf("Provider: %s%n", p.getName());
            
            displayProviderInfo(p);
        }
    }
    
    
    public static void displayProviderInfo(Provider p) {
        System.out.printf("Provider: %s%n",p.getName());
        
        Set<Provider.Service> services = p.getServices();
        for(Provider.Service s : services) {
            System.out.printf("Type: %s / Algorithm: %s%n",s.getType(),s.getAlgorithm());
            
            
        }
        System.out.println("==========================");
    }
    
    
    // =========================================================================
    
    
    
    public void setup() throws NoSuchAlgorithmException, NoSuchPaddingException {
        
        
        keygen = KeyPairGenerator.getInstance(ALGORITHM);
        keygen.initialize(KEYSIZE);
        
        KeyPair keys = keygen.generateKeyPair();
        PublicKey pub = keys.getPublic();
        PrivateKey priv = keys.getPrivate();
        
        System.out.printf("pub algo: %s%n",pub.getAlgorithm());
        
        pubkey = keys.getPublic();
        privkey = keys.getPrivate();
        
        ciph = Cipher.getInstance(CIPHER);  
    }
    
    public byte[] encrypt(byte[] message) throws InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        ciph.init(Cipher.ENCRYPT_MODE, pubkey);
        ciph.update(message);
        byte[] out = ciph.doFinal();
        
        return out;
    }
    
    public byte[] decrypt(byte[] message) throws InvalidKeyException, IllegalBlockSizeException, BadPaddingException {
        ciph.init(Cipher.DECRYPT_MODE, privkey);
        ciph.update(message);
        byte[] out = ciph.doFinal();
        return out;
    }
    
    
}
