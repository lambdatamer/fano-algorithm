#pragma once
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

/** Comfortable logging function
 * @param _item log item
 */
template<typename T>
void log(T &_item){
	cout << _item << endl;
}

/** Converts any type with declared operator<< into string
 * @param _val an entity which will be converted into string
 * @return converted 
 */
template <typename T>
string toString(T _val)
{
	ostringstream oss;
	oss << _val;
	return oss.str();
}

/** Converts string into any type with declared operator<< 
 * @param _string which will be converted
 * @return string converted into another type
 */
template<typename T> 
T fromString(const string& _string) 
{
	istringstream iss(_string);
	T res;
	iss >> res;
	return res;
}

/** Flips elements in the pair.
 * Used in flip_map
 * @param _pair original pair
 * @return flipped pair
 */
template<typename A, typename B>
pair<B,A> flip_pair(const pair<A,B> &_pair){
	return pair<B,A>(_pair.second, _pair.first);
}

/** Flips all keys with appropriate values
 * @param _src original map
 * @return flipped map
 */
template<typename A, typename B>
map<B,A> flip_map(const map<A,B> &_src){
	map<B,A> dst;
	transform(_src.begin(), _src.end(), inserter(dst, dst.begin()), 
		flip_pair<A,B>);
	return dst;
}

/** Converts int value into binary
 * @return string containing binary code
 */
string decToBin(int dec);

/** Converts string with binary code into int value
 * @return int value
 */
int binToDec(string &str);

/** Converts char value into binary
 * @return string containing binary code
 */
string charToBin(char c);
