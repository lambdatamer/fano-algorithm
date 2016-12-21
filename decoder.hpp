#pragma once
#include <iostream>
#include <string>
#include <map>

using namespace std;

/// Decoder class

class Decoder{
private:
	//File header
	/// charMap length in a header
	int charMapSize;
	/// bitMap length in a header
	int bitMapLength;
	/// position of encoded data
	int dataPointer;
	/// information about symbols code lengths 
	map<char, int>* codeLengths;
	/// decoding charmap
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
