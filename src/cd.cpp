#include <sys/types.h>
#include <sys/stat.h>

#include "base.h"
using namespace std;

class cd : public base {

private:
		std::vector<char*> cd_vect;
		int status;

public:
		cd(){};

		cd(std::vector<char*> test_in) {
			cd_vect = test_in; 
		};

		void exec() {
			if(cd_vect.size() == 1) {
				setenv("OLDPWD", getenv("PWD"), 1);	
				setenv("PWD", getenv("HOME"), 1);
				chdir(getenv("HOME"));
			}
			else if(std::string(cd_vect[1]) == "-") {
				char* hold = getenv("PWD");
				setenv("PWD", getenv("OLDPWD"), 1);
				chdir(getenv("OLDPWD"));
				setenv("OLDPWD", hold, 1);
			}
			else if(cd_vect.size() > 1) {
				struct stat chk;
				if(stat(cd_vect[1], &chk) != -1) {
					if(S_ISDIR(chk.st_mode) == true) {
						setenv("OLDPWD", getenv("PWD"), 1);
						string nxt_dir;
						string str1;
						string str2;
						stringstream ss1;
						stringstream ss2;
						char* curr_dir = get_current_dir_name();
						ss1 << curr_dir;
						ss1 >> str1;
						char* get_dir = cd_vect[1];
						ss2 << get_dir;
						ss2 >> str2;
						nxt_dir = str1 + "/" + str2;
						setenv("PWD", nxt_dir.c_str(), 1);
						chdir(nxt_dir.c_str());
						status = 0;
					}
					else {
						status = 1;
					}
				}	
				else {
					status = 1;
				}
			}
			//
			if(errno != 0) {
				status = 1; 
				errno = 0;
			}
		};

	int cmd_stat() {
		return status;
	};
};
