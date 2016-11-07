#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

class Character{
public:
	Character(char _self, int _prob);
	char self;
	int prob;
	std::string code;
};

class CharMap{
private:
	map<char, string>* self;

	void createProbMap(map<char,int> &probMap, string &str);
	void createCharVector(map<char, int> &probMap, vector<Character*> &vec);
	map<char, string>* createCharMap(vector<Character*> &vec);
	void createBranch(int begin, int end, vector<Character*> &vec);
	int findBranchPoint(int begin, int end, vector<Character*> &vec);
	int seqProbSum(int begin, int end, vector<Character*> &vec);

public:
	CharMap(string &inputStr);
	map<char, string>* get();
};