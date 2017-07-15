#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <arpa/inet.h>

int dnsLookUp(const char *host, const char *serv, const int afam, char **ipaddr)
{
	struct addrinfo *result = NULL;
	struct in_addr dns_server;
	struct sockaddr_in dns_sock;

	int ret = 0;

	if (NULL == host || NULL == serv) {
		fprintf(stdout, "Host Name or DNS Server is NULL");
	}
	if (inet_pton(AF_INET, serv, &dns_server) == 0) {
		return -2;
	}

//	*ipaddr = NULL;

	dns_sock.sin_family = AF_INET;
	dns_sock.sin_port = htons(53);
	dns_sock.sin_addr = dns_server;
	res_init();
	_res.nscount = 1;
	_res.nsaddr_list[0] = dns_sock;

	ret = getaddrinfo(host, NULL, NULL, &result);

	if (ret == 0) {
		struct addrinfo *host = NULL;
		for (host = result; host != NULL; host = host->ai_next) {
			if ((afam == AF_INET) && (host->ai_family == AF_INET)) {
				*ipaddr = malloc(INET_ADDRSTRLEN);
				if (NULL == *ipaddr) {
					break;
				}
				struct sockaddr_in *sock = (struct sockaddr_in *)host->ai_addr;
				inet_ntop(AF_INET, &(sock->sin_addr), *ipaddr, INET_ADDRSTRLEN);
				break;
			} else if ((afam == AF_INET6) && (host->ai_family == AF_INET6)) {
				*ipaddr = malloc(INET6_ADDRSTRLEN);
				if (NULL == *ipaddr) {
					break;
				}
				struct sockaddr_in6 *sock = (struct sockaddr_in6 *)host->ai_addr;
				inet_ntop(AF_INET6, &(sock->sin6_addr), *ipaddr, INET6_ADDRSTRLEN);
				break;
			}
		}
		freeaddrinfo(result);
	} else {
		fprintf(stderr, "%s\n", gai_strerror(ret));
	}
	if (NULL == *ipaddr) {
		ret = -1;
	}
	return ret;
}
int main()
{
	char *ipaddr;
	int ret = 0;
	//ret = dnsLookUp("www.google.com", "192.168.0.1", AF_INET, &ipaddr);
	ret = dnsLookUp("www.google.com", "10.141.36.252", AF_INET, &ipaddr);
	fprintf(stdout, "ret = %d, ipaddr = %s\n", ret, ipaddr);
	return 0;
}
