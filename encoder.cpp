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

// Simply opens the file.
// The argument be text file with txt ext.
ifstream* Encoder::openFile(string &_fileName){
	ifstream* file = new ifstream;
	file->open(_fileName, ios_base::binary);
	if(!file->is_open()){	
		cout << "Error while opening file." << endl;
		exit(1);
	}


	return file;
}

// Return a string readed from _file
string* Encoder::createStringFromInputFile(ifstream *_file){
	ifstream &file = *_file;
	char tmp;
	auto inputString = new string;

	while(true){
		tmp = file.get();
		if(file.eof()) break;
		*inputString += tmp;
	};

	file.close();

	return inputString;
}

// Creates encoded file
void Encoder::encode(string &_fileName, string &_outputFileName){
	string fileName(_fileName);

	auto file = openFile(fileName);
	auto inputString = createStringFromInputFile(file);
	cout << "Encoding..." << endl;
	CharMap charmap;
	makeOutputFile(*(charmap.createFromText(*inputString)), *inputString, _outputFileName);
	cout << "Done." << endl;
	delete inputString;
}

// Creates and writes the header and encoded string in the file
void Encoder::makeOutputFile(map<char,string> &_charMap, string &_inputString, string &_fileName){

	if(!(_fileName.substr(_fileName.length() - 5, 5) == ".fano")){
		_fileName += ".fano"; 
	}

	ofstream file;
	file.open(_fileName, ios_base::binary);

	writeDWordToFile(file, _charMap.size());

	file.seekp(16, ios_base::beg);

	string bitMap;
	for (auto i = _charMap.begin(); i != _charMap.end(); i++){
		file << i->first << static_cast<char>(i->second.length());
		bitMap += i->second;
	}

	file.seekp(4, ios_base::beg);
	writeDWordToFile(file, bitMap.length());

	file.seekp(0, ios_base::end);
	int bitMapLength = writeBinStringToFile(file, bitMap);

	file.seekp(8, ios_base::beg);
	int dataPtr = (4*4 + _charMap.size() * 2 + bitMapLength);
	writeDWordToFile(file, dataPtr);
	file.seekp(0, ios_base::end);

	auto data = new string;
	int len = _inputString.length();
	for(int i = 0; i < len; i++){
		*data += _charMap.at(_inputString[i]);
	}

	writeBinStringToFile(file, *data);

	file.close();
	delete data;
}

// Writes int value binary to the file
void Encoder::writeDWordToFile(ofstream &_file, int _dword){
	int* ptr = &_dword;

	char* c = reinterpret_cast<char*>(ptr);

	_file.write(c, 4);
} 

// Writes the string containing the '0's and '1's to the file
// Returns amount of the bytes had been written
int Encoder::writeBinStringToFile(ofstream &_file, string &_inputString){
	int counter = 0;
	int len = _inputString.length();
	string buf;
	bitset<8> byte;
	auto bytePtr = &byte;
	char* c = reinterpret_cast<char*>(bytePtr);

	for(int i = 0; i < len ; i+=8){
		byte = byte.reset();	
		buf = _inputString.substr(i, 8);
		for(int j = 0; j < 8; j++){
			if(j > buf.length()) break;
			if(buf[j] == '1'){
				byte[7 - j] = 1;
			}
		}
		_file << *c;
	}
	return counter;
}
