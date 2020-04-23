#pragma once 
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>

#define DEAFAULT_BACKLOG 10
class Pro
{
	public:
		static int Sock()
		{
			int sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock<0)
			{
				std::cerr<<"socket error"<<std::endl;
				exit(2);
			}
			return sock;
		}
		static void Bind(int sock,std::string ip,int port)
		{
			struct sockaddr_in local;
			socklen_t len = sizeof(local);
			bzero(&local,sizeof(local));
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			if(bind(sock,(struct sockaddr*)&local,len)<0)
			{
				std::cerr<<"bind error"<<std::endl;
				exit(3);
			}
			else
			{
				std::cout<<"bind successfully"<<std::endl;
			}
		}
		static void Listen(int sock,int backlog)
		{
			if(listen(sock,backlog)<0)
			{
				std::cerr<<"listen error"<<std::endl;
				exit(4);
			}
			else
			{
				std::cout<<"listen successfully"<<std::endl;
			}
		}
		static int Accept(int sock)
		{
			sockaddr_in peer;
			socklen_t len = sizeof(peer);
			int newsock = accept(sock,(sockaddr*)&peer,&len);
			if(newsock<0)
			{
				std::cerr<<"accpet error"<<std::endl;
			}
			else
			{
				std::cout<<"accept successfully"<<std::endl;
			}
			return newsock;
		}
		static void Connect(int sock,std::string ip,int port)
		{
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			bzero(&peer,sizeof(peer));
			peer.sin_family = AF_INET;
			peer.sin_port = htons(port);
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			if(connect(sock,(struct sockaddr*)&peer,len)<0)
			{
				std::cerr<<"connect error"<<std::endl;
				exit(5);
			}
			else
			{
				std::cerr<<"connect successfully"<<std::endl;
			}
		}
		static void Send(int sock,std::string& input)
		{
			write(sock,input.c_str(),input.size());
		}
		static bool Recv(int sock,std::string& output)
		{
			bool flag = true;
			char buf[1024];
			ssize_t s = read(sock,buf,sizeof(buf)-1);
			if(s>0)
			{
				buf[s] = 0;
				output = buf;
			}
			else if(s==0)
			{
				std::cout<<"客户"<<sock<<"中断连接"<<std::endl;
				close(sock);
				flag = false;
			}
			else
			{
				std::cerr<<"read error"<<std::endl;
				close(sock);
				flag = false;
			}
		}
};
