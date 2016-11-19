#ifndef CMD_ONLY_H
#define CMD_ONLY_H

#include "exec.h"

class Cmd_only : public Exec {
	private:
		char* cmd;
		int status;
		std::vector <char*> cmd_rip;
	public:
		Cmd_only();
		Cmd_only(char* cmd_input);
		void execute();
		int the_status();
};

#endif