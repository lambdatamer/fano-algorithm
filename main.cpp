#include <iostream>
#include "encoder.hpp"

using namespace std;

int main(int argc, char* argv[]){
	Encoder enc;
	if(argc == 3){
		if(string(argv[1]) == "-e"){
			cout << "Encoding file..." << endl;
			enc.encode(argv[2]);
			cout << "Done." << endl;
		}else if(string(argv[1]) == "-d"){
			cout << "decode" << endl;
		}
	}else if(argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")){
		cout << "usage: fano [--help] [<mode> <ifile> [-o <ofile>]]" << endl;
		cout << "\n\t<mode>:";
		cout << " '-e\': Encode file.\n\t\t'-d': Decode file." << endl;
	}else{
		cout << "usage: fano [--help] [<mode> <ifile> [-o <ofile>]]" << endl;
	}
	return 0;
}