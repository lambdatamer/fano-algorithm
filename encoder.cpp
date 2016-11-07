#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>

#include "encoder.hpp"
#include "charmap.hpp"
#include "lib.hpp"

using namespace std;

string* Encoder::getInputString(){
	ifstream file;
	file.open("files//input.txt", ios_base::in);
	
	auto inStr = new string;
	char tmp;

	while(true){
		tmp = file.get();
		if (tmp == EOF){
			break;
		}
		*inStr += tmp;
	}

	file.close();
	
	cout << *inStr << endl;

	return inStr;
	}

void Encoder::encode(){
	auto inputStr = getInputString();
	if (inputStr->length() == 0){
		return;
	}

	CharMap cm(*inputStr);
	auto cMap = cm.get();
	for(auto i = cMap->begin(); i != cMap->end(); i++){
		cout << i->first << " : " << i->second << endl;
	}
}
