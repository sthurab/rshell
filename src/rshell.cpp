#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

#include "rshell.h"
#include "Trans_rshell.cpp"
using namespace std;

rshell::rshell() {
	while(1) {
		cout << getlogin() << "$ ";
		getline(cin, user_input_str);
		if(user_input_str == "exit") {
			exit(0);
		}
		size_t symbol_position = user_input_str.find("#");
		string user_input_str_wo_syms = user_input_str.substr(0,symbol_position);
		Trans_rshell* shell = new Trans_rshell(user_input_str_wo_syms);
		shell->interpret();
	}
}