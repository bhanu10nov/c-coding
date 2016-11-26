#include <stdio.h>
#include <string.h>
#include "foo.h"
int gVariable=0;
char clientName[100] ={0};
void foo(void)
{
	fprintf(stdout,"I am shared Lib, var = %d, clientName = %s\n",
		gVariable,clientName);
	gVariable++;
	if (gVariable > 2) {
		fprintf(stdout,"gVariable > 2\n");
	}
}
void registerClient(const char *pName)
{
	strncpy(clientName,pName,100);
}
