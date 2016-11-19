#ifndef OR_H
#define OR_H

#include "exec.h"

class Or : public Exec
{
	private:
		Exec *l;
		Exec *r;
		int status;
	public:
		Or();
		Or(Exec *first, Exec *second);
		void execute();
		int the_status();
};

#endif