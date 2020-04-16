#pragma once 
#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
using namespace std;


class Server
{
	public:
		Server(string _ip,short _port):ip(_ip),port(_port),socketfd(-1)
		{}
		~Server()
		{
			if(socketfd>=0)
			{
				close(socketfd);
			}
		}
	public:
		void InitServer()
		{
			socketfd = socket(AF_INET,SOCK_STREAM,0);
			if(socketfd<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			struct sockaddr_in ser;
			ser.sin_family = AF_INET;
			ser.sin_port = htons(port);
			ser.sin_addr.s_addr = inet_addr(ip.c_str());
			int bd = bind(socketfd,(sockaddr*)&ser,sizeof(ser));
			if(bd<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			int lis = listen(socketfd,5);
			if(lis<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
		}
		void Run()
		{
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			while(1)
			{
				int newfd = accept(socketfd,(sockaddr*)&peer,&len);
				if(newfd<0)
				{
					cerr<<"accept error"<<endl;
					continue;
				}
				ServerIO(newfd);
			}
		}
		void ServerIO(int fd)
		{
			while(1)
			{
				char buf[1024] = {0};
				ssize_t s = read(fd,buf,sizeof(buf));
				if(s>0)
				{
					cout<<"来自client的消息:"<<buf<<endl;
					write(fd,buf,sizeof(buf));
				}
				else if(s==0)
				{
					cout<<"client quit"<<endl;
					break;
				}
				else
				{
					cerr<<"read error"<<endl;
					break;
				}
			}
			close(fd);
		}
	private:
		int socketfd;
		short port;
		string ip;
};
