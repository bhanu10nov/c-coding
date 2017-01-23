/**
 * @file    server.c
 * @author  Bhanu Jha(bhanujha@gmail.com)
 * @brief   server code depicting usage of socket
 */

#include <stdio.h>
#include <string.h>
#include <glib.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

#define size 1024
void helper()
{
	fprintf(stdout, "client [ui]\n");
	fprintf(stdout, "u for unix socket\n");
	fprintf(stdout, "i for internet socket\n");
}
void unixsocket()
{
	fprintf(stdout, "unix socket Example\n");
}
void internetsocket()
{
	gint socketfd, newsocketfd;
	gint accept_size = 0;
	gint ret = 0;
	char buffer[size] = {0};
	struct sockaddr_in server_addr;
	memset (buffer, 0, size);
	fprintf(stdout, "internet socket Example\n");
	/*int socket(int domain, int type, int protocol);*/
	socketfd = socket(PF_INET, SOCK_STREAM, 0);
	if (socketfd == -1) {
		fprintf(stdout, "socket creation error, errno: %d\n",errno);
		return;
	}
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(123);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

	/*int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);*/
	ret = bind(socketfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (ret == -1) {
		fprintf(stdout, "Bind error, errno: %d\n",errno);
		return;
	}

	/*int listen(int sockfd, int backlog)*/
	ret = listen(socketfd, 5);
	if (ret == -1) {
		fprintf(stdout, "Listen Failed, errno: %d\n", errno);
		return;
	}

	accept_size = sizeof(server_addr);
	/*int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)*/
	newsocketfd = accept(socketfd, (struct sockaddr *)&server_addr, &accept_size);
	strcpy(buffer, "Hello World");

	/*ssize_t send(int sockfd, const void *buf, size_t len, int flags)*/
	send(newsocketfd, buffer, 13, 0);
}
int main(int argc, char *argv[])
{
	gint ret = 0;
	gint option = 0;
	fprintf(stdout,"server program\n");
	if (argc < 2) {
		fprintf(stdout, "No of argument is more\n");
		helper();
		return 0;
	}
	while ((option = getopt(argc, argv, "ui")) != -1) {
		switch (option) {
		case 'u':
			fprintf(stdout, "Unix Domain Socket\n");
			break;
		case 'i':
			internetsocket();
			fprintf(stdout, "Internet Domain Socket\n");
			break;
		default:helper();
			fprintf(stdout, "Wrong Input\n");
			exit(1);
			break;

		}
	}
	return ret;
}
