#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h> 

void isort(int arr[], int n){
    
    int i,k,j;
    for(i=1;i<n;i++){
        
	    k=arr[i];
	    j=i-1;
	    while(j>=0&&arr[j]>k){
	        
		    arr[j+1]=arr[j];
		    j=j-1;
		    
	    }
	    arr[j+1] = k;
    }
}

void merge(int arr[], int lowa, int higha, int highb){
    
	int cnt=highb-lowa+1;
	int res[cnt];
	int i=lowa,k=higha+1,m=0;
	
	while(i<=higha&&k<=highb){
	    
		if (arr[i]<arr[k]){
			res[m++]=arr[i++];
		}else if(arr[k]<arr[i]){
			res[m++]=arr[k++];
		}else if(arr[i]==arr[k]){
		    
			res[m++]=arr[i++];
			res[m++]=arr[k++];
			
		}
	}

	while (i<=higha){
		res[m++]=arr[i++];
	}

	while (k<=highb){
		res[m++]=arr[k++];
	}

	int arr_cnt=lowa;
	for(i=0;i<cnt;i++,lowa++){
		arr[lowa]=res[i];
	}
}

void solve(int arr[], int low, int high){
    
	int i,len=(high-low+1);

	if (len<=5){
		isort(arr+low, len);
		return;
	}

	pid_t lpid,rpid;
	lpid = fork();
    if (lpid==0){
        
		solve(arr,low,low+len/2-1);
		_exit(0);
		
	}else{
	    
		rpid=fork();
		if(rpid==0){
		    
			solve(arr,low+len/2,high);
			_exit(0);
		}
	}

	int status;

	waitpid(lpid, &status, 0);
	waitpid(rpid, &status, 0);

	merge(arr, low, low+len/2-1, high);
}

void usr_inpt(int arr[], int len){
    
	int i;
	for(i=0;i<len;i++){
		int a;
		scanf("%d",&a);
		arr[i] = a;
	}
	
	return;
	
}

int main(){
    
	int shmid;
	key_t k=IPC_PRIVATE;
	int *shared_arr;

	int length=10;

	size_t SHM_SIZE=sizeof(int)*length;

	if((shmid=shmget(k,SHM_SIZE,IPC_CREAT|0666))<0){
	    
		perror("shmget");
		_exit(1);
		
	}

	if((shared_arr=shmat(shmid,NULL,0))==(int*)-1){
	    
		perror("shmat");
		_exit(1);
		
	}

	srand(time(NULL));
	usr_inpt(shared_arr, length);
	
	printf("unsorted array %d %d %d %d %d %d %d %d %d %d", shared_arr[0], shared_arr[1], shared_arr[2], shared_arr[3],shared_arr[4], shared_arr[5], shared_arr[6], shared_arr[7],shared_arr[8], shared_arr[9]);

	solve(shared_arr, 0, length-1);
	
	printf("\nsorted array %d %d %d %d %d %d %d %d %d %d", shared_arr[0], shared_arr[1], shared_arr[2], shared_arr[3],shared_arr[4], shared_arr[5], shared_arr[6], shared_arr[7],shared_arr[8], shared_arr[9]);

	if (shmdt(shared_arr) == -1)
	{
		perror("shmdt");
		_exit(1);
	}

	if (shmctl(shmid, IPC_RMID, NULL) == -1)
	{
		perror("shmctl");
		_exit(1);
	}

	return 0;
}
