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

//create the segment
if((shmid=shmget(key, SHMSIZE,0666|IPC_CREAT))<0){
	perror("shmget");
	exit(1);
}
printf("Shmid is %d\n",shmid);

//Attach the segment to our data space
if((shm=(char*)shmat(shmid,NULL,0))==(char*)-1){
	perror("shmat");
	exit(1);
}

//Put the data in Shared memory
s=shm;
for(c='a';c<='z';c++){
	*s++=c;
}
*s=0;//end with a NULL termination

//termination condition
while(*shm!='*')
	sleep(1);
	
//detach the segment
shmdt(s);
//shmctl(shmid,IPC_RMID,NULL)
exit(1);
		
}
