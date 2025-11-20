#include<stdio.h>
#include<unistd.h>
int main(){
int pid=fork();
if(pid==0){
printf("-----child process----\n");
printf("PID= %d PPID %d\n",getpid(),getppid());
}else{
printf("-----parent process---\n");
printf("PPID= %d\n",getppid());
}
}
