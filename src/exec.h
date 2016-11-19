#ifndef EXEC_H
#define EXEC_H

class Exec
{
	public:
		Exec(){};
		virtual void execute() = 0;
		virtual int the_status() = 0;
};

#endif