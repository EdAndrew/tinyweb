#include "tinyweb.h"
#define SBUFSIZE 16
#define NTHREADS 4

void * thread(void *vargp);

sbuf_t sbuf;

int main(int argc, char **argv)
{
	int i, listenfd, port, connfd;
	socklen_t clientlen = sizeof(struct sockaddr_in);
	struct sockaddr_in clientaddr;
	pthread_t tid;

	/* Check command line args */
	if (argc != 2)
	{
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(1);
	}
	port = atoi(argv[1]);
	sbuf_init(&sbuf, SBUFSIZE);
	listenfd = Open_listenfd(port);
	for (i = 0; i < NTHREADS; ++i)
		Pthread_create(&tid, NULL, thread, NULL);

	for(;;)
	{
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		sbuf_insert(&sbuf, connfd);
	}
}

void * thread(void *vargp)
{
	int connfd;
	Pthread_detach(pthread_self());
	for(;;)
	{
		connfd = sbuf_remove(&sbuf);
		doit(connfd);
		Close(connfd);
	}
}
