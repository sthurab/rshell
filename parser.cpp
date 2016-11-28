#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <vector>

#include "executor.cpp" //
#include "connector.cpp"
#include "parentheses.cpp"
#include "parser.h"
using namespace std;

parser::parser(){}

parser::parser(string str){
    input = str;
}

void parser::interpret() {
    char* input_char = new char[input.length() + 1];
    strcpy(input_char, input.c_str());
    char* tok_cmd = strtok(input_char, ";");
    while (tok_cmd != 0) {
        commands.push_back(tok_cmd);
        tok_cmd = strtok(NULL, ";");
    }
	// checking for parens, operators
    for (unsigned i=0; i < commands.size(); i++) {
        if (string(commands[i]).find("(") != string::npos && string(commands[i]).find(")") != string::npos) {
            parentheses* cmd_has_paren = new parentheses(commands[i]);
            cmd_has_paren->paren_chk();
        }
        else if (string(commands[i]).find("&&") == string::npos && string(commands[i]).find("||") == string::npos) {
            executor* cmd1 = new executor(commands[i]);
            cmd1->exec();
        }
        else {
            connector* cmd1_connect = new connector(commands[i]);
            cmd1_connect->exec();
        }
    }
    delete[] input_char;
}
