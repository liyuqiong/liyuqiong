#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
using namespace std;

int main()
{
	//定义sockfd
	int server_sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(server_sockfd < 0)
	{
		perror("server socket");
		exit(1);
	}

	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET;
	server_sockaddr.sin_port = htons(8023);
	server_sockaddr.sin_addr.s_addr = inet_addr("192.168.200.168");

	if(bind(server_sockfd,(struct sockaddr*)&server_sockaddr,sizeof(server_sockaddr)) < 0)
	{
		perror("bind");
		exit(1);
	}

	if(listen(server_sockfd,20) < 0)
	{
		perror("listen");
		exit(1);
	}

	//客户端套接字
	struct sockaddr_in client_addr;
	socklen_t length = sizeof(client_addr);

	int conn = accept(server_sockfd,(struct sockaddr*)&client_addr,&length);
	if(conn < 0)
	{
		perror("accept");
		exit(1);
	}
	cout<<"客户端连接成功"<<endl;

	//接收缓冲区
	char buffer[100];

	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		int len = recv(conn,buffer,sizeof(buffer),0);
		if(len <= 0 || strcmp(buffer,"exit") == 0)
		{
			break;
		}
		cout<<"收到客户端信息:"<<buffer<<endl;
	}
	close(conn);
	close(server_sockfd);
	return 0;
}
