#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<bits/stdc++.h>
using namespace std;
int main()
{
fstream file;
int sock;
int sum=0;
int rsum[100];
int csum[100];
int rmax,rmin,cmax,cmin;
int min,max;
int ld=0;
int rd=0;
int tt[100][100];
int arr[100][100];
int m,n;
int a,i;
char c[100];
char d[100]="hi";
char e[100];
char word[100];
int l;
char g;
int count=0;
char ch[3]="no";
char ch1[30];
char v[10]="@123";

unsigned int len;

struct sockaddr_in client;

if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
{
perror("socket: ");
exit(-1);
}

client.sin_family=AF_INET;
client.sin_port=htons(10000);

client.sin_addr.s_addr=INADDR_ANY;

bzero(&client.sin_zero,0);

len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1)
{
perror("connect: ");
exit(-1);
}
while(1)
{
	file.open("exam.txt",ios::in|ios::out|ios::trunc);
	if(!file.is_open()) cout<<"\nError while opening the file\n";	
	else
	{
	cout<<"\nenter the dimensions of matrix  \n";
	cin>>m>>n;
	send(sock,&m,sizeof(m),0);
	send(sock,&n,sizeof(n),0);	
	
	cout<<"\nenter the values of matrix\n";
	for(int ii=0;ii<m;ii++)
	{
		for(int j=0;j<n;j++)
			{
			cin>>arr[ii][j];
			file<<arr[ii][j]<<" ";
			send(sock,&arr[ii][j],sizeof(arr[ii][j]),0);	
			}
			file<<endl;
	}	file.close();
	
	/*for(int ii=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			{
			cout<<arr[ii][j]<<" ";
			}
			cout<<endl;
	}*/		
	
	
	/*else
	{
		for(int ii=0;i<m;i++)
		{
			for(int j=0;j<n;j++)
			{
				file<<arr[ii][j];
			}
		}
		file.close();*/
		/*cout<<"\nUPLOADING STARTED\n";
		for(int ii=0;ii<m;ii++)
		{
			for(int j=0;j<n;j++)
			{
				send(sock,&arr[ii][j],sizeof(arr[ii][j]),0);	
			}
		}
		cout<<"\nUPLOADING COMPLETED\n";*/
		
		recv(sock,&g,sizeof(g),0);
		if(g=='y')
		/*cout<<"\nupload complete\n";
		cout<<endl<<"transpose\n"
		for(int ii=0;ii<n;ii++)
{
	for(int j=0;j<m;j++)
	{
	
	recv(sock,&tt[ii][j],sizeof(tt[ii][j]),0);
	cout<<tt[ii][j]<<" ";
	}cout<<endl;
}*/
		recv(sock,&sum,sizeof(sum),0);
		cout<<"\nsum="<<sum<<endl;
		recv(sock,&max,sizeof(max),0);
		cout<<"\nmax element in matrix="<<max<<endl;
		recv(sock,&min,sizeof(min),0);
		cout<<"\nmin element in matrix="<<min<<endl;
		//cout<<"\nrow wise sum\n";
		/*for(int ii=0;ii<m;ii++)
		{
		recv(sock,&rsum[ii],sizeof(rsum[ii]),0);
		cout<<rsum[ii]/2<<endl;
		}
		cout<<"\ncolumn wise sum\n";
		for(int ii=0;ii<n;ii++)	
		{
		recv(sock,&csum[ii],sizeof(csum[ii]),0);
		cout<<csum[ii]/2<<endl;
		}*/
		printf("\nto exit press ......no\n");
		scanf("%s",ch1);

		if((i=strcmp(ch,ch1))==0)
		{
		close(sock);
		exit(0);
		}
	}
	
}
}




















