#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "base.h"

class executor : public base {

private:
        char* cmd;
        int status;
        std::vector <char*> cmd_rip;

public:
        executor();
        executor(char* input_cmd);
        void exec();
        int cmd_stat();
};

#endif