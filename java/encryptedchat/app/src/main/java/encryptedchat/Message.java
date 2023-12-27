/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package encryptedchat;

import java.nio.ByteOrder;

/** A portable message.
 *
 * @author franksuarez
 */
public class Message {
    byte[] data;
    
    public void setData(String dataString) {
        // char is usually two bytes
        // endianness is 
        
        String byteOrder = ByteOrder.nativeOrder().toString();
        
        System.out.printf("byte order = %s%n", byteOrder);
        
        
        
    
    
    }
    
    
    
    
    
}
