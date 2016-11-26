#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>
#include <vector>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "testor.h"
using namespace std;

// test cases 

test_cmd::test_cmd(){
}

test_cmd::test_cmd(std::vector<char*> test_in) {
    test_tokd = test_in;
}

void test_cmd::exec() {
    struct stat test_cmdA; /////
    string flag_test = test_tokd[1];
    if (flag_test == "-e") {
        if (stat(test_tokd[2], &test_cmdA) != -1) { ////////////////
            cout << "(True)\n";
            status = 0;
        }
        else {
            cout << "(False)\n";
            status = 1;
        }
    }
    else if (flag_test == "-f") {
        if (stat(test_tokd[2], &test_cmdA) != -1) {  ////////////////
            if (S_ISREG(test_cmdA.st_mode) == true) {
                cout << "(True)\n";
                status = 0;
            }
            else {
                cout << "(False)\n";
                status = 1;
            }
        }
        else {
            perror("status");
            status = 1;
        }
    }
    else if (flag_test == "-d") {
        if (stat(test_tokd[2], &test_cmdA) != -1) {  ////////////////
            if (S_ISDIR(test_cmdA.st_mode) == true) {
                cout << "(True)\n";
                status = 0;
            }
            else {
                cout << "(False)\n";
                status = 1;
            }
        }
        else {
            perror("status");
            status = 1;
        }
    }
    else if (flag_test != "-e" && flag_test != "-f" && flag_test != "-d") { 
        if (stat(test_tokd[1], &test_cmdA) != -1) {  ////////////////
            cout << "(True)\n";
            status = 0;
        }
        else {
            cout << "(False)\n";
            status = 1;
        }
    }
}

int test_cmd::cmd_stat() {
    return status;
}