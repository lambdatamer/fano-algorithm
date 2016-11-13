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
	void makeOutputFile(map<char,string> &_charMap, string &_inputString, string &_fileName);
	void writeDWordToFile(ofstream &_file, int _dword);
	int writeBinStringToFile(ofstream &_file, string &_inputString);
public:
	void encode(string &_fileName, string &_outputFileName);
};
