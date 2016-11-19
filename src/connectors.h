#ifndef CONNECTORS_H
#define CONNECTORS_H

#include "exec.h"

class Connectors : public Exec
{
	private:
		char* cmd;
		vector<char *> cmd_vect;
		vector<string> connector_vect;
		vector<int> status_vect;
	public:
		Connectors();
		Connectors(char* cmd_connect);
		void execute();
		int the_status();
};

#endif