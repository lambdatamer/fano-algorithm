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
	std::vector<Character*>* createCharVector(std::map<char, int> &probMap);
	std::map<char, std::string>* createCharMap(std::vector<Character*> &array);
	void createBranch(int begin, int end, std::vector<Character*> &array);
	int findBranchPoint(int begin, int end, std::vector<Character*> &array);
	int seqProbSum(int begin, int end, std::vector<Character*> &array);

public:
	void encode();
	// createEncodedFile();

};



