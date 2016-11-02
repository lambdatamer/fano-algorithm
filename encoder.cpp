#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "encoder.hpp"
#include "lib.hpp"

using namespace std;



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

map<char, string>* Encoder::createCharMap(vector<Character*> &array){
	log("begin charmap");
	createBranch(0, array.size(), array);

	auto charMap = new map<char, string>;
	for(int i = 0; i < array.size(); i++){
		charMap->insert(pair<char, string>(array[i]->self, array[i]->code));
	}

	return charMap;
}

void Encoder::createBranch(int begin, int end, vector<Character*> &array){
	if(end == begin){
		return;
	}
	cout << "new branch from " << begin << " to " << end << endl;

	int point = findBranchPoint(begin, end, array);
	for(int i = begin; i < point; i++){
		array[i]->code += "0";
	}
	for(int i = point; i < end; i++){
		array[i]->code += "1";
	}
	cout << "branch: from " << begin << " to " << end << endl;
	// cin.get();
	if(begin + 1 >= point){
		createBranch(begin, point, array);
	}
	if(point + 1 >= end){
		createBranch(point, end, array);
	}
}

int Encoder::findBranchPoint(int begin, int end, vector<Character*> &array){
	if(end == begin + 2){
		return begin + 1;
	}

	int i = begin,
		difference = 0,
		tmp = array[begin]->prob - seqProbSum(0, end, array);

		if(tmp < 0){
			tmp = -tmp; 
		}
	
	do{
		i++;
		difference = tmp;
		tmp = seqProbSum(begin, i, array) - seqProbSum(i, end, array);
	
		if(tmp < 0){
			tmp = -tmp; 
		}
		
		cout << "diff: " << difference << " at " << i << endl;
	}while(tmp < difference);

	cout << --i << endl;
	return i;
}

int Encoder::seqProbSum(int begin, int end, vector<Character*> &array){
	int sum = 0;
	for(int i = begin; i < end; i++){
		sum += array[i]->prob;
	}
	return sum;
}

void Encoder::encode(){
	auto inputString = getInputString();
	if (inputString->length() == 0){
		return;
	}
	map<char, int> probMap;
	createProbMap(probMap, *inputString);
	// for_each(probMap.begin(), probMap.end(), [] (pair<char, int> a){
	// 	cout << a.first << " : " << a.second << endl;
	// });
	auto charVector = createCharVector(probMap);
	// for_each(charVector->begin(), charVector->end(), [] (Character* c){
	// 	cout << c->self << ":" << c->prob << endl;
	// });
	auto charMap = createCharMap(*charVector);
	for_each(charVector->begin(), charVector->end(), [] (Character* c){
		cout << "\'" << c->self << "\'" << ":" << c->prob << " = " << c->code << endl;
	});
}

Character::Character(char _self, int _prob){
	self = _self;
	prob = _prob;
	code = "";
}

