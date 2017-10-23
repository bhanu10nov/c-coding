/***
 @file   : my_nl_monitor.c
 @brief  : c program to monitor the network interface
 @author : bhanujha@gmail.com
 **/

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

#define ETHERNET_DEVICE_NAME "enp1s0"
static struct nl_cache *link_cache, *addr_cache;;
static struct rtnl_addr *addr;
static int eth_thread_alive = 1;


int printIpAddress()
{
	struct ifaddrs *ifap, *ifa;
	struct sockaddr_in *sa;
	char *addr;
	//int iface_found = 0;

	//printf("printIpAddress()+\n");

	getifaddrs (&ifap);

	for (ifa = ifap; ifa; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr->sa_family==AF_INET) {

			//printf("Interface: %s\n", ifa->ifa_name);
			if (0 != strncmp(ifa->ifa_name, ETHERNET_DEVICE_NAME,
				sizeof(ETHERNET_DEVICE_NAME))) {
				continue;
			}
			//iface_found = 1;

			sa = (struct sockaddr_in *) ifa->ifa_addr;
			addr = inet_ntoa(sa->sin_addr);
			printf("Interface: %s\tIPAddress: %s\n", ifa->ifa_name, addr);
			sa = (struct sockaddr_in *) ifa->ifa_netmask;
			addr = inet_ntoa(sa->sin_addr);
			printf("Interface: %s\tMaskAddress: %s\n", ifa->ifa_name, addr);

			printf("Network Flags : %d\n\n\n", ifa->ifa_flags);

		}
	}

	/*if (1 == iface_found) {
		printf("IFF_CONNECTED\n");
	} else {
		printf("IFF_DISCONNECTED\n");
	}*/

	freeifaddrs(ifap);
	return 0;
}

int read_event(int sockint)
{
	int status;
	int ret = 0;
	char buf[4096];
	struct iovec iov = { buf, sizeof buf };
	struct sockaddr_nl snl;
	struct msghdr msg = { (void *) &snl, sizeof(snl), &iov, 1, NULL, 0, 0 };
	struct nlmsghdr *h;
	struct ifinfomsg *ifi;
	char iface_name[512];

	status = recvmsg (sockint, &msg, 0);

	if (status < 0) {
		/* Socket non-blocking so bail out once we have read everything */
		if (errno == EWOULDBLOCK || errno == EAGAIN) {
			return ret;
		}

		/* Anything else is an error */
		printf ("read_netlink: Error recvmsg: %d\n", status);
		perror ("read_netlink: Error: ");
		return status;
	}

	if (status == 0) {
		printf ("read_netlink: EOF\n");
	}

	// We need to handle more than one message per 'recvmsg'
	for (h = (struct nlmsghdr *) buf; NLMSG_OK (h, (unsigned int) status);
			h = NLMSG_NEXT (h, status)) {
		//Finish reading
		if (h->nlmsg_type == NLMSG_DONE)
			return ret;

		// Message is some kind of error
		if (h->nlmsg_type == NLMSG_ERROR) {
			printf ("read_netlink: Message is an error - decode TBD\n");
			return -1;        // Error
		}
		if (h->nlmsg_type == RTM_NEWLINK) {
			ifi = NLMSG_DATA(h);
			//printf("NETLINK::%s\n", (ifi->ifi_flags & IFF_RUNNING) ? "Up" : "Down");
			//printf("LINK Index : %d\n", ifi->ifi_index);
			if (NULL != rtnl_link_i2name(link_cache, ifi->ifi_index, iface_name, sizeof(iface_name))) {
				//printf("Link Dev Name : %s\n", iface_name);
				if (0 != strncmp(iface_name, ETHERNET_DEVICE_NAME, sizeof(ETHERNET_DEVICE_NAME))) {
					continue;
				}
				if (ifi->ifi_flags & IFF_RUNNING) {
					printf("IFF_UP\n");
				} else {
					printf("IFF_DOWN\n");
				}

				printIpAddress();
			}

		}
	}
	return ret;
}

int main()
{
	int err = 0;
	struct nl_sock *sock = NULL;
	struct timeval timeout;

	printf("Hello\n");

	sock = nl_socket_alloc();
	if (NULL == sock) {
		printf("Couldn't allocate socket\n");
		return -1;
	}
	nl_socket_disable_seq_check(sock);

	err = nl_connect(sock, NETLINK_ROUTE);
	if (0 != err) {
		printf("Error during nl connect\n");
	}

	err = nl_socket_add_membership(sock, RTNLGRP_LINK);
	if (0 != err) {
		printf("Error during nl connect\n");
	}

	err = rtnl_link_alloc_cache(sock, AF_UNSPEC, &link_cache);
	if (0 != err) {
		printf("Error during nl connect\n");
	}

	err = rtnl_addr_alloc_cache(sock, &addr_cache);
	if (0 != err) {
		printf("Error during nl connect\n");
	}

	addr = rtnl_addr_alloc();
	if (NULL == addr) {
		printf("Couldn't allocate addr\n");
		return -1;
	}

	rtnl_addr_set_ifindex(addr, rtnl_link_name2i(link_cache, "enp1s0"));

	while (eth_thread_alive) {
		fd_set rfds;
		int fd, retval;

		/* 10 seconds of timeout */
		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		//printf("Bhanu : %s : %d\n", __FUNCTION__, __LINE__);
		fd = nl_socket_get_fd(sock);

		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);

		//printf("Bhanu : %s : %d\n", __FUNCTION__, __LINE__);

		/* wait for an incoming message on the netlink socket */
		retval = select(fd+1, &rfds, NULL, NULL, &timeout);

		//printf("Bhanu : %s : %d, ret : %d\n", __FUNCTION__, __LINE__, retval);
		if (retval) {
			/* FD_ISSET(fd, &rfds) will be true */
			//nl_recvmsgs_default(sock);
			read_event(fd);
		}
	}

	return 0;
}
