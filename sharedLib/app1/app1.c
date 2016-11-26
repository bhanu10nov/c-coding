#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "foo.h"
int main()
{
	int i = 0;
	fprintf(stdout,"This is app1\n");
	registerClient("app1");
	foo();
	foo();
        while (i < 10) {
		foo();
		sleep(1);
		i++;
	}
	return 0;
}
