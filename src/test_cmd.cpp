#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "test_cmd.h"
using namespace std;

test_cmd::test_cmd(){}
test_cmd::test_cmd(std::vector<char*> test_in) {
	tokd_test = test_in;
}
void test_cmd::execute() {
	struct stat tc;
	string flag_test = tokd_test[1];
	if(flag_test == "-e") {
		if (stat(tokd_test[2], &tc) != -1) {
			cout << "(True)\n";
			status = 0;
		}
		else {
			cout << "(False)\n";
			status = 1;
		}
	}
	else if(flag_test == "-f") {
		if(stat(tokd_test[2], &tc) != -1) {
			if (S_ISREG(tc.st_mode) == true) {
				cout << "(True)\n";
				status = 0;
			}
			else {
				cout << "(False)\n";
				status = 1;
			}
		}
		else {
			perror("stat");
			status = 1;
		}
	}
	else if(flag_test == "-d") {
		if(stat(tokd_test[2], &tc) != -1) {
			if(S_ISDIR(tc.st_mode) == true) {
				cout << "(True)\n";
				status = 0;
			}
			else {
				cout << "(False)\n";
				status = 1;
			}
		}
		else {
			perror("stat");
			status = 1;
		}
	}
	else if(flag_test != "-e" && flag_test != "-f" && flag_test != "-d") {
		if(stat(tokd_test[1], &tc) != -1) {
			cout << "(True)\n";
			status = 0;
		}
		else {
			cout << "(False)\n";
			status = 1;
		}
	}
} //
int test_cmd::the_status() {	
	return status;
}