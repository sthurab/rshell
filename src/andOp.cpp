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

#include "andOp.h"
using namespace std;

andOp::andOp(){}

andOp::andOp(base *first, base *second) {
    l = first;
    r = second;
}

void andOp::exec() {
    l->exec();
    if (l->cmd_stat() == 0) {
        r->exec();
        if (r->cmd_stat() == 0) {
            status = 0;
        }
        else {
            status = 1;
        }
    }
    else {
        status = 1;
    }
}

int andOp::cmd_stat() {
    return status;
}
