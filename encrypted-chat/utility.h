//
//  utility.h
//  encrypted-chat
//
//  Created by Frank Suarez on 8/17/23.
//

#include <string>
#include <iostream>


#ifndef utility_h
#define utility_h




string repeat_string(string src, size_t count) {
    string outstring{""};

    
    for (size_t n = 0; n < count; n++) {
        outstring.append(src);
    }
    return outstring;
    
}




#endif /* utility_h */
