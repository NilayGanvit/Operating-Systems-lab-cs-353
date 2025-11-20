
#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
int main(){
	int x=5;
	printf("%d",++x);
	fork();
	printf("hello\n");
}
