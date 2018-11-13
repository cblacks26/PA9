#include <Count.h>
#include <Compare.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using std::cout;
using std::endl;
using std::ifstream;

// Print the usage message.
int Usage(){
  cout << "Usage: filename.txt filename.txt lower upper\n" << endl;
	return -1;
}
// Print the failed to read message
int Failed(const string str){
	cerr << "Unable to read input file " << str << endl;
	return -1;
}

int main(int argc, char* argv[]){
	
	if(argc != 5) return Usage();
	ifstream fstr(argv[2]);
	Exception ex;
	Compare cp;
	string str;
	double lower = atof(argv[3]);
	double upper = atof(argv[4]);
	fstr >> str;
	if(!fstr.fail()){
		ifstream istr(str);
		if(ex.read(istr)==false) return Failed(str);
		fstr >> str;
	}else{
		cerr << "Error with file containing filenames" << endl;
		return -1;
	}
	if(cp.addCompare(argv[1],ex)==false) return Failed(str);
	while(!fstr.fail()){
		if(cp.addCount(str,ex)==false) return Failed(str);
    fstr >> str;
	}
  string doc=cp.getDocumentMatch(lower,upper);
	if(doc.empty()){
		cerr << "No documents in reading level range" << endl;
    return -1;
	}else{
		cout << doc << endl;
	}
	return 0;
}