/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

/**
 *
 * @author franksuarez
 */
public class XorCipher {
    
    public static byte[] repeatKeyBytes(byte[] key, int messageLength) {
        int iterations = messageLength / key.length;
        int extra = messageLength % key.length;
        
        byte[] newKey = new byte[messageLength];
        
        for(int n = 0; n < iterations; n++) {
            System.arraycopy(key, 0, newKey, key.length * n, key.length);
        }
        
        
        // extra calculation
        // start = key.length * iterations
        System.arraycopy(key, 0, newKey, key.length*iterations, extra);
        
        return newKey;
    }
    
    /**
     * Repeat the String key for the messageLength
     * @param key
     * @param messageLength
     * @return 
     */
    public static String repeatedKey(String key, int messageLength) {
        int iterations = messageLength / key.length();
        int extra = messageLength % key.length();
        String newKey = key.repeat(iterations) + key.substring(0, extra);
        return newKey;
    }
    
    
    public static byte transformByte(byte n, byte key) {
        return (byte) (n ^ key);
    }
    
    
    public static int transformInt(int n, int key) {
        return n ^ key;
    }
    
    public static char transformChar(char c, char key) {
        return ' ';
    }
}
