#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/wait.h>
#include <errno.h>

#include "Cmd_only.h"
#include "test_cmd.cpp"
using namespace std;

Cmd_only::Cmd_only(){}
Cmd_only::Cmd_only(char* cmd_input) {	
	cmd = cmd_input;
}
void Cmd_only::execute() {
	cmd_rip.clear();
	char* cmdToken = strtok(cmd, " ");
	while (cmdToken != 0) {
		cmd_rip.push_back(cmdToken);
		cmdToken = strtok(NULL, " ");
	}
	char *cmd_ar[30];
	for (unsigned j = 0; j < cmd_rip.size(); j++) {
		cmd_ar[j] = cmd_rip[j];
	}
	char* cmd_run = cmd_rip[0];
	cmd_ar[cmd_rip.size()] = NULL;
	if (string(cmd_run) == "test" || string(cmd_run) == "[" ) {
		test_cmd* test_cmd1 = new test_cmd(cmd_rip);
		test_cmd1->execute();
		status = test_cmd1->the_status();
		return;
	}
	int pipe_stat[2];
	status = 0;
	pipe(pipe_stat);
	int pid = fork();
	if(pid == -1) {
		perror("fork");
		exit(1);
	}
	else if(pid == 0) {
		close(pipe_stat[0]);
		if(execvp(cmd_run, cmd_ar) < 0) {
			status = 1;
			write(pipe_stat[1], &status, sizeof(status));
			close(pipe_stat[1]);
			exit(1);
		}     
	}
	else{
		wait(0);
		close(pipe_stat[1]);
		read(pipe_stat[0], &status, sizeof(status));
		close(pipe_stat[0]);
	}
}
int Cmd_only::the_status() {
	return status;
}