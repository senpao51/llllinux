#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <iostream>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>
#include <stdlib.h>
#include <strings.h>
#include <netinet/in.h>
using namespace std;
class Client
{
	public:
		Client(string _ip,short _port):ip(_ip),port(_port),socketfd(-1)
		{}
		~Client()
		{
			if(socketfd>=0)
			{
				close(socketfd);
			}
		}
		void InitClient()
		{
			socketfd = socket(AF_INET,SOCK_DGRAM,0);
			if(socketfd<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}			
		}
		void Run()
		{
			struct sockaddr_in sockser;
			bzero(&sockser,sizeof(sockser));
			sockser.sin_family = AF_INET;
			sockser.sin_port = htons(port);
			sockser.sin_addr.s_addr = inet_addr(ip.c_str());
			socklen_t len = sizeof(sockser);
			string msg;
			while(1)
			{
				cout<<"请输入信息:"<<endl;
				cin>>msg;
				ssize_t s = sendto(socketfd,msg.c_str(),msg.size(),0,(const struct sockaddr*)&sockser,len);
				if(s<0)
				{
					cerr<<"sendto error"<<endl;
					exit(3);
				}
			}
		}
	private:
		short port;
		string ip;
		int socketfd;
};
#endif
