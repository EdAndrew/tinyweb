#include "tinyweb.h"

void * thread(void *vargp);

int main(int argc, char **argv)
{
	int listenfd, port, clientlen, *connfdp;
	struct sockaddr_in clientaddr;
	pthread_t tid;

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
		connfdp = Malloc(sizeof(int));
		*connfdp = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Pthread_create(&tid, NULL, thread, connfdp);
	}
}

void * thread(void *vargp)
{
	int connfd = *((int *)vargp);
	Pthread_detach(pthread_self());
	Free(vargp);
	doit(connfd);
	Close(connfd);
	return NULL;
}
