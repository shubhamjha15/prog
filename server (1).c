/*Server code*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define buffer_size 100
char no_file[] = "file not found!";
void clear(char *a)
{
   int i;
   for(i=0;i<buffer_size;i++)
       a[i]='\0';
}

int send_file(FILE *fp,char *buffer){

    if(!fp){
         strcpy(buffer,no_file);
         int len=strlen(no_file);
         buffer[len]=EOF;
         return 1;
    }
    int i=0;
    char ch;
    for (i = 0; i < buffer_size; i++) {
        ch = fgetc(fp);
        buffer[i] = ch;
        if (ch == EOF)
            return 1;
    }
    return 0; 
    
}

int main()
{
int ssock,csock;
// creating server and client socket discriptor

unsigned int len;
struct sockaddr_in server,client;
// creating server & client socket object
if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
// creating socket
{
perror("socket: ");
exit(-1);
}
server.sin_family=AF_INET;
server.sin_port=htons(10000);
// initializing server socket parameters.
server.sin_addr.s_addr=INADDR_ANY;
bzero(&server.sin_zero,0);
// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
len=sizeof(struct sockaddr_in);
if((bind(ssock,(struct sockaddr *)&server,len))==-1)
// binding port & IP
{
perror("bind error: ");
exit(-1);
}
if((listen(ssock,5))==-1)
// listening for client
{
perror("listen error: ");
exit(-1);
}
if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
// accepting connection
{
perror("accept error: ");
exit(-1);
}



//recieves the string from client
//recv(csock,&msg,sizeof(msg),0);

//sends the string to client(sending key);
//send(csock,&key,sizeof(key),0);

char buffer[buffer_size];
FILE* fp;
while(1){
    //recieve file name(buffer contains file name)
    clear(buffer);
    recvfrom(csock,buffer,buffer_size,0,(struct sockaddr*)&server, &len);
    fp=fopen(buffer,"r");
    printf("\nFile Name Received: %s\n", buffer);
    if (fp == NULL)
          printf("\nFile open failed!\n");
    else
          printf("\nFile Successfully opened!\n"); 

     while (1) {
  
            // process
            if (send_file(fp, buffer)) {
                sendto(csock, buffer, buffer_size,
                       0, 
                    (struct sockaddr*)&server, len);
                break;
            }
  
            // send
            sendto(csock, buffer, buffer_size,
                   0,
                (struct sockaddr*)&server, len);
            clear(buffer);
        }
        if (fp != NULL)
            fclose(fp);
    } 

    


close(ssock);

return 0;
}
