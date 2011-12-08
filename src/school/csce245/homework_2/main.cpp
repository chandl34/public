// Jonathan Chandler
// main.cpp - source file

#include <iostream>
#include "homework2.h"
using namespace std;

int main(){
	TwoDArrayPtr array;
	int i;
    	while(true){
		array = Readinput();  	
		cout << "The mininmum value is:  " << Min(array) << "\n";
		cout << "The maximum value is:  "  << Max(array) << "\n\n";	 
		Destroy(array);
	}
	return 0;
}
