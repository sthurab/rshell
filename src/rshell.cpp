#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <vector>

#include "parser.cpp" //
#include "rshell.h"

using namespace std;

rshell::rshell() {
    while(1) {
        cout << getlogin() << "$ ";
        getline(cin, input_inc);
        if (input_inc == "exit") {
            exit(0);
        }
        size_t location_sym = input_inc.find("#");
        string input_wo_sym = input_inc.substr(0,location_sym);
        parser* p = new parser(input_wo_sym);
        p->interpret();
    }
}
