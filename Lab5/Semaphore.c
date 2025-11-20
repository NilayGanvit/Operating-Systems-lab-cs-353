#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/sem.h>

int P(int semId, int semNum) {
    // Operation list of 1 operation, taking resource, no flag
    struct sembuf operationList[1];
    operationList[0].sem_num = semNum;
    operationList[0].sem_op = -1;
    operationList[0].sem_flg = 0;
    return semop(semId, operationList, 1);
}

// Release a resource
int V(int semId, int semNum) {
    // Operation list of 1 operation, releasing resource, no flag
    struct sembuf operationList[1];
    operationList[0].sem_num = semNum;
    operationList[0].sem_op = 1;
    operationList[0].sem_flg = 0;
    
    return semop(semId, operationList, 1);
}
int main()
{
int semID1, semID2;
int flag;
char* str;
int count=10;
FILE *fp;
int data=0;

semID1=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
semID2=semget(IPC_PRIVATE,1,0666|IPC_CREAT);
semctl(semID1,0,SETVAL,0);
semctl(semID2,0,SETVAL,1);
if(fork()==0)
{
while (count) {
P(semID1,0);
fp = fopen("./datafile","r");
fscanf(fp, "%d", &data);
printf("\t\t\t\t Consumer reads %d\n",data);
fclose(fp);
V(semID2,0);
count--;
}
}

else{
    while (count) {
    sleep(1);
    P(semID2,0);
    fp = fopen("./datafile","w");
    fprintf(fp, "%d\n", data);
    printf("Producer writes %d\n", data);
    data++;
    fclose(fp);
    V(semID1,0);
    count--;
    }
}

return 0;

}
