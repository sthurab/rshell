#ifndef TESTOR_H
#define TESTOR_H

#include "base.h"

class test_cmd : public base {
    private:
        int status;
        std::vector <char*> test_tokd;
    public:
        test_cmd();
        test_cmd(std::vector<char*> test_in);
        void exec();
        int cmd_stat();
};

#endif