#pragma once 
#include "common.h"
#include "type.h"
class Client
{
	public:
		Client(std::string _ip,int _port):ip(_ip),port(_port),sockfd(-1)
		{}
		~Client()
		{
			if(sockfd>=0)
			{
				close(sockfd);
			}
		}
	public:
		void InitClient()
		{
			sockfd = Pro::Sock();
		}
		void Run()
		{
			Pro::Connect(sockfd,ip,port);
			while(1)
			{
				request_t rq;
				response_t rp;
				memset(&rq,0,sizeof(rq));
				memset(&rp,0,sizeof(rp));
				std::cout<<"请输入两个操作数:";
				std::cin>>rq.x;
				std::cin>>rq.y;
				std::cout<<"请输入运算符:";
				std::cin>>rq.op;
				write(sockfd,&rq,sizeof(rq));
				ssize_t s = read(sockfd,&rp,sizeof(rp));
				if(s>0)
				{
					switch(rp.status)
					{
						case 0:
							std::cout<<rq.x<<" "<<rq.op<<" "<<rq.y<<" = "<<rp.result<<std::endl;
							break;
						case -1:	
							std::cout<<"除数不能为0"<<std::endl;							
							break;
						case -2:
							std::cout<<"取模数不能为0"<<std::endl;
							break;
						case -3:
							std::cout<<"操作符无效"<<std::endl;
							break;
						default:
							break;
					}
				}
				else 
					break;
			}
			close(sockfd);
			sockfd = -1;
		}
	private:
		int sockfd;
		std::string ip;
		int port;
};
