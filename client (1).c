/*Client code*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


#define buffer_size 32
void clearBuf(char* b)
{
    int i;
    for (i = 0; i < buffer_size; i++)
        b[i] = '\0';
}
  

  
// function to receive file
int recvFile(char* buf)
{
    int i;
    char ch;
    for (i = 0; i < buffer_size; i++) {
        ch = buf[i];
    
        if (ch == EOF)
            return 1;
        else
            printf("%c", ch);
    }
    return 0;
} 
int main()
{
int sock;
// client socket discriptor

struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
// client socket is created.
{
perror("socket: ");
exit(-1);
}
client.sin_family=AF_INET;
client.sin_port=htons(10000);
// initializing socket parameters
client.sin_addr.s_addr=INADDR_ANY;
bzero(&client.sin_zero,0);
// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
int len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1)
//connecting to client
{
perror("connect: ");
exit(-1);
}


// sending data to server(sending otp)
//send(sock,&msg_crc,sizeof(msg_crc),0);


// receiving data from server
//recv(sock,&divisor,sizeof(divisor),0);
char net_buf[buffer_size];
while (1) {
        printf("\nPlease enter file name to receive:\n");
        scanf("%s", net_buf);
        sendto(sock, net_buf, buffer_size,
               0, (struct sockaddr*)&client,
               len);
  
        printf("\n---------Data Received---------\n");
  
        while (1) {
            // receive
            clearBuf(net_buf);
            recvfrom(sock, net_buf, buffer_size,
                              0, (struct sockaddr*)&client,
                              &len);
  
            // process
            if (recvFile(net_buf)) {
                break;
            }
        }
        printf("\n-------------------------------\n");
    } 

close(sock);
exit(0);

}

