#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "encoder.hpp"
#include "lib.hpp"

using namespace std;

/*
 *	Encoder
 */

Encoder::Encoder(){
}

Encoder::~Encoder(){
}

string* Encoder::getInputString(){
	ifstream file;
	file.open("files//input.txt", ios_base::in);
	
	file.seekg(0, ios_base::end);
	int length = file.tellg();
	file.seekg(0, ios_base::beg);

	char *buffer = new char[length];

	file.read(buffer, length);
	file.close();

	delete buffer;
	return new string(buffer, length);
}

void Encoder::createProbMap(map<char,int> &probMap, std::string &str){
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

vector<Character*>* Encoder::createCharVector(map<char, int> &probMap){
	auto vec = new vector<Character*>;
	for(auto character: probMap){
		auto current = new Character(character.first, character.second);
		vec->push_back(current);
	}
	sort(vec->rbegin(), vec->rend(), characterCompare);
	return vec;
}

void Encoder::encode(){
	auto inputString = getInputString();
	map<char, int> probMap;
	createProbMap(probMap, *inputString);
	// for_each(probMap.begin(), probMap.end(), [] (pair<char, int> a){
	// 	cout << a.first << " : " << a.second << endl;
	// });
	auto charVector = createCharVector(probMap);
	// for_each(charVector->begin(), charVector->end(), [] (Character* c){
	// 	cout << c->self << ":" << c->prob << endl;
	// });

}

Character::Character(char _self, int _prob){
	self = _self;
	prob = _prob;
	code = "";
}