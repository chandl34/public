#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

int main(){
	srandom(time(0));
	ofstream out;
	out.open("input.txt");
	int perm, num, arraySize;
	cout << "Input number of permutations:  ";
	cin >> perm;
	cout << "Input number of integers:  ";
	cin >> arraySize;
	int temp = arraySize;
	
	int *spot = new int[arraySize];
	int j;
	for(int i = 0; i < perm; i++){
		out << ">S" << i << endl;
		arraySize = temp;
		for(j = 0; j < arraySize; j++)
			spot[j] = j+1;
		while(arraySize > 0){
		
		// Finding a random number
		j = random()%arraySize;
		// Printing the person at that random number
		out << spot[j] << " ";
		// Replacing the person to be removed with the end
		spot[j] = spot[arraySize-1];
		arraySize--;
		}
		out << endl;
	}
	


}
