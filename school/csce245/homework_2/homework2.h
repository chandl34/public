// Jonathan Chandler
// homework2.h - header file

#include <iostream>
using namespace std;

typedef int* IntArrayPtr;  // int*
typedef IntArrayPtr* TwoDArrayPtr;  // int**

TwoDArrayPtr Readinput();
// Requires user input (int) to create an (input X input) array
// Requires user to input (int) all values of the array
// Inputting a non-int will crash the program or cause an infinite loop
// Returns the array

int Min(TwoDArrayPtr array);
// Returns the minimum value in a two-dimensional array

int Max(TwoDArrayPtr array);
// Returns the minimum value in a two-dimensional array

void Destroy(TwoDArrayPtr array);
// Deletes the array from memory
