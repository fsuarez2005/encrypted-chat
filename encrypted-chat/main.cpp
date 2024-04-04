
//
//  main.cpp
//
//  Created by Frank Suarez on 8/12/23.
//

#include <iostream>
#include <cstdlib>

using namespace std;

#include "xorcipher.h"
#include "utility.h"


void create_repeated_key() {
    string key{"mykey"};
    string message{"the new password is 12345"};
    
    
    
    // repeat key until required length >= length of message
    // count >= message_length / key_length
    // count is an integer
    
    float message_len = message.length();
    float key_length = key.length();
    
    float count = message_len / key_length;
    
    cout << "count: " << count;
    
    
    //string repeated_key = repeat_string(key, 10);
    
    
    // crop repeat key to message length
    
    
    
}



int main(int argc, const char * argv[]) {

    
    
    
    
    
    
    return EXIT_SUCCESS;
}
