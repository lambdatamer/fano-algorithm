#pragma once
#include <iostream>
#include <sstream>
#include <map>

template<typename T>
void log(T &item){
	std::cout << item << std::endl;
}

template <typename T>
std::string toString(T val)
{
    std::ostringstream oss;
    oss<< val;
    return oss.str();
}

template<typename T> 
T fromString(const std::string& s) 
{
  std::istringstream iss(s);
  T res;
  iss >> res;
  return res;
}

std::string decToBin(int dec);
int binToDec(std::string &str);

template <typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p){
  return std::pair<B,A>(p.second, p.first);
}

template <typename A, typename B>
std::map<B,A> flip_map(const std::map<A,B> &src){
  std::map<B,A> dst;
  std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), flip_pair<A,B>);
  return dst;
}