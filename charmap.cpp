#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "charmap.hpp"

using namespace std;

/*
	Character
*/

Character::Character(char _self, int _prob){
	self = _self;
	prob = _prob;
	code = "";
}

/*
	CharMap
*/

CharMap::CharMap(string &_inputString){
	if(_inputString.length()!= 0){
		auto probMap = createProbmap(_inputString);
		auto charVector = createCharVector(*probMap);
		delete probMap;
		self = createCharmap(*charVector);
		delete charVector;
	}
}

//Creates probMap sorted by alphabet
map<char, int>* CharMap::createProbmap(string &_inputString){
	int length = _inputString.length();
	auto probMap = new map<char, int>;
	char cur;

	for(int i = 0; i < length; i++){
		cur = _inputString[i];
		if(probMap->count(cur)){
			probMap->at(cur)++;
		}else{
			probMap->insert(pair<char,int>(cur, 1));
		}
	}

	return probMap;
}

//The compare function for sort in createCharVector
bool characterCompare(Character* _first, Character* _second){
	return _first->prob < _second->prob;
}

//Creates the charVector and sort it by probability
vector<Character*>* CharMap::createCharVector(map<char, int> &_probMap){
	auto charVector = new vector<Character*>;

	for(auto character: _probMap){
		auto current = new Character(character.first, character.second);
		charVector->push_back(current);
	}

	sort(charVector->rbegin(), charVector->rend(), characterCompare);
	
	return charVector;
}

//Creates the complete charmap sorted by alphabet
map<char, string>* CharMap::createCharmap(vector<Character*> &_charVector){
	createBranch(0, _charVector.size(), _charVector);

	auto charMap = new map<char, string>;
	for(int i = 0; i < _charVector.size(); i++){
		charMap->insert(
			pair<char, string>(
				_charVector[i]->self, 
				_charVector[i]->code
			)
		);
	}

	return charMap;
}

//Recursively creates a binary tree 
void CharMap::createBranch(int _begin, int _end, vector<Character*> &_vec){
	if(_end == _begin){
		return;
	}

	int point = findSplitPoint(_begin, _end, _vec);

	for(int i = _begin; i < point; i++){
		_vec[i]->code += "0";
	}
	for(int i = point; i < _end; i++){
		_vec[i]->code += "1";
	}

	if(_begin + 1 < point){
		createBranch(_begin, point, _vec);
	}
	if(point + 1 < _end){
		createBranch(point, _end, _vec);
	}
}

//finds point between two branches with related probability
int CharMap::findSplitPoint(int _begin, int _end, vector<Character*> &_vec){
	vector<int> differences;
	int tmp;
	for(int i = _begin; i < _end; i++){
		tmp = seqProbSum(_begin, i, _vec) - seqProbSum(i, _end, _vec);
		if(tmp < 0){
			tmp = -tmp;
		}
		differences.push_back(tmp);
	}
	
	int difference = differences[0],
			index = 0;
	for(int i = 1; i < differences.size(); i++){
		if(differences[i] < difference){
			difference = differences[i];
			index = i;
		}
	}

	return _begin + index;
}

//Returns sum of probabilities of chars between _begin_ and _end_ in _vec_.
int CharMap::seqProbSum(int _begin, int _end, vector<Character*> &_vec){
	int sum = 0;
	for(int i = _begin; i < _end; i++){
		sum += _vec[i]->prob;
	}

	return sum;
}

//Simply returns charmap
map<char, string>* CharMap::get(){
	return self;
}

//Prints charmap to console
void CharMap::log(){
	for(auto character: *self){
		cout << "'" << character.first << "' : " << character.second << endl;
	}
}