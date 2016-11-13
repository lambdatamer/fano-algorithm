#include <iostream>

#include "encoder.hpp"
#include "decoder.hpp"

using namespace std;

//TODO normal main func
//improve filenames in encoder


int main(int argc, char* argv[]){
	if(argc == 5){
		if(string(argv[1]) == "-e"){
			Encoder enc;
			cout << "Encoding file..." << endl;
			enc.encode(argv[2]);
		}else if(string(argv[1]) == "-d"){
			Decoder dec;
			cout << "Decoding file..." << endl;
			dec.decode(string(argv[2]), string(argv[4]));
		}
		cout << "Done." << endl;
	}else if(argc > 1 && (string(argv[1]) == "--help" || string(argv[1]) == "-h")){
		cout << "usage: fano [--help] [<mode> <ifile> [-o <ofile>]]" << endl;
		cout << "\n\t<mode>:";
		cout << " '-e\': Encode file.\n\t\t'-d': Decode file." << endl;
	}else{
		cout << "usage: fano [--help] [<mode> <ifile> [-o <ofile>]]" << endl;
	}
	return 0;
}