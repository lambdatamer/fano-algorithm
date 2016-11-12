#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class Encoder{
private:
	ifstream* openFile(string &_fileName);
	string* createStringFromInputFile(ifstream *_file);
	//Old
	string* getInputString();
	void writeDWordToFile(ofstream &file, int dword);
	int writeBinStringToFile(ofstream &file, string &str);
	void makeOutputFile(map<char,string> &charMap, string &str);
public:
	void encode(char *_fileName);
	//Old
	// void encode();
};



