#include <iostream>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <typeinfo>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <stdio.h>
#include <memory>
#include <string.h>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
#include <unistd.h>
using namespace std;

int main()
{	while(1) {
		string input;
		vector<char*> cmd_tok;
		vector<char*> parser;
		vector<char*> and_cmd;
		vector<char*> and_pars;

		cout << getlogin() << "$ " << endl;
		getline(cin, input);
		if(input == "exit") {
			return 0;
		}
		size_t pound_sign = input.find("#");
		string input_pound = input.substr(0, pound_sign);
		char* input_char = new char[input_pound.length() + 1];
		strcpy(input_char, input_pound.c_str());
		char* args = strtok(input_char, ";");

		while (args != 0) {
			cmd_tok.push_back(args);
			args = strtok(NULL,";");
		}

	for (int j = 0; j < cmd_tok.size(); j++) {	
		if (string(cmd_tok[j]).find("&&") == std::string::npos) {
			parser.clear();
			char* args4 = strtok(cmd_tok[j], " ");

			while (args4 != 0) {
				parser.push_back(args4);
				args4 = strtok(NULL, " ");
			}
			char *exec_cmd[parser.size()+1];
			for (int i = 0; i < parser.size(); i++)
			{
				exec_cmd[i] = parser[i];
			}

			exec_cmd[parser.size()] = NULL;
			char *cmd = parser[0];
			int pid = fork();

			if(pid == -1) {
    				perror("fork");
    				exit(1);
			}

			else if (pid == 0) {	
				execvp(cmd, exec_cmd);
			}		

			else {
				wait(0);
			}
		}

		else if(string(cmd_tok[j]).find("&&") != std::string::npos || string(cmd_tok[j]).find("||") != std::string::npos) {
			and_cmd.clear();
			char* args4 = strtok(cmd_tok[j], "&&");
			while (args4 != 0) {
				and_cmd.push_back(args4);
				args4 = strtok(NULL, "&&");
			}
			for (int k = 0; k < and_cmd.size(); k++) {
				and_pars.clear();
				char* args3 = strtok(and_cmd[k], " ");
				while (args3 != 0) {
					and_pars.push_back(args3);
					args3 = strtok(NULL, " ");
				}
				char* exec_cmd[and_pars.size()+1];
				for (int i = 0; i < and_pars.size(); i++) {
					exec_cmd[i] = and_pars[i];
				}
				exec_cmd[and_pars.size()] = NULL;
				char* cmd = and_pars[0];
				int status;
				int pid = fork();
					if(pid == -1) {
						perror("fork");
						exit(1);
					}
					if (pid == 0) {	
						if ((status = execvp(cmd, exec_cmd)) == -1) {
							goto quitthis;
						} 
					}		
					else {
						wait(0);
					}
				}	
			}
		}		
		quitthis: if (errno != 0) {
			cout << "error" << endl;
		}
		delete[] input_char;
	}
	return 0;
}

