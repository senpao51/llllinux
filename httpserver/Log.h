#pragma once 
#include <iostream>
#include <sys/time.h>
using namespace std;

#define ARG_ERROR  1
#define SOCKET_ERROR 2
#define BIND_ERROR 3
#define LISTEN_ERROR 4


#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4

string level_string[] = {"UNKNOW","NORMAL","WARNING","ERROR","FATAL"};
//日志  等级，时间，消息，文件名，行数 
uint64_t GetTimeStamp()
{
	struct timeval now;
	if(gettimeofday(&now,nullptr)==0)
	{
		return now.tv_sec;
	}
}
void Log(int level,string msg,string filename,int line)
{
	if(level<1||level>4)
	{
		level = 0;
	}
	cout<<"[ "<<level_string[level]<<" ][ "<<GetTimeStamp()<<" ][ "<<msg<<" ][ "<<filename<<" ][ "<<line<<" ]"<<endl;
}

#define LOG(level,msg) Log(level,msg,__FILE__,__LINE__)
