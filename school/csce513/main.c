/*	Jonathan Chandler
 *	CSCE 513
 *	Matrix Multiplication
 *
 *	How does this work?
 *	  -Rows of matrix A are split evenly between 8 threads
 *    -Each thread does matrix multiplication on the rows it is assigned
 *
 *	  -The bounds on matrix B are swapped to simplify multiplication 
 *    -Later this is fixed by printing the matrix as YxX instead of XxY
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <iostream>
#include <algorithm>

using namespace std;


//const int MAX_BOUND = 10;	// matrix bounds
//const int MAX_VALUE = 10;	// matrix values
//const int MAX_THREADS = 8;

int** bound;
int*** matrix;
int innerBound;

enum{X, Y};
enum{A, B, C};


void setup(int maxBound, int maxValue){
	int i, j, k;

	// Setting up RNG
	srand(time(NULL));

	// Randomize matrix bounds
	bound = new int*[3];
	bound[A] = new int[2];
	bound[B] = new int[2];
	bound[C] = new int[2];

	innerBound = rand()%maxBound + 1;

	bound[A][X] = rand()%maxBound + 1;
	bound[A][Y] = innerBound;

	bound[B][X] = rand()%maxBound + 1;
	bound[B][Y] = innerBound;			// Swapped

	bound[C][X] = bound[A][X];
	bound[C][Y] = bound[B][X];			// Swapped, would normally be Y

	printf("%ix%i*%ix%i = %ix%i\n\n", bound[0][X], bound[0][Y], bound[1][Y], bound[1][X], bound[2][X], bound[2][Y]);

	// Randomize matrix A and B
	matrix = new int**[3];
	for(i = 0; i < 2; i++){
		matrix[i] = new int*[bound[i][X]];
		for(j = 0; j < bound[i][X]; j++){
			matrix[i][j] = new int[bound[i][Y]];
			for(k = 0; k < bound[i][Y]; k++)
				matrix[i][j][k] = rand()%(maxValue+1);
		}
	}

	// Create a blank matrix C
	matrix[2] = new int*[bound[2][X]];
	for(j = 0; j < bound[2][X]; j++)
		matrix[2][j] = new int[bound[2][Y]];
}

void* multiplySub(void* r){
	int* range = (int*)r;
	int i, j, k;

	for(i = range[0]; i < range[1]; i++){							// Vertical depth in C
		for(j = 0; j < bound[C][Y]; j++){							// Horizontal breadth in C
			matrix[C][i][j] = 0;
			for(k = 0; k < innerBound; k++)
				matrix[C][i][j] += matrix[A][i][k]*matrix[B][j][k];
		}
	}
	pthread_exit(NULL);
}

void multiply(int maxThreads){
	int i;

	double work = bound[A][X];
	int share = ceil(work/maxThreads);

	int threadCount = min(maxThreads, (int)work);
	int** range = new int*[threadCount];
	pthread_t thread[threadCount];
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	void* status;

	// Distribute work
	for(i = 0; i < threadCount; i++){
		range[i] = new int[2];
		range[i][0] = i*share;
		range[i][1] = min((i+1)*share, (int)work);
		if(pthread_create(&thread[i], &attr, multiplySub, range[i]))
			printf("Error creating thread %i\n", i);
	}

	// Link up, link up
	pthread_attr_destroy(&attr);
	for(i = 0; i < threadCount; i++){
		if(pthread_join(thread[i], &status))
		   printf("Error joining thread %i\n", i);
	}

	// Clean-up
	for(i = 0; i < threadCount; i++)
		delete [] range[i];
	delete [] range;
}

void printMatrix(int** matrix, int* bound, bool flip){
	int i, j;
	if(!flip){
		for(i = 0; i < bound[X]; i++){
			for(j = 0; j < bound[Y]; j++)
				printf("%i ", matrix[i][j]);
			printf("\n");
		}
	}
	else{
		for(j = 0; j < bound[Y]; j++){
			for(i = 0; i < bound[X]; i++)
				printf("%i ", matrix[i][j]);
			printf("\n");
		}
	}
	printf("\n");
}

void printAnswer(){
	for(int i = 0; i < 3; i++){
		printf("Matrix %i\n", i+1);
		printMatrix(matrix[i], bound[i], i%2);
	}
}

void clearData(){
	int i, j;

	// Clean-up
	for(i = 0; i < 3; i++){
		for(j = 0; j < bound[i][X]; j++)
			delete [] matrix[i][j];
		delete [] matrix[i];
		delete [] bound[i];
	}
	delete [] matrix;
	delete [] bound;
}


int main (int argc, char * const argv[]) {
	int maxBound, maxValue, maxThreads;
	printf("Please enter the max bound for a matrix:");
	cin >> maxBound;
	printf("Please enter the max matrix value:");
	cin >> maxValue;
	printf("Please enter the max threads to be used:");
	cin >> maxThreads;
	printf("\n");

	setup(maxBound, maxValue);
	multiply(maxThreads);
	printAnswer();
	clearData();

    return 0;
}
