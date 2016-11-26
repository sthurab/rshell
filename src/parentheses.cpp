// paren class

class parentheses : public base {

private:

int status;
int l_parens;
int r_parens;
char* cmd;
// check connector
bool tf_connectA;
bool tf_connectB;
bool tf_connectC;
bool tf_connectD;
vector<char*> cmd_vect;
vector<string> connector_vect;
vector<int> stat_vect;
vector<base*> exec_vect; 

	public:

    parentheses(){};

	parentheses(char* input) {
        cmd = input;
    };

    void paren_chk() {   
        int l_parens = 0;  
        int r_parens = 0;  
        size_t starting_paren = 0;
        size_t ending_paren = 0;
        string has_str = string(cmd);
        for(unsigned i=0; i <= has_str.length(); i++) {
			// no parens
            if(l_parens == 0 && r_parens == 0) {
				// doing the andOp operator
                if (cmd[i] == '&' && cmd[i+1] == '&') {
                    connector_vect.push_back("&&");
                    if (cmd_vect.empty()) {
                        string y = has_str.substr(0, i-0);
                        char* tok_other = new char[y.length()];
                        strcpy(tok_other, y.c_str());
                        cmd_vect.push_back(tok_other);
                    }
                }
				// doing the orOp operator
                else if (cmd[i] == '|' && cmd [i+1] == '|') {
                    connector_vect.push_back("||");
                    if (cmd_vect.empty()) {
                        string y = has_str.substr(0, i-0);
                        char* tok_other = new char[y.length()];
                        strcpy(tok_other, y.c_str());
                        cmd_vect.push_back(tok_other);
                    }
                }
            }
			// is the left paren
            if(cmd[i] == '(') {
                l_parens++;
                if (l_parens == 1) {
                    starting_paren = i++;   
                }
            }
			// is the right paren
            else if (cmd[i] == ')') {
                r_parens++;
                if (l_parens == r_parens) {
                    ending_paren = i;
					// append for paren
                    string x = has_str.substr(starting_paren+1,(ending_paren-starting_paren)-1); 
                    int last = x.length();
                    if (x[0] == '(' && x[last] != ')') {
                        x.append(")");
                    }
                    // tokenize paren
                    char* tok_par = new char[x.length()];
                    strcpy(tok_par, x.c_str());
                    if (x.find("(") != string::npos) {
                        cmd = tok_par;
                        paren_chk();
                    }
					// push back
                    cmd_vect.push_back(tok_par);
                    l_parens = 0;
                    r_parens = 0;
                }
            }
        }
        exec();
    };

    void exec() {
        if(connector_vect.empty()) {
            for(unsigned vec=0; vec < cmd_vect.size(); vec++) {
                for(unsigned iter=0; iter < string(cmd_vect[vec]).length(); iter++) {
                    if (cmd_vect[vec][iter] == '&' || cmd_vect[vec][iter] == '|') {
                        tf_connectA = true;
                    }
                }
                if (!tf_connectA) {
                    executor* from_left = new executor(cmd_vect[vec]);
                    from_left->exec();
                    stat_vect.push_back(from_left->cmd_stat());
                    status = from_left->cmd_stat();
                }
                else if (tf_connectA) {
                    connector* from_left = new connector(cmd_vect[vec]);
                    from_left->exec();
                    stat_vect.push_back(from_left->cmd_stat());
                    status = from_left->cmd_stat();
                }
            }
        }
        for(unsigned it=0; it < connector_vect.size(); it++) {
            exec_vect.clear();
            if (it == 0) {
                for(unsigned iter=0; iter < string(cmd_vect[it]).length(); iter++) {
                    if (cmd_vect[it][iter] == '&' || cmd_vect[it][iter] == '|') {
                        tf_connectB = true;
                    }
                }
                for(unsigned iter=0; iter < string(cmd_vect[it+1]).length(); iter++) {
                    if (cmd_vect[it+1][iter] == '&' || cmd_vect[it+1][iter] == '|') {
                        tf_connectC = true;
                    }
                }
                if (connector_vect[it] == "&&") {
                    if (tf_connectB) {
                        connector* from_left = new connector(cmd_vect[it]);
                        exec_vect.push_back(from_left);
                    }
                    else {
                        executor* from_left = new executor(cmd_vect[it]);
                        exec_vect.push_back(from_left);
                    }
                    if (tf_connectC) {
                        connector* from_right = new connector(cmd_vect[it+1]);
                        exec_vect.push_back(from_right);
                    }
                    else {
                        executor* from_right = new executor(cmd_vect[it+1]);
                        exec_vect.push_back(from_right);
                    }
                    andOp* and_oper = new andOp(exec_vect[0], exec_vect[1]);
                    and_oper->exec();
                    stat_vect.push_back(and_oper->cmd_stat());
                    status = and_oper->cmd_stat();
                }
                else if (connector_vect[it] == "||") {
                    if (tf_connectB) {
                        connector* from_left = new connector(cmd_vect[it]);
                        exec_vect.push_back(from_left);
                    }
                    else {
                        executor* from_left = new executor(cmd_vect[it]);
                        exec_vect.push_back(from_left);
                    }
                    if (tf_connectC) {
                        connector* from_right = new connector(cmd_vect[it+1]);
                        exec_vect.push_back(from_right);
                    }
                    else {
                        executor* from_right = new executor(cmd_vect[it+1]);
                        exec_vect.push_back(from_right);
                    }
					// make instance of orOp operator
                    orOp* or_oper = new orOp(exec_vect[0], exec_vect[1]);
                    or_oper->exec();
                    stat_vect.push_back(or_oper->cmd_stat());
                    status = or_oper->cmd_stat();
                }
            }
            else {
                for(unsigned iter=0; iter < string(cmd_vect[it+1]).length(); iter++) {
                    if (cmd_vect[it+1][iter] == '&' || cmd_vect[it+1][iter] == '|') {
                        tf_connectD = true;
                    }
                }
                if (connector_vect[it] == "&&") {
                    if (stat_vect[it-1] == 0) {
                        if (tf_connectD) {
                            connector* nxt_cmd = new connector(cmd_vect[it+1]);
                            nxt_cmd->exec();
                            stat_vect.push_back(nxt_cmd->cmd_stat());
                            status = nxt_cmd->cmd_stat();
                        }
                        else {
                            executor* nxt_cmd = new executor(cmd_vect[it+1]);
                            nxt_cmd->exec();
                            stat_vect.push_back(nxt_cmd->cmd_stat());
                            status = nxt_cmd->cmd_stat();
                        }
                    }
                }
                else if (connector_vect[it] == "||") {
                    if (stat_vect[it-1] == 1) {
                        if (tf_connectD) {
                            connector* nxt_cmd = new connector(cmd_vect[it+1]);
                            nxt_cmd->exec();
                            stat_vect.push_back(nxt_cmd->cmd_stat());
                            status = nxt_cmd->cmd_stat();
                        }
                        else {
                            executor* nxt_cmd = new executor(cmd_vect[it+1]);
                            nxt_cmd->exec();
                            stat_vect.push_back(nxt_cmd->cmd_stat());
                            status = nxt_cmd->cmd_stat();
                        }
                    }
                }
            }
            tf_connectB = false;
            tf_connectC = false;
            tf_connectD = false;
        }
    }
    
	int cmd_stat() {
        return status;
    };
};
