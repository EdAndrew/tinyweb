#include "tinyweb.h"

int main()
{
    char *buf, *p; 
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int a = 0;
    int b = 0;
    
    //Extract two arguments
    if ((buf = getenv("QUERY_STRING")) == NULL)
    {   
        fprintf(stderr, "there is no arguments.\n");
        return -1; 
    }   
    p = strchr(buf, '&');
    *p = '\0';
    strcpy(arg1, buf);
    strcpy(arg2, p+1);
    a = atoi(arg1);
    b = atoi(arg2);
    
    sprintf(content, "Welcome to add.com\n");
    sprintf(content, "%sThe answer is: %d + %d = %d.\n", content, a, b, a+b);

    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Cotent-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);
    exit(0);
}
