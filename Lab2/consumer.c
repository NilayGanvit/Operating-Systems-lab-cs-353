#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#define SHMSIZE 30

int main(){
char c;
char *s,*shm;
int shmid;
key_t key=5690;

//Locate the segment
if((shmid=shmget(key, SHMSIZE,0666))<0){
	perror("shmget");
	exit(1);
}
printf("Shmid is %d\n",shmid);

//Attach the segment to our data space
if((shm=(char*)shmat(shmid,NULL,0))==(char*)-1){
	perror("shmat");
	exit(1);
}

//Read the data from Shared memory
for(s=shm;*s!=0;s++)
	putchar(*s);
putchar('\n');

//cahnge the first character of the segment to '*', indicating we have read the segment.
*shm='*';
	
//detach the segment
shmdt(s);
shmctl(shmid,IPC_RMID,NULL);
exit(1);
		
}
