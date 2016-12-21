#pragma once
#include <string>
#include <map>
#include <vector>

using namespace std;

/// Character class

/**
 * Presents a simple character and its code
 */

class Character{
public:
	/// Default constructor
	Character(char _self, int _prob); 
	/// Character in ASCII
	char self;
	/// Character's probability
	int prob;
	/// Character's Fano code
	string code;
};

/// CharMap class

/**
 * Presents tools for creating CharMap,
 * which is a map, that binds the symbol and 
 * its binary code, obtained by Fano algorithm
 */

class CharMap{
private:
	/// charMap itself, a map, that binds characters and their Fano codes
	map<char, string>* self;
	map<char, int>* createProbmap(string &_inputString);
	vector<Character*>* createCharVector(map<char, int> &_probMap);
	void createBranch(int _begin, int _end, vector<Character*> &_vec);
	int findBranchingPoint(int _begin, int _end, vector<Character*> &_vec);
	int seqProbSum(int _begin, int _end, vector<Character*> &_vec);
public:
	map<char, string>* createFromText(string &_inputString);
	map<char, string>* get();

	void log();
};