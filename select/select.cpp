#include <iostream>
#include "select.h"
using namespace std;
void Usage(char* proc)
{
	cout<<proc<<" port"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		Usage(argv[0]);
		exit(2);
	}
	SelectServer ss(atoi(argv[1]));
	ss.InitServer();
	ss.Start();
	return 0;
}
