#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "base.h"

class connector : public base {
    private:
        char* cmd;
        vector<char*> cmd_vect;
        vector<string> connector_vect;
        vector<int> stat_vect;
    public:
        connector();
        connector(char* cmd_connect);
        void exec();
        int cmd_stat();
};

#endif