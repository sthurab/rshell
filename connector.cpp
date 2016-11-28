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

#include "connector.h"
#include "andOp.cpp"
#include "orOp.cpp"
using namespace std;

connector::connector(){}

connector::connector(char* cmd_connect) {
    cmd = cmd_connect;
}

void connector::exec() {
    string str_dup = string(cmd);
    // clear vector
	cmd_vect.clear();
    char* tok_cmdA = strtok(cmd, "&&||");
    while (tok_cmdA != 0) {
        cmd_vect.push_back(tok_cmdA);
        tok_cmdA = strtok(NULL, "&&||");
    }
	// clear vector
    connector_vect.clear();
    char* char_dup = new char[str_dup.length() + 1];
    strcpy(char_dup, str_dup.c_str());
    char* tok_cmdB = strtok(char_dup, " ");
    while (tok_cmdB != 0) {
        if (string(tok_cmdB) == "&&" || string(tok_cmdB) == "||") {
            connector_vect.push_back(tok_cmdB);
        }
        tok_cmdB = strtok(NULL, " ");
    }
	// clear vector
    stat_vect.clear();
    for (unsigned it=0; it < connector_vect.size(); it++) {
        if (it == 0) {
            if (connector_vect[it] == "&&") {
                executor* from_left = new executor(cmd_vect[it]);
                executor* from_right = new executor(cmd_vect[it+1]);
                andOp* and_oper = new andOp(from_left, from_right);
                and_oper->exec();
                stat_vect.push_back(and_oper->cmd_stat());
            }
            else if (connector_vect[it] == "||") {
                executor* from_left = new executor(cmd_vect[it]);
                executor* from_right = new executor(cmd_vect[it+1]);
                orOp* or_oper = new orOp(from_left, from_right);
                or_oper->exec();
                stat_vect.push_back(or_oper->cmd_stat());
            }
        } // end of if
        else {
            if (connector_vect[it] == "&&") {
                if (stat_vect[it-1] == 0) {
                    executor* nxt_cmd = new executor(cmd_vect[it+1]);
                    nxt_cmd->exec();
                    stat_vect.push_back(nxt_cmd->cmd_stat());
                }
            }
            else if (connector_vect[it] == "||") {
                if (stat_vect[it-1] == 1) {
                    executor* nxt_cmd = new executor(cmd_vect[it+1]);
                    nxt_cmd->exec();
                    stat_vect.push_back(nxt_cmd->cmd_stat());
                }
            }
        } // end of else
    } // end of loop
}

int connector::cmd_stat() {
    return 0;
}
