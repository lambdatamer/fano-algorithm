#include <string>
#include <algorithm>
#include <cmath>

#include "lib.hpp"

using namespace std;

string decToBin(int dec){
	string &bin = *(new string);
	int rem;
	int tmp;
	while(true){
		rem = dec % 2;
		tmp = dec / 2;
		bin += toString(rem);
		if(tmp < 2){
			bin += toString(tmp);
			break;
		}
		dec = tmp;
	}
	reverse(bin.begin(), bin.end());
	return bin;
}

int binToDec(string &str){
	int ret = 0;
	int len = str.length();
	int offset;
	for(int i = 0; i < len; i++){
		if(str[i] == '1'){
			offset = len - i - 2;
			if(offset < 0){
				ret += 2 >> (-offset);
			}else{
				ret += 2 << offset;
			}
		}
	}
	return ret;
}