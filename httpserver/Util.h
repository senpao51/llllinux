#pragma once 
#include <iostream>
#include <unordered_map>
#include <string>
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
};
