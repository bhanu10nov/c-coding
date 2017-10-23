#include <stdlib.h>
#include <stdio.h>
#include <string.h>     
#include <sys/ioctl.h>  /* ioctl()  */
#include <sys/socket.h> /* socket() */
#include <arpa/inet.h>  
#include <unistd.h>     /* close()  */
#include <linux/if.h>   /* struct ifreq */
#include <errno.h>

int main(int argc, char* argv[])
{
	/* this socket doesn't really matter, we just need a descriptor 
	* to perform the ioctl on */
	int fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct ifreq ethreq;

	memset(&ethreq, 0, sizeof(ethreq));

	/* set the name of the interface we wish to check */
	strncpy(ethreq.ifr_name, argv[1], IFNAMSIZ);
	/* grab flags associated with this interface */
	if (ioctl(fd, SIOCGIFFLAGS, &ethreq) == -1) {
		printf("ioctl failed , errno : %d\n",errno);
	}
	if (ethreq.ifr_flags & IFF_UP) {
		printf("%s is in up mode\n",
			ethreq.ifr_name);
	} else {
		printf("%s is NOT in up mode\n",
			ethreq.ifr_name);
	}

	close(fd);
	return 0;
}
