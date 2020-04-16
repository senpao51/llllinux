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
	public:
		void InitClient()
		{
			socketfd = socket(AF_INET,SOCK_STREAM,0);
			if(socketfd<0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			else
			{
				cout<<"socket successfully!"<<endl;
			}
		}
		void Connect()
		{
			struct sockaddr_in ser;
			ser.sin_family = AF_INET;
			ser.sin_port = htons(port);
			ser.sin_addr.s_addr = inet_addr(ip.c_str());
			int c = connect(socketfd,(struct sockaddr*)&ser,sizeof(ser));
			if(c<0)
			{
				cerr<<"connect error"<<endl;
				exit(3);
			}
			else
			{
				cout<<"connect successfully!"<<endl;
			}
		}
		void Run()
		{
			string msg;
			while(1)
			{
				cout<<"请输入信息:";
				cin>>msg;
				write(socketfd,msg.c_str(),msg.size());
				if(msg=="q"||msg=="quit")
				{
					cout<<"Run quit!"<<endl;
					break;
				}
				char buf[1024] = {0};
				ssize_t s = read(socketfd,buf,sizeof(buf));
				if(s>0)
				{
					cout<<"来自server的消息:"<<buf<<endl;
				}
			}
		}
	private:
		int socketfd;
		string ip;
		short port;
};
