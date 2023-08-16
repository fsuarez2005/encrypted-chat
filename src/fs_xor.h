/** \file fs_xor.h
 ** \brief bitwise encryption cipher
 **/

#ifndef FS_XOR_H
#define FS_XOR_H

using namespace std;

#include <iostream>
#include <sstream>
#include <string>

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <climits>

namespace fs {
  class xor_cipher {
  private: 
    // not null terminated
    string key;
    size_t key_offset;
    string buffer;

  public:
    // multi-char encryption
    static size_t encrypt(char * dest,
			  const char * message,
			  size_t message_len,
			  const char * key,
			  size_t key_len,
			  size_t key_offset) {
      for (unsigned int n = 0; n < message_len; n++ ) {
	dest[n] = message[n] ^ key[key_offset];

	key_offset++;
	key_offset %= key_len;
      }
      return key_offset;
    }
    // -------------------------------------------------
    xor_cipher() :
      key_offset(0),
      buffer(""),
      key("")
    {}
    ~xor_cipher() {}
    // -------------------------------------------------
    /// prepare for new message with same key
    void new_message() {
      buffer = "";
      key_offset = 0;
    }
    // -------------------------------------------------
    /// sets encryption key
    void set_key(string key) {
      this->key = key;
    }
    // -------------------------------------------------
    /// sets encryption key
    void set_key(char key) {
      this->key = key;
    }
    // -------------------------------------------------
    /// get current text
    string get_string() {
      return buffer;      
    }
    // -------------------------------------------------
    /// appends to encrypted buffer
    xor_cipher& operator<<(const string & message) {
      // encrypt and append to cipher buffer
      char* dest_buffer = new char[message.size()];

      key_offset = encrypt(dest_buffer,
			   message.c_str(),
			   message.size(),
			   key.c_str(),
			   key.size(),
			   key_offset);

      buffer.append(dest_buffer,message.size());
      delete[] dest_buffer;
      return *this;
    }
    // -------------------------------------------------
    /// assigns whole buffer to string_out
    xor_cipher& operator>>(string & string_out) {
      string_out = buffer;
      buffer.clear();
      return *this;
    }
  };
} // namespace fs
#endif // FS_XOR_H
