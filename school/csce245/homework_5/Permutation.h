// Jonathan Chandler
// Permutation.h

#ifndef PERMUTATION_H_
#define PERMUTATION_H_

#include <fstream>
#include <iostream>
#include <cmath>	// For log10()
#include "nString.h"
using namespace std;

class Permutation{
	public:
		Permutation(char * inputFile);
		~Permutation();
	private:
		void FindMax();       // Finds largest number in permutations
		void FindLength();    // Finds number of permutations
		void CreatePermutationsArray();
		void ComputeMatrix();
		void PrintMatrix();
		void Reset();  // Resets position in input file

		int max, length;
		int ** permutation; // Permutation chain
		int ** bp;   // Break point values
		
		nString nextLine;
		ifstream in;
};
#endif
