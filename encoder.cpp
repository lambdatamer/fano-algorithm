#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <algorithm>
#include <bitset>

#include "encoder.hpp"
#include "charmap.hpp"
#include "lib.hpp"

using namespace std;

//Simply opens the file.
//The file must be txt.
ifstream* Encoder::openFile(string &_fileName){
	ifstream* file;
	try{
		if(_fileName.substr(_fileName.length() - 4, 4) != ".txt"){
			throw 1;
		}
		
		file = new ifstream(_fileName);
		
		if(!file->is_open()){
			throw 2;
		}

	}catch(int e){
		switch (e){
			case 1:
				cout << "The program works only with txt files." << endl;
				exit(1);
			case 2:
				cout << "Error while opening file." << endl;
				exit(1);
		}
	}

	return file;
}

//Return a string readed from _file
string* Encoder::createStringFromInputFile(ifstream *_file){
	ifstream &file = *_file;
	char tmp = file.get();
	auto inputString = new string;

	while(true){
		tmp = file.get();
		if(file.eof()) break;
		*inputString += tmp;
	};

	file.close();
	
	return inputString;
}

//Creates encoded file
void Encoder::encode(char *_fileName){
	string fileName(_fileName);

	auto file = openFile(fileName); 
	auto inputString = createStringFromInputFile(file);

	CharMap charmap(*inputString);

	//DONT FORGET DELETE INPUTSTRING AFTER ENCODING
}















// OLD

// Read input file, and return its content as a string
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

//Writes int value to file as four chars
void Encoder::writeDWordToFile(ofstream &file, int dword){
	int* ptr = &dword;

	char* c = reinterpret_cast<char*>(ptr);
	
	file.write(c, 4);
} 

//Writes the string containing the '0's and '1's in the file
//Returns amount of the bytes had been written
int Encoder::writeBinStringToFile(ofstream &file, string &str){
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

//Creates and writes the header and encoded string in the file
void Encoder::makeOutputFile(map<char,string> &charMap, string &str){
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

//Creates encoded file
// void Encoder::encode(){
// 	auto inputStr = getInputString();
// 	if (inputStr->length() == 0){
// 		return;
// 	}

// 	CharMap cm(*inputStr);
// 	auto cMap = cm.get();
// 	// for(auto i = cMap->begin(); i != cMap->end(); i++){
// 	// 	cout << i->first << " : " << i->second << endl;
// 	// }
// 	makeOutputFile(*cMap, *inputStr);
// }

