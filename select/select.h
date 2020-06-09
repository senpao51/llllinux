#include <iostream>
#include <strings.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
using namespace std;
class SelectServer
{
private:
	int port;
	int listen_sock;
public:
	SelectServer(int _port):port(_port),listen_sock(0)
	{}
	~SelectServer()
	{}
	void InitServer()
	{	

		struct sockaddr_in local;
		bzero(&local,sizeof(local));
		local.sin_family = AF_INET;
		local.sin_port = htons(port);
		local.sin_addr.s_addr = INADDR_ANY;
		socklen_t len = sizeof(local);
		listen_sock = socket(AF_INET,SOCK_STREAM,0);
		if(listen_sock<0)
		{
			cerr<<"listen error!"<<endl;
			exit(2);
		}
		//int opt = 1;
		//setsocketopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
		if(bind(listen_sock,(struct sockaddr*)&local,len)<0)
		{
			cerr<<"bind error!"<<endl;
			exit(3);
		}
		if(listen(listen_sock,5)<0)
		{
			cerr<<"listen error"<<endl;

		}
	}
	void Start()
	{
		while(1)
		{
			//accept本质上是读事件，可以用select完成
			struct timeval tv = {0,0};
			fd_set fset;
			FD_ZERO(&fset);
			FD_SET(listen_sock,&fset);
			int maxfd = listen_sock+1;
			switch(select(maxfd,&fset,nullptr,nullptr,&tv))
			{
				case -1:
					cerr<<"select error!"<<endl;
					break;
				case 0:
					cerr<<"time out!"<<endl;
					break;
				default:
					cout<<"select success"<<endl;
					break;
			}
		}
	}
};
