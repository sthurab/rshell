#ifndef AND_H
#define AND_H

#include "exec.h"

class And : public Exec
{
	private:
		Exec *l;
		Exec *r;
		int status;
	public:
		And();
		And(Exec *first, Exec *second);
		void execute();
	int the_status();
};

#endif