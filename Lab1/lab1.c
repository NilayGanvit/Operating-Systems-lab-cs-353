#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char *apps[] = {"/usr/bin/gnome-calculator","/usr/bin/gedit"};
    	int option;
    	while(1){
        	printf("1.Calc\n2.gedit\nand any other to exit\nEnter your choice :");
        	scanf("%d", &option);
        	if(option>2){ 
        		break;
        	}
        	if(fork() == 0){
            		char *args[] = {apps[option-1], NULL};
            		execvp(args[0], args);
            		break;
        	}
    	}
    	return 0;
}
