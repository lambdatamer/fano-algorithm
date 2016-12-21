#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "lib.hpp"
#include "decoder.hpp"

using namespace std;

/**
 * Prepairing the file for decoding.
 * Expects .fano file.
 * @return file opened in binary mode
 */
ifstream* Decoder::getInputFile(string &_fileName){
	ifstream* file;

	try{
		if(_fileName.length() > 6 && _fileName.substr(_fileName.length() - 5, 5) != ".fano"){
			throw 1;
		}

		file = new ifstream(_fileName);
		
		if(!file->is_open()){
			throw 2;
		}
	}catch(int e){
		switch (e){
			case 1:
				cout << "Expected encoded .fano file." << endl;
				exit(1);
			case 2:
				cout << "Error while opening file." << endl;
				exit(1);
		}
	}

	return file;
}

/**
 * Read int value from the file
 * @param _file file in binary mode
 * @return int value
 */
int Decoder::getDWordFromFile(ifstream &_file){
	char buf[4];
	_file.read(buf, 4);
	int* DWord = reinterpret_cast<int*>(buf);
	return *DWord;
}

/** Decodes file
 */
void Decoder::decode(string _fileName, string _outputFileName){
	ifstream &file = *(getInputFile(_fileName));
	cout << "Decoding..." << endl;
	disassembly(file);
	decodeText(file);
	makeOutputFile(_outputFileName);
	cout << "Done." << endl;
}

/** Processes header
 * reads charmap info, creating decode charMap
 * @param _file file in binary mode
 */
void Decoder::disassembly(ifstream &_file){
	charMapSize = getDWordFromFile(_file);
	bitMapLength = getDWordFromFile(_file);
	dataPointer = getDWordFromFile (_file);
	getDWordFromFile(_file);
	createCodeLengths(_file);
	createCharMap(_file);
}

/** Reads codeLengths 
 * map required for charMap from a header of the file
 * @param _file file in binary mode
 */
void Decoder::createCodeLengths(ifstream &_file){
	char character, length;
	int lengthCast;
	codeLengths = new map<char,int>;
	for(int i = charMapSize; i > 0; i--){
		character = _file.get();
		length = _file.get();
		lengthCast = static_cast<int>(length);
		codeLengths->insert(pair<char, int>(character, lengthCast));
	}
}

/** Makes a Charmap from the header
 * @param _file file in binary mode
 */
void Decoder::createCharMap(ifstream &_file){
	string bitMap;
	char buf;

	for(int counter = 0; counter < bitMapLength; counter += 8){
		buf = _file.get();
		bitMap += charToBin(buf);
	}

	charMap = new map<char, string>;
	string code;
	int ptr = 0;

	for(auto item : *codeLengths){
		code = bitMap.substr(ptr, item.second);
		ptr += item.second;
		charMap->insert(pair<char, string>(item.first, code));
	}
}

/** Decodes text using charMap
 * @param _file file in binary mode
 */
void Decoder::decodeText(ifstream &_file){
	string &encoded = *(new string);
	char tmp;

	while(true){
		tmp = _file.get();
		if(_file.eof()) break;
		encoded += charToBin(tmp);
	};

	string buf;
	auto charMapFlipped = flip_map(*charMap);

	for(int i = 0; i < encoded.length(); i++){
		buf += encoded[i];
		if(charMapFlipped.find(buf) != charMapFlipped.end()){
			decodedText += charMapFlipped.at(buf);
			buf = "";
		}
	}
}
/** Makes output file
 */
void Decoder::makeOutputFile(string &_fileName){
	ofstream file;
	file.open(_fileName, ios_base::binary);
	file << decodedText;
	file.close();
}
