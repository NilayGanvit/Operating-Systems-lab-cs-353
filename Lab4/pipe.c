#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

int main()
{
int pipefd[2];
int pid;
char* send="Hello world!";
char recieve[strlen(send)+1];
printf("%ld\n",strlen(send));
pipe(pipefd);

if(pid=fork())
{
    printf("Writing.....\n");
    write(pipefd[1], send, strlen(send)+1 );
}
else
{
    printf("Reading.....\n");
    read(pipefd[0], recieve, strlen(send)+1 );
    printf("%s\n",recieve);
}
return 0;    
}
