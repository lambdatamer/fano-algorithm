#include <iostream>
#include <clocale>

#include "main.hpp"
#include "encoder.hpp"
#include "decoder.hpp"

using namespace std;

/**
 * Processes user input
 */

int main(int argc, char* argv[]){

	if(argc < 2){
		printShortHelp();
	}else if(string(argv[1]) == "-h" 
		|| string(argv[1]) == "--help"){
		printHelp();
	}else if(argc > 2){
		string iFile(argv[2]);
		if(string(argv[1]) == "-e"){
			Encoder enc;
			if(argc > 4 && string(argv[3]) == "-o"){
				string oFile(argv[4]);
				enc.encode(iFile, oFile);
			}else{
				enc.encode(iFile, iFile);
			}
		}else if(string(argv[1]) == "-d"){
			Decoder dec;
			if(argc > 4 && string(argv[3]) == "-o"){
				string oFile(argv[4]);
				dec.decode(iFile, oFile);
			}else{
				dec.decode(iFile, iFile);
			}
		}else{
			printShortHelp();
		}
	}else{
		printShortHelp();
	}

	return 0;
}

/**
 * Prints full help
 */

void printHelp(){
	cout << "usage: fano <mode> <input> [-o <output>]" << endl;
	cout << "\n\tmode:\t-e\tEncode file" << endl;
	cout << "\t\t-d\tDecode file" << endl;
}

/**
 * Prints short help, without a parameters explanation
 */

void printShortHelp(){
	cout << "usage: fano <mode> <input> [-o <output>]" << endl;
}