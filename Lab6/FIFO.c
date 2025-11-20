#include<stdio.h>

int main(){

	printf("Frames=");
	int frames;
	scanf("%d",&frames);
	printf("no of pages in reference string=");
	int pages;
	scanf("%d",&pages);

    int incomingStream[pages];
	printf("Input pages...\n");
	for(int i=0;i<pages;i++){
		scanf("%d",&incomingStream[i]);
	}
    int pageFaults=0;
    int m,n,s;

    int temp[frames];
    for(m=0;m<frames;m++){

        temp[m]=-1;

    }

    for(m=0;m<pages;m++){

        s=0;

        for(n=0;n<frames;n++){

            if(incomingStream[m]==temp[n]){

                s++;
                pageFaults--;
            }
        }

        pageFaults++;
        
        if((pageFaults<=frames)&&(s==0)){

            temp[m]=incomingStream[m];

        }else if(s==0){

            temp[(pageFaults-1)%frames]=incomingStream[m];

        }      
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
