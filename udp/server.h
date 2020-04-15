#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
#include <string>
#include <strings.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
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
			socketfd = socket(AF_INET,SOCK_DGRAM,0);
			if(socketfd<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			struct sockaddr_in sockser;
			bzero(&sockser,sizeof(sockser));
			sockser.sin_family = AF_INET;
			sockser.sin_port = htons(port);
			sockser.sin_addr.s_addr = inet_addr(ip.c_str());
			int bd = bind(socketfd,(const struct sockaddr*)&sockser,sizeof(sockser));
			if(bd<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"server is running on "<<ip<<":"<<port<<endl;
		}
		void Run()
		{
			struct sockaddr_in peer;
			while(1)
			{
				char buf[1024] = {0};
				socklen_t len = sizeof(peer);
				ssize_t s = recvfrom(socketfd,buf,sizeof(buf),0,(struct sockaddr*)&peer,&len);
				if(s<0)
				{
					cerr<<"recvfrom error"<<endl;
					exit(4);
				}
				cout<<"收到来自client的消息:"<<buf<<endl;
			}
		}
	private:
		short port;
		string ip;
		int socketfd;
};
#endif
