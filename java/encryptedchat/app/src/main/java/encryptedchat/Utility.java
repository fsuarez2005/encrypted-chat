/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

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

    
    
}
