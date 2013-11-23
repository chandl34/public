// Jonathan Chandler
// main.C

#include "Permutation.h"
#include "nString.h"

int main(int argc, char ** argv){
	if(argc < 2){
		cout << "Incorrect input format.  Should be:  project5.exe input" << endl;
		exit(-1);
	}
	Permutation *perm = new Permutation(argv[1]);
	delete perm;
	return 0;
}
