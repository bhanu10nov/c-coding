#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "foo.h"
int main()
{
	int i = 0;
	fprintf(stdout,"This is app2\n");
	registerClient("app2");
	foo();
	while (i < 10) {
		foo();
		sleep(1);
		i++;
	}
	return 0;
}
