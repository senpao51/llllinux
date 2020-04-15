#include "client.h"

void method(char* udp_msg)
{
	cout<<udp_msg<<" server ip server port"<<endl;
}

int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		method(argv[0]);
		exit(2);
	}	
	Client ce(argv[1],atoi(argv[2]));
	ce.InitClient();
	ce.Run();
	return 0;
}
