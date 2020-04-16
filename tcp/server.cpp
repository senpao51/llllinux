#include "server.h"

void method(char*msg)
{
	cout<<msg<<" server ip server port"<<endl;
}
int main(int argc,char*argv[])
{
	if(argc!=3)
	{
		method(argv[0]);
		exit(2);
	}
	Server sv(argv[1],atoi(argv[2]));
	sv.InitServer();
	sv.Run();
	return 0;
}
