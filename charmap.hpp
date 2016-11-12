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
	string code;
};

class CharMap{
private:
	map<char, string>* self;

	map<char, int>* createProbmap(string &_inputString);
	vector<Character*>* createCharVector(map<char, int> &_probMap);
	map<char, string>* createCharmap(vector<Character*> &_charVector);
	void createBranch(int _begin, int _end, vector<Character*> &_vec);
	int findBranchingPoint(int _begin, int _end, vector<Character*> &_vec);
	int seqProbSum(int _begin, int _end, vector<Character*> &_vec);
public:
	CharMap(string &_inputString);
	map<char, string>* get();
	void log();
};