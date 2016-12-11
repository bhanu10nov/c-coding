#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int mysystem(const char *command)
{
	pid_t childpid;
	int status;
	if (NULL == command) {
		return 0;
	}
	switch (childpid = fork()) {
	case -1:
		status = -1;
		break;
	case 0:
		fprintf(stdout,"Child Process\n");
		execl("/bin/sh", "sh", "-c", command, (char*) NULL);
		_exit(127);
	default:
		fprintf(stdout,"Parent Process, Debug 1, childpid: %d\n", childpid);
		while (waitpid(childpid, &status, 0) == -1) {
			if (errno != EINTR) {
				status = -1;
				break;
			}
		}
		fprintf(stdout,"Parent Process, Debug 2\n");
		break;
	}
	return status;
}
int main()
{
	mysystem("ps");
	return 0;
}
