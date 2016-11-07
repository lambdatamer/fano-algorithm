#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "charmap.hpp"

using namespace std;

CharMap::CharMap(std::string &inputStr){
	map<char, int> probMap;
	createProbMap(probMap, inputStr);
	vector<Character*> vec;
	createCharVector(probMap, vec);
	self = createCharMap(vec);
	for_each(vec.begin(), vec.end(), [] (Character* cur){
		delete cur;
	});
}

void CharMap::createProbMap(map<char,int> &probMap, string &str){
	int strLength = str.length();
	char cur;
	for(int i = 0; i < strLength; i++){
		cur = str[i];
		if(probMap.count(cur)){
			probMap.at(cur)++;
		}else{
			probMap.insert(pair<char,int>(cur, 1));
		}
	}
}

bool characterCompare(Character* first, Character* second){
	return first->prob < second->prob;
}

void CharMap::createCharVector(map<char, int> &probMap, vector<Character*> &vec){
	for(auto character: probMap){
		auto current = new Character(character.first, character.second);
		vec.push_back(current);
	}
	sort(vec.rbegin(), vec.rend(), characterCompare);

}

map<char, string>* CharMap::createCharMap(vector<Character*> &vec){
	createBranch(0, vec.size(), vec);

	auto charMap = new map<char, string>;
	for(int i = 0; i < vec.size(); i++){
		charMap->insert(pair<char, string>(vec[i]->self, vec[i]->code));
	}

	return charMap;
}

void CharMap::createBranch(int begin, int end, vector<Character*> &vec){
	if(end == begin){
		return;
	}

	int point = findBranchPoint(begin, end, vec);

	for(int i = begin; i < point; i++){
		vec[i]->code += "0";
	}
	for(int i = point; i < end; i++){
		vec[i]->code += "1";
	}

	if(begin + 1 < point){
		createBranch(begin, point, vec);
	}
	if(point + 1 < end){
		createBranch(point, end, vec);
	}
}

int CharMap::findBranchPoint(int begin, int end, vector<Character*> &vec){

	vector<int> differences;
	int tmp;
	for(int i = begin; i < end; i++){
		tmp = seqProbSum(begin, i, vec) - seqProbSum(i, end, vec);
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

	return begin + index;
}

int CharMap::seqProbSum(int begin, int end, vector<Character*> &vec){
	int sum = 0;
	for(int i = begin; i < end; i++){
		sum += vec[i]->prob;
	}

	return sum;
}

map<char, string>* CharMap::get(){
	return self;
}

/*
	Character
*/

Character::Character(char _self, int _prob){
	self = _self;
	prob = _prob;
	code = "";
}
