//
//  main.cpp
//  test
//
//  Created by Frank Suarez on 8/17/23.
//

#include <iostream>
#include <cstdlib>

using namespace std;

#include "utility.h"

int test_repeat_string() {
    string instring{"teststring"};
    size_t count = 3;
    string outstring = repeat_string(instring, count);
    
    int exitstatus{EXIT_FAILURE};
    
    
    if (outstring == "teststringteststringteststring") {
        cout << __FUNCTION__ << " works." << endl;
        exitstatus = EXIT_SUCCESS;
    } else {
        cout << __FUNCTION__ << " failed." << endl;
        exitstatus = EXIT_FAILURE;
    }
    
    return exitstatus;
    
}



int main(int argc, const char * argv[]) {
    
    
    return 0;
}
