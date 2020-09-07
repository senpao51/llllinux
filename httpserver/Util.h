#pragma once 
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <unordered_map>
using namespace std;


class Util
{
public:
	static void MakeKV(unordered_map<string,string>& header_map,string& str)
	{
		auto pos = str.find(": ");
		if(string::npos == pos)
			return;
		string s1 = str.substr(0,pos);
		string s2 = str.substr(pos+2,string::npos);
		header_map.insert({s1,s2});
	}
	static int StringToInt(string &s)
	{
		stringstream ss(s);
		int count = 0;
		ss>>count;
		return count;
	}
	static string IntToString(int num)
	{
		stringstream ss;
		ss<<num;
		string s = ss.str();
		return s;
	}
	static string SuffixToType(string suffix)
	{
		if(suffix==".html"||suffix=="htm")
			return "text/html";
		else if(suffix==".js")
			return "application/x-javascript";
		else if(suffix==".css")
			return "text/css";
		else if(suffix==".jpg")
			return "application/x-jpg";
		else
			return "text/html";
	}
	static string GetResponseLine(int code)
	{
		switch(code)
		{
			case 200:
				return "HTTP/1.0 200 OK\r\n";
				break;
			case 404:
				return "HTTP/1.0 404 NotFound\r\n";
				break;
			default:
				return "HTTP/1.0 200 OK\r\n";
				break;
		}
	}
	static void GetNumber(int& num1,int& num2)
	{		
	}
};
