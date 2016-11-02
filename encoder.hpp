#pragma once
#include <string>
#include <map>
#include <vector>

class Character{
public:
	Character(char _self, int _prob);
	char self;
	int prob;
	std::string code;
};

class Encoder{
private:
	std::map<char,int> *probMap;
	std::string* getInputString();
	void createProbMap(std::map<char,int> &probMap, std::string &str);
	void createCharMap(std::map<int,char> &probMap);
	std::vector<Character*>* createCharVector(std::map<char, int> &probMap);
public:
	Encoder();
	~Encoder();
	void encode();
	// createEncodedFile();

};



