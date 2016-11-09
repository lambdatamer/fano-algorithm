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
	
	return inStr;
}

void writeDWordToFile(ofstream &file, int dword){
	int* ptr = &dword;

	char* c = reinterpret_cast<char*>(ptr);
	
	file.write(c, 4);
} 

int writeBinStringToFile(ofstream &file, string &str){
	/*
		Returns amount of the bytes had been written.
	*/
	int counter = 0;
	bitset<8> tmp;
	bitset<8> mask("10000000");
	int len = str.length();
	char* byte = reinterpret_cast<char*>(&tmp);

	for(int i = 0; ; i+=8){
		tmp.reset();
		for(int j = i; j < len; j++){
			if(j == i + 8){
				break;
			}
			if(str[j] == '1'){
				tmp^=mask;
			}
			tmp>>=1;
		}
		file << *byte;
		counter++;
		if (i > len){
			break;
		}
	}

	return counter;
}

void makeOutputFile(map<char,string> &charMap, string &str){
	ofstream file;
	file.open("files//output.fano", ios_base::binary);

	writeDWordToFile(file, charMap.size());
	
	file.seekp(16, ios_base::beg);

	string bitMap;
	for (auto i = charMap.begin(); i != charMap.end(); i++){
		file << i->first << static_cast<char>(i->second.length());
		bitMap += i->second;
	}

	file.seekp(4, ios_base::beg);
	writeDWordToFile(file, bitMap.length());

	file.seekp(0, ios_base::end);
	int bitMapLength = writeBinStringToFile(file, bitMap);

	file.seekp(8, ios_base::beg);
	int dataPtr = (4*4 + charMap.size() * 2 + bitMapLength);
	writeDWordToFile(file, dataPtr);
	cout << dataPtr << endl;
	file.seekp(0, ios_base::end);

	auto data = new string;
	int len = str.length();
	for(int i = 0; i < len; i++){
		*data += charMap.at(str[i]);
	}

	writeBinStringToFile(file, *data);
	
	file.close();
	delete data;
}

void Encoder::encode(){
	auto inputStr = getInputString();
	if (inputStr->length() == 0){
		return;
	}

	CharMap cm(*inputStr);
	auto cMap = cm.get();
	// for(auto i = cMap->begin(); i != cMap->end(); i++){
	// 	cout << i->first << " : " << i->second << endl;
	// }
	makeOutputFile(*cMap, *inputStr);
}

