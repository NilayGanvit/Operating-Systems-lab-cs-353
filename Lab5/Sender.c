#include<stdlib.h>  
 #include<stdio.h>  
 #include<string.h>  
 #include<unistd.h>  
 #include<sys/types.h>  
 #include<sys/ipc.h>  
 #include<sys/msg.h>  
 #define MAX_TEXT 512   //maximum length of the message that can be sent allowed  
 struct my_msg{  
         long int msg_type;  
         char some_text[MAX_TEXT];  
 };  
 int main()  
 {   
         int msgid;  
         struct my_msg some_data;  
         char buffer[50]; //For storing user input  
         key_t key = 8880;
         msgid=msgget(key, 0666|IPC_CREAT);  
         if (msgid == -1)  
         {       // returns -1 on error 
                 perror("Error in creating queue\n");  
                 exit(0);  
         }  
  
         while(1)  
         {  
                 printf("Enter some text:\n");  
                 fgets(buffer,50,stdin);  
                 some_data.msg_type=1;  
                 strcpy(some_data.some_text,buffer);  
                 if(msgsnd(msgid,(void *)&some_data, sizeof(some_data),0)==-1)   
                 {       // returns -1 on error
                         perror("Msg not sent\n");  
                 }  
                 if(strncmp(buffer,"end",3)==0)  
                 {  
                         break;  
                 }  
         }  
         printf("out of while loop\n");
 }  
