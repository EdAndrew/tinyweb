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
	threadpool thpool = thpool_init(NTHREADS);
	listenfd = Open_listenfd(port);

	for(;;)
	{
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		thpool_add_work(thpool, thread, (void *)&connfd);
	}
}

void * thread(void *vargp)
{
	int connfd;
	connfd = *((int *)vargp);
	doit(connfd);
	Close(connfd);
}
