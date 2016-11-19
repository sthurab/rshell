#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <errno.h>
#include "and.h"
using namespace std;

And::And(){}
And::And(Exec *first, Exec *second)
{
	l= first;
	r = second;
}
void And::execute()
{
	l->execute();
	if (l->the_status() == 0)
	{
		r->execute();
		if (r->the_status() == 0)
		{
			status = 0;
		}
		else
		{
			status = 1;
		}
	}
	else 
	{ 
		status = 1; 
	}
}
int And::the_status()
{
	return status;
}