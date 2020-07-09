#pragma once 
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include "Log.h"
using namespace std;

#define BACKLOG 5
class Sock
{
public:
	static int Socket()
	{
		int sock = socket(AF_INET,SOCK_STREAM,0);
		if(sock<0)
		{
			LOG(FATAL,"socket error!");
			exit(SOCKET_ERROR);
		}
		int opt = 1;
		socklen_t len = sizeof(opt);
		setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,len);
		return sock;
	}
	static void Bind(int sock,int port)
	{
		struct sockaddr_in local;
		socklen_t len = sizeof(local);
		bzero(&local,sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = INADDR_ANY;
		if(bind(sock,(struct sockaddr*)&local,len)<0)
		{
			LOG(FATAL,"bind error!");
			exit(BIND_ERROR);
		}
	}
	static void Listen(int sock)
	{
		if(listen(sock,BACKLOG)<0)
		{
			LOG(FATAL,"listen error!");
			exit(LISTEN_ERROR);
		}
	}
	static int Accept(int sock)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		cout<<"5"<<endl;
		int _sock = accept(sock,(struct sockaddr*)&peer,&len);
		if(_sock<0)
		{
			LOG(ERROR,"accpet new socket error!");
		}
		return _sock;
	}
};
