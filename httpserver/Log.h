#pragma once 
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
using namespace std;

#define ARG_ERROR  1
#define SOCKET_ERROR 2
#define BIND_ERROR 3
#define LISTEN_ERROR 4

#define OTHER  -1
#define NORMAL 1
#define WARNING 2
#define ERROR 3
#define FATAL 4

//string level_string[] = {"UNKNOW","NORMAL","WARNING","ERROR","FATAL"};
//日志  等级，时间，消息，文件名，行数 
time_t GetTimeStamp()
{
	struct timeval now;
	if(gettimeofday(&now,nullptr)==0)
	{
		return now.tv_sec;
	}
}
string GetDateTime()
{
	time_t time = GetTimeStamp();
    tm *tm_ = localtime(&time);                // 将time_t格式转换为tm结构体
    int year, month, day, hour, minute, second;// 定义时间的各个int临时变量。
    year = tm_->tm_year + 1900;                // 临时变量，年，由于tm结构体存储的是从1900年开始的时间，所以临时变量int为tm_year加上1900。
    month = tm_->tm_mon + 1;                   // 临时变量，月，由于tm结构体的月份存储范围为0-11，所以临时变量int为tm_mon加上1。
    day = tm_->tm_mday;                        // 临时变量，日。
    hour = tm_->tm_hour;                       // 临时变量，时。
    minute = tm_->tm_min;                      // 临时变量，分。
    second = tm_->tm_sec;                      // 临时变量，秒。
    char yearStr[5], monthStr[3], dayStr[3], hourStr[3], minuteStr[3], secondStr[3];// 定义时间的各个char*变量。
    sprintf(yearStr, "%d", year);              // 年。
    sprintf(monthStr, "%d", month);            // 月。
    sprintf(dayStr, "%d", day);                // 日。
    sprintf(hourStr, "%d", hour);              // 时。
    sprintf(minuteStr, "%d", minute);          // 分。
    if (minuteStr[1] == '\0')                  // 如果分为一位，如5，则需要转换字符串为两位，如05。
    {
        minuteStr[2] = '\0';
        minuteStr[1] = minuteStr[0];
        minuteStr[0] = '0';
    }
    sprintf(secondStr, "%d", second);          // 秒。
    if (secondStr[1] == '\0')                  // 如果秒为一位，如5，则需要转换字符串为两位，如05。
    {
        secondStr[2] = '\0';
        secondStr[1] = secondStr[0];
        secondStr[0] = '0';
    }
    char s[20];                                // 定义总日期时间char*变量。
    sprintf(s, "%s-%s-%s %s:%s:%s", yearStr, monthStr, dayStr, hourStr, minuteStr, secondStr);// 将年月日时分秒合并。
    string str(s);                             // 定义string变量，并将总日期时间char*变量作为构造函数的参数传入。
    return str;                                // 返回转换日期时间后的string变量。
}
void Log(string level,string msg,string filename,int line)
{
	cout<<"[ "<<level/*level_string[level]*/<<" ][ "<<GetDateTime()<<" ][ "<<msg<<" ][ "<<filename<<" ][ "<<line<<" ]"<<endl;
}

#define LOG(level,msg) Log(#level,msg,__FILE__,__LINE__)
