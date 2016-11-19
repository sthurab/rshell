#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h> 

#include "or.h"
using namespace std;

Or::Or(){}
Or::Or(Exec *first, Exec *second) {	
	l= first;
	r = second;
}
void Or::execute() {
	l->execute();
	if (l->the_status() == 1) {
		r->execute();
		if (r->the_status() == 0) {
			status = 0;
		}
		else {	
			status = 1;
		}
	}
	else {	
		status = 0;
	}
}
int Or::the_status() {
	return status;
}