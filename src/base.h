#ifndef BASE_H
#define BASE_H
// comment here
class base
{
    public:
        base(){};
        virtual void exec() = 0;
        virtual int cmd_stat() = 0;
};

#endif