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

#include "orOp.h"
using namespace std;

orOp::orOp(){}

orOp::orOp(base *first, base *second) {
    l = first;
    r = second;
}

void orOp::exec() {
    l->exec();
    if(l->cmd_stat() == 1) {
        r->exec();
        if(r->cmd_stat() == 0) {
            status = 0;
        }
        else {
            status = 1;
        }
    }
    else {
        status = 0;
    }
}

int orOp::cmd_stat() {
    return status;
}
