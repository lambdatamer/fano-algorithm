#include <iostream>
#include "encoder.hpp"

using namespace std;

int main(int argc, char* argv[]){
	Encoder enc;
	if(argc < 2){
		cout << "help" << endl;
	}else{
		enc.encode(argv[1]);
	}
	return 0;
}