#ifndef ANDOP_H
#define ANDOP_H

#include "base.h"

class andOp : public base {
    private:
        base *l;
        base *r;
        int status;
    public:
        andOp();
        andOp(base *first, base *second);
        void exec();
        int cmd_stat();
};

#endif