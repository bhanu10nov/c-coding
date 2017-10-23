#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <net/if.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netlink/netlink.h>
#include <netlink/addr.h>
#include <netlink/cache.h>
#include <netlink/route/link.h>
#include <netlink/route/addr.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <ifaddrs.h>

#ifndef IFF_DORMANT
#define IFF_DORMANT	0x20000
#endif


int main()
{
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	char *addr;

	getifaddrs (&ifap);

	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family==AF_INET) {
			sa = (struct sockaddr_in *) ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			printf("Interface: %s\tIpAddress: %s\n", ifa->ifa_name, addr);
			sa = (struct sockaddr_in *) ifa->ifa_netmask;
			addr = inet_ntoa(sa->sin_addr);
			printf("Interface: %s\tMaskAddress: %s\n", ifa->ifa_name, addr);

			if (ifa->ifa_flags & IFF_UP) {
				printf("IFF_UP\n");
			}

			if (ifa->ifa_flags & IFF_BROADCAST) {
				printf("IFF_BROADCAST\n");
			}

			if (ifa->ifa_flags & IFF_DEBUG) {
				printf("IFF_DEBUG\n");
			}

			if (ifa->ifa_flags & IFF_LOOPBACK) {
				printf("IFF_LOOPBACK\n");
			}

			if (ifa->ifa_flags & IFF_POINTOPOINT) {
				printf("IFF_POINTOPOINT\n");
			}

			printf("Network Flags : %d\n\n\n", ifa->ifa_flags);
		}
	}

	freeifaddrs(ifap);
	return 0;
}
