#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Decoder{
private:
	// Header
	int charMapSize;
	int bitMapLength;
	int dataPointer;
	map<char, int>* codeLengths;
	map<char, string>* charMap;
	string decodedText;

	//Methods
	ifstream* getInputFile(string &_fileName);
	int getDWordFromFile(ifstream &_file);
	void disassembly(ifstream &_file);
	void createCodeLengths(ifstream &_file);
	void createCharMap(ifstream &_file);
	void decodeText(ifstream &_file);
	void makeOutputFile(string &_fileName);
public:
	void decode(string _fileName, string _outputFileName);
};
