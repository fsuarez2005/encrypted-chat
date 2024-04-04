/** \file fs_xor.h
 ** \brief bitwise encryption cipher
 **/

#include <string>
#include <iostream>

using namespace std;




#ifndef xorcipher_h
#define xorcipher_h

class xor_cipher {
    private:
    // not null terminated
    string key;
    size_t key_offset;
    string buffer;

    public:
    void encrypt_new(const string message,
                     const string key);
    
    
    // testing purpose
    void test();



    // multi-char encryption
    static size_t encrypt(  char * dest,
                            const char * message,
                            size_t message_len,
                            const char * key,
                            size_t key_len,
                            size_t key_offset);
    // -------------------------------------------------
    xor_cipher();
    ~xor_cipher();
    // -------------------------------------------------
    /// prepare for new message with same key
    void new_message();
    // -------------------------------------------------
    /// sets encryption key
    void set_key(string key);
    // -------------------------------------------------
    /// sets encryption key
    void set_key(char key);
    // -------------------------------------------------
    /// get current text
    string get_string();
    // -------------------------------------------------
    /// appends to encrypted buffer
    xor_cipher& operator<<(const string & message);
    // -------------------------------------------------
    /// assigns whole buffer to string_out
    xor_cipher& operator>>(string & string_out);
};

#endif //XORCIPHER_H
