#ifndef OROP_H
#define OROP_H

#include "base.h"

class orOp : public base {
    private:
        base *l;
        base *r;
        int status;

    public:
        orOp();
        orOp(base *first, base *second);
        void exec();
        int cmd_stat();
};

#endif