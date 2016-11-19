#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>

#include "precedence.cpp"
#include "connectors.cpp"
#include "Trans_rshell.h"
#include "Cmd_only.cpp"
using namespace std;

Trans_rshell::Trans_rshell(){}
Trans_rshell::Trans_rshell(string input) {
	user_input = input;
}
void Trans_rshell::interpret() {
	char* char_input = new char[user_input.length() + 1];
	strcpy(char_input, user_input.c_str());
	char* cmdToken = strtok(char_input, ";");
	while (cmdToken != 0) {
		cmds.push_back(cmdToken);
		cmdToken = strtok(NULL, ";");
	}
	for (unsigned i = 0; i < cmds.size(); i++) {	
		if (string(cmds[i]).find("(") != string::npos && string(cmds[i]).find(")") != string::npos) {		
			Precedence* cmd_paren = new Precedence(cmds[i]);
			cmd_paren->chk_paren();
		}
		else if (string(cmds[i]).find("&&") == string::npos && string(cmds[i]).find("||") == string::npos) {
			Cmd_only* cmd1 = new Cmd_only(cmds[i]);
			cmd1->execute();
		}
		else {	
			Connectors* cmd1_connect = new Connectors(cmds[i]);
			cmd1_connect->execute();
		}
	}
	delete[] char_input;
}