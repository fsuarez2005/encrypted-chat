/*
# TODO:
- [] Standardize message data type
- [] Standardize key data type
- [x] Implement a stateful xor cipher class
- [] 




Message data types
* String
 * Easy to use
 * Can be converted to other data types
 * getButes just downcasts char to 1 byte. it does not 
* char[]
 * Similar to String
 * Due to character encoding, char size may be different
* byte[]
 * Conversion needs to be portable
 * The most consistent

The message and the key should be of the same character set and have the
same byte order. 


*/

package encryptedchat;

/**
 *
 * @author franksuarez
 */
public class XorCipher {
    String key;
    int keyOffset;

    public void newMessage() {
        this.keyOffset = 0;
    }
    
    public String encode(String message) {
        return transform(message);
    }
    
    public String decode(String message) {
        return transform(message);
    }
    
    
    /** 
     * 
     * 
     * @param message
     * @return 
     */
    private String transform(String message) {
        // encode message with key
        // return encoded message
        // store key offset
        String output = "";
        
        for(int n = 0; n < message.length(); n++) {
            output += (char) (message.charAt(n) ^ this.key.charAt((n+this.keyOffset) % this.key.length()));
        }
        
        this.keyOffset = message.length() % this.key.length();
        return output;
    }

}
