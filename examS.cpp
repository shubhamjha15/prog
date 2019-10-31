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
#include<fstream>
using namespace std;
int main()
{
int sum=0;
int rsum[100]={0};
int csum[100]={0};
int rmax=-99,rmin=73293,cmax=-7329873,cmin=9839;

int min=98239,max=-28383;
int ld=0;
int rd=0;
int tt[100][100];
fstream file;
int ssock,csock;
int arr[100][100];
int m,n;
char c[100];
char d[100];
char e[100]="hello";
char word[100];

char t;

char ch[3];
char ch1[3]="no";

int a,i;
unsigned int len;

struct sockaddr_in server,client;

if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
{
perror("socket: ");
exit(-1);
}

server.sin_family=AF_INET;
server.sin_port=htons(10000);

server.sin_addr.s_addr=INADDR_ANY;

bzero(&server.sin_zero,0);

len=sizeof(struct sockaddr_in);
if((bind(ssock,(struct sockaddr *)&server,len))==-1)
{
perror("bind error: ");
exit(-1);
}

if((listen(ssock,5))==-1)
{
perror("listen error: ");
exit(-1);
}

if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
{
perror("accept error: ");
exit(-1);
}

while(1)
{
file.open("et.txt",ios::in|ios::out|ios::trunc);
if(!file.is_open()) cout<<"\nerror while accessing file\n";
else
{
recv(csock,&m,sizeof(m),0);
recv(csock,&n,sizeof(n),0);
cout<<"\nrecieved dimensions are "<<m<<"x"<<n<<endl;
for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
			{
			recv(csock,&arr[i][j],sizeof(arr[i][j]),0);
			file<<arr[i][j]<<" ";
			}
			file<<endl;
	}
}
//printf("server:%s\n",e);

//send(csock,&e,sizeof(e),0);
//recv(csock,&word,sizeof(word),0);
//recv(csock,&a,sizeof(a),0);
//printf("word and no recieved are %s and %d\n",word,a);

/*l=strlen(word);
for(k=0;k<l;k++)
{
cnt=0;
	for(j=0;j<l;j++)
	{
		if(word[k]==word[j])
		{
			cnt++;
		}
	}

	if(cnt==a)
	{
		t=word[k];
		break;
	}
	else
	{
		if(cnt>max)
		{
			t=word[k];
			max=cnt;
		}
	}
}
printf("\nsend character is %c\n",t);*/
t='y';

send(csock,&t,sizeof(t),0);
for(int i=0;i<m;i++)
{
	for(int j=0;j<n;j++)
	{
	if(arr[i][j]>max)
	{
	max=arr[i][j];
	}
	if(arr[i][j]<min)
	{
	min=arr[i][j];
	}
	sum+=arr[i][j];

	/*for(int j=0;j<n;j++)
	{
	rsum[i]+=arr[i][j];
	}*/
	//ld+=arr[i];
}

}
/*for(int i=0;i<n;i++)
{
	for(int j=0;j<m;j++)
	{
	tt[i][j]=arr[j][i];
	send(csock,&tt[i][j],sizeof(tt[i][j]),0);
	}
}*/
/*for(int i=0;i<n;i++)
{
	for(int j=0;j<m;j++)
	{
	csum[i]+=arr[i][j];
	}
}*/

send(csock,&sum,sizeof(sum),0);
send(csock,&max,sizeof(max),0);
send(csock,&min,sizeof(min),0);

for(int i=0;i<m;i++)
{
send(csock,&rsum[i],sizeof(rsum[i]),0);
}
for(int i=0;i<n;i++)
{
send(csock,&csum[i],sizeof(csum[i]),0);
}}
close(ssock);

}





























