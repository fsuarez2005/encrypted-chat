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
    public static int transformInt(int n, int key) {
        return n ^ key;
    }
    
    public static char transformChar(char c, char key) {
        return ' ';
    }
}
