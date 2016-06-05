#include "tinyweb.h"

int main(int argc, char **argv)
{
	int listenfd, connfd, port, clientlen;
	struct sockaddr_in clientaddr;

	/* Check command line args */
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	} 
	port = atoi(argv[1]);

	listenfd = Open_listenfd(port);
	for(;;)
	{
		clientlen = sizeof(clientaddr);
		connfd = accept(listenfd, (SA *)&clientaddr, &clientlen);
		doit(connfd);
		close(connfd);
	}
}
