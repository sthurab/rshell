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

#include "executor.h"
#include "testor.cpp" //
using namespace std;

executor::executor(){}

executor::executor(char* input_cmd) {
    cmd = input_cmd;
}

void executor::exec() {
    cmd_rip.clear();
    char* tok_cmd = strtok(cmd, " ");
    while(tok_cmd != 0) {
        cmd_rip.push_back(tok_cmd);
        tok_cmd = strtok(NULL, " ");
    }
	// for 50 character arrray
    char *cmd_ar[50];
    for (unsigned itr=0; itr < cmd_rip.size(); itr++) {
        cmd_ar[itr] = cmd_rip[itr];
    }
    char* run_cmd = cmd_rip[0];
    cmd_ar[cmd_rip.size()] = NULL;
	// left bracket
    if (string(run_cmd) == "main" || string(run_cmd) == "[" ) {
        test_cmd* cmd1_test = new test_cmd(cmd_rip);
        cmd1_test->exec();
        status = cmd1_test->cmd_stat();
        return;
    }
    int pipe_stat[2];
    status = 0;
    pipe(pipe_stat);

    int pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    else if (pid == 0) {
        close(pipe_stat[0]);
        if (execvp(run_cmd, cmd_ar) < 0) {
            status = 1;
            write(pipe_stat[1], &status, sizeof(status));
            close(pipe_stat[1]);
            exit(1);
        }     
    }
    else {
        wait(0);
        close(pipe_stat[1]);
        read(pipe_stat[0], &status, sizeof(status));
        close(pipe_stat[0]);
    }
}

int executor::cmd_stat() {
    return status;
}
