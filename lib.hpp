#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

template<typename T>
void log(T &_item){
	cout << _item << endl;
}

template <typename T>
string toString(T _val)
{
	ostringstream oss;
	oss << _val;
	return oss.str();
}

template<typename T> 
T fromString(const string& _string) 
{
	istringstream iss(_string);
	T res;
	iss >> res;
	return res;
}

template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &_pair){
	return pair<B,A>(_pair.second, _pair.first);
}

template<typename A, typename B>
map<B,A> flip_map(const map<A,B> &_src){
	map<B,A> dst;
	transform(_src.begin(), _src.end(), inserter(dst, dst.begin()), 
		flip_pair<A,B>);
	return dst;
}

string decToBin(int dec);
int binToDec(string &str);
string charToBin(char c);
