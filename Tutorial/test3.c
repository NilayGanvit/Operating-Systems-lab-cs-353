#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
int ret;
printf("exec1 has PID=%d\n",getpid());
//char *args[]={"/usr/bin/ls",NULL};
char *args[]={"/opt/brave.com/brave/brave-browser",NULL};
ret = execv(args[0],args);
if(ret<0){
printf("ERROR, terminating\n");
}
return 0;
}
