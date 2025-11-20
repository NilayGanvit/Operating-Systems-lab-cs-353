#include<stdlib.h>  
 #include<stdio.h>  
 #include<string.h>  
 #include<unistd.h>  
 #include<sys/types.h>  
 #include<sys/ipc.h>  
 #include<sys/msg.h>  
 struct my_msg{  
         long int msg_type;  
         char some_text[BUFSIZ];  
 };  
 int main()  
 {   
         int msgid;  
         struct my_msg some_data;  
         long int msg_to_rec=0;  
         key_t key = 8880;
         msgid=msgget(key,0666|IPC_CREAT);  
         
         while(1)  
         {  
                 msgrcv(msgid,(void *)&some_data,sizeof(some_data),msg_to_rec,0);
                 printf("Data received: %s\n",some_data.some_text);  
                 if(strncmp(some_data.some_text,"end",3)==0)  
                 {  
                         break;  
                 }  
         }  
         printf("out of while loop\n");
         msgctl(msgid,IPC_RMID,0);  
 }  
