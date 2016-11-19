#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>

#include "or.cpp"
#include "and.cpp"
#include "connectors.h"
using namespace std;

Connectors::Connectors(){}

Connectors::Connectors(char* cmd_connect) {
	cmd = cmd_connect;
}

void Connectors::execute() {
	string str_duplicate = string(cmd);
	cmd_vect.clear();
	char* cmdToken1 = strtok(cmd, "&&||");
	while(cmdToken1 != 0) {
		cmd_vect.push_back(cmdToken1);
		cmdToken1 = strtok(NULL, "&&||");
	}
	connector_vect.clear();
	char* char_duplicate = new char[str_duplicate.length() + 1];
	strcpy(char_duplicate, str_duplicate.c_str());
	char* cmdToken2 = strtok(char_duplicate, " ");
	while(cmdToken2 != 0) {
		if(string(cmdToken2) == "&&" || string(cmdToken2) == "||") {
			connector_vect.push_back(cmdToken2);
		}
		cmdToken2 = strtok(NULL, " ");
	} // end of while
	status_vect.clear();
	for(unsigned i = 0; i < connector_vect.size(); i++) {
		if (i == 0) {
			if (connector_vect[i] == "&&") {
				Cmd_only* left = new Cmd_only(cmd_vect[i]);
				Cmd_only* right = new Cmd_only(cmd_vect[i+1]);
				And* and_cmd = new And(left, right);
				and_cmd->execute();
				status_vect.push_back(and_cmd->the_status());
			}
			else if(connector_vect[i] == "||") {
				Cmd_only* left = new Cmd_only(cmd_vect[i]);
				Cmd_only* right = new Cmd_only(cmd_vect[i+1]);
				Or* or_cmd = new Or(left, right);
				or_cmd->execute();
				status_vect.push_back(or_cmd->the_status());
			}
		} // end of if
		else {
			if(connector_vect[i] == "&&") {
				if(status_vect[i-1] == 0) {
					Cmd_only* nxt_cmd = new Cmd_only(cmd_vect[i+1]);
					nxt_cmd->execute();
					status_vect.push_back(nxt_cmd->the_status());
				}
			}
			else if(connector_vect[i] == "||") {
				if (status_vect[i-1] == 1) {
					Cmd_only* nxt_cmd = new Cmd_only(cmd_vect[i+1]);
					nxt_cmd->execute();
					status_vect.push_back(nxt_cmd->the_status());
				}
			}
		} // end of else
	} // end of for loop
}
int Connectors::the_status()
{
	return 0;
}