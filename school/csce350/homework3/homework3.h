#include <iostream>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

// Creates an input file
void createInput(char * filename, int size);

// SelectionSort on the six input files
void selectionSort(int * data, int size, string filename);	

// BubbleSort on the six input files
void bubbleSort(int * data, int size, string filename);

// MergeSort on the six input files
void mergeSort(int * data, int size, string filename);

// MergeSort base method 
void mergeSort(int * a, int size);

// Mergesort sub method
void merge(int * b, int * c, int * a, int bSize, int cSize);

// QuickSort on the six input files
void quickSort(int * data, int size, const char * filename);

// Quicksort base method
void quickSort(int * a, int l, int r);

// Quicksort sub method
int partition(int * a, int l, int r);

// Sorts all input files
void sort(string filename);

int main();
