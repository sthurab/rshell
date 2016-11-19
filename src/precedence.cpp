class Precedence : public Exec {
	private:		
		int status;
		int l_paren_position;
		int r_paren_position;
		char* cmd;
		vector<char*> tokd_preced;
	public:
		Precedence(){};
		Precedence(char* input) {
			cmd = input;
		};
		int the_status() {
			return status;
		};

		void chk_paren() {
			string str_cmd_in = string(cmd);
			for(unsigned i = 0; i < str_cmd_in.length(); i++) {   
				if (str_cmd_in.find("(") == string::npos) {
					l_paren_position++;
					cout << l_paren_position;	
				}
				else {
					cout << " no paren ";
				}	
			}
		};

		void execute() {
			tokd_preced.clear();
			char* tok_preced = strtok(command, "()");
			while (tok_preced != 0) {
				tokd_preced.push_back(tok_preced);
				tok_preced = strtok(NULL, "()");
			}
			for(unsigned x = 0; x < tokd_preced.size(); x++) {
				cout << tokd_preced[x] << x << "\n";
			}
		}
};