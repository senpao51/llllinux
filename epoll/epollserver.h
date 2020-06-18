#pragma once 
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <strings.h>
#include <sys/epoll.h>
using namespace std;

class Sock
{
public:
	static int Socket()
	{
		int sock = socket(AF_INET,SOCK_STREAM,0);
		if(sock<0)
		{
			cerr<<"socket error!"<<endl;
			exit(2);
		}
		int opt = 1;
		setsocketopt(sock,SQL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
		return sock;
	}
	static void Bind(int sock,int port)
	{
		struct sockaddr_in local;
		bzero(&local,sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = INADDR_ANY;
		socklen_t len = sizeof(local);
		if(bind(sock,(struct sockaddr*)&local,len)<0)
		{
			cerr<<"bind error!"<<endl;
			exit(3);
		}
	}
	static void Listen(int sock)
	{
		const int backlog = 5;
		if(listen(sock,backlog)<0)
		{
			cerr<<"listen sock!"<<endl;
			exit(4);
		}
	}
	static int Accept(int sock,int port)
	{
		struct sockaddr_in peer;
		socklen_t len = sizeof(peer);
		int newsock = accept(sock,(struct sockaddr*)&peer,&len);
		if(newsock<0)
		{
			cerr<<"accept error!"<<endl;
			return -1;
		}
		return newsock;
	}
};




class EpollServer()
{
public:
	EpollServer(int _port):port(_port),listen_sock(-1),epfd(-1)
	{}
	~EpollServer()
	{
		if(listen_sock>=0)
			close(listen_sock);
		if(epfd>=0)
			close(epfd);
	}
	void InitEpollServer()
	{
		epfd = epoll_create(128);
		listen_sock = Sock::Socket();
		Sock::Bind(listen_sock,port);
		Sock::Listen(listen_sock);
	}
	void Run()
	{



	}
private:
	int listen_sock;
	int port;
	int epfd;//epoll句柄
};
