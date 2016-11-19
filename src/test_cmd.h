#ifndef TEST_CMD_H
#define TEST_CMD_H

#include "exec.h"

class test_cmd : public Exec {
	private:
		int status;
		std::vector <char*> tokd_test;
	public:
		test_cmd();
		test_cmd(std::vector<char*> test_in);
		void execute();
		int the_status();
};

#endif