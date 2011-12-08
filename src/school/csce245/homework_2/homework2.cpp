// Jonathan Chandler
// homework2.cpp - source file

#include <iostream>
#include "homework2.h"
using namespace std;

int length;

TwoDArrayPtr Readinput(){
	cout << "Input the dimension of the sides:  ";
	cin >> length;
	cout << "Input "<< (length*length) << " values:  ";
	
	// Creating first dimension of the array
	IntArrayPtr *col = new IntArrayPtr[length];
	int i, j;
	// Creating second dimension of the array
	for(i = 0; i < length; i++){
		col[i] = new int[length];	
	}
	// Taking array input
	for(i = 0; i < length; i++){
		for(j = 0; j < length; j++){
			cin >> col[i][j];	
		}
	}
	// Printing array contents
	for(i = 0; i < length; i++){
		for(j = 0; j < length; j++){
			cout << col[i][j] << " ";	
		}
		cout << endl;
	}	
	return col;
}

// Return minimum value of the array
int Min(TwoDArrayPtr array){
	int i, j;
	int min = array[0][0];
	for(i = 0; i < length; i++){
		for(j = 0; j < length; j++){
			if(array[i][j] < min)
				min = array[i][j];	
		}
	}	
	return min;
}

// Return maximum value of the array
int Max(TwoDArrayPtr array){
	int i, j;
	int max = array[0][0];
	for(i = 0; i < length; i++){
		for(j = 0; j < length; j++){
			if(array[i][j] > max)
				max = array[i][j];	
		}
	}	
	return max;
}

// Delete array
void Destroy(TwoDArrayPtr array){             
	int i;
	for(i = 0; i < length; i++){
        	delete[] array[i];
        }
        delete[] array;
}
