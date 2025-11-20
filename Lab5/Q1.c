#include<sys/ipc.h> //Including required libraries
#include<sys/shm.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>
#include<sys/wait.h>
#define SHMSIZE 30
//Driver Code
int main(){
//Initialising Variables
int X=0;
int *s,*shm;
int shmid;
key_t key=5690;

//create the segment
if((shmid=shmget(key, SHMSIZE,0666|IPC_CREAT))<0){
	perror("shmget");
	exit(1);
}
printf("Shmid is %d\n",shmid);

//Attach the segment to our data space
if((shm=(int*)shmat(shmid,NULL,0))==(int*)-1){
	perror("shmat");
	exit(1);
}

//Put the data in Shared memory
*shm=X;
//Initializing PIDs and forking child1
pid_t pid1,pid2;
pid1=fork();

if(pid1==0){
	X=*shm;
	for(int i=0;i<100000;i++){
		X++;
		*shm=X;
	}
}else if(pid1>0){ 
	sleep(1); //solving the race condition by suspending for a sec.
	pid2=fork(); //forking child 2
	if(pid2==0){
		X=*shm;
		for(int i=0;i<100000;i++){
		X--;
		*shm=X;}
	}
	_exit(0);
}
//waiting for child processes to end
int status;
waitpid(pid1,&status,0);
waitpid(pid2,&status,0);
// wait(NULL);
X=*shm;
printf("Value at termination %d \n",X);
//detaching the shared memory
shmdt(s);
shmctl(shmid,IPC_RMID,NULL);
exit(1);
		
}
