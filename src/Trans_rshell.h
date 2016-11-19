#ifndef TRANS_RSHELL_H
#define TRANS_RSHELL_H

class Trans_rshell {
	private:
		string user_input;
		vector<char*> cmds;
	public:
		Trans_rshell();
		Trans_rshell(string input);
		void interpret();
};

#endif