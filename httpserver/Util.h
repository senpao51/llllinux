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
		unordered_map<string,string> mp;
		mp.insert({".js","application/x-javascipt"});
		mp.insert({".css","text/css"});
		mp.insert({".jpg","application/x-jpg"});
		mp.insert({".html","text/html"});
		return mp[suffix];
	}
};
