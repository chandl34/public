#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <values.h>


int p, rank;
int keys = 0;
int low, high;
float bestcost; 
int bestroot;
int size;
float** cost = NULL;
int** root = NULL;
float* prob = NULL;
float* probSum = NULL;
int* contr = NULL;
int* offset = NULL;
MPI_Status status;


void init();
void master();
void slave();
void printRoot(int**, int, int);


int main(int argc, char *argv[]){

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	init();

	if(rank == 0)
		master();
	else
		slave();

	free(cost);
	free(root);
	free(probSum);
	free(prob);
	free(contr);
	free(offset);
}


void init(){
	if(rank == 0){
		// Collect values
		printf("Input number of keys:  ");	
		fflush(stdout);
		scanf("%d", &keys); 
	}
	MPI_Bcast(&keys, 1, MPI_INT, 0, MPI_COMM_WORLD);

	prob = (float*) malloc(keys*sizeof(float));
	probSum = (float*) malloc(keys*sizeof(float));

	if(rank == 0){
		printf("Input %i key values:  ", keys);
		fflush(stdout);
	
		for(int i = keys - 1; i >= 0; i--){	
			scanf("%f", &prob[i]);
			probSum[i] = prob[i];
			if(i != keys - 1)
				probSum[i] += probSum[i+1];	
		}
		printf("Collected all values\n");
		fflush(stdout);
	}
	MPI_Bcast(probSum, keys, MPI_FLOAT, 0, MPI_COMM_WORLD);

	int m = keys+1;
	root = (int**) malloc(m*m*sizeof(int));
	cost = (float**) malloc(m*m*sizeof(float));
	for(int i = 0; i < m; i++){
		root[i] = (int*) malloc(m*sizeof(int));
		cost[i] = (float*) malloc(m*sizeof(float));
	}
			
	// Determine size of each processes contribution
	contr = (int*) malloc(p*sizeof(int));
	offset = (int*) malloc(p*sizeof(int));
	contr[1] = keys/(p-1);
	offset[1] = 0;
	for(int i = 2; i < p; i++){
		contr[i] = contr[1];
		offset[i] = contr[i-1] + offset[i-1];			
	}
	contr[p-1] += keys%(p-1);
}


void master(){
	int count = 0;

	for(low = keys; low >= 0; low--){
		MPI_Bcast(&low, 1, MPI_INT, 0, MPI_COMM_WORLD);
		cost[low][low] = 0.0;
		root[low][low] = low;	
		MPI_Bcast(&cost[low][low], 1, MPI_FLOAT, 0, MPI_COMM_WORLD);	
		for(high = low+1; high <= keys; high++){
			MPI_Bcast(&high, 1, MPI_INT, 0, MPI_COMM_WORLD);			
			size = high - low - 1;
			bestcost = MAXFLOAT;
			MPI_Bcast(&bestcost, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
			for(int i = 1; size > 0; i++){
				count++;
				MPI_Send(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
				size -= contr[i];
			}
			printf("Waiting\n");
			fflush(stdout);
			while(count > 0){
				MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
				count--;
			}
			fflush(stdout);
			cost[low][high] = bestcost;
			root[low][high] = bestroot;
			MPI_Bcast(&cost[low][high], 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
		}
		printf("One key down\n");
		fflush(stdout);
	}

        printRoot(root, low, high);
	
	printf("Shutting down...\n");
	fflush(stdout);
	size = -1;
	for(int i = 1; i < p; i++)
		MPI_Send(&size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
}	

void slave(){
	while(1){
		MPI_Recv(&size, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		if(size == -1)
			break;
		if(size > contr[rank])
			size = contr[rank];
		float rcost;
		for(int r = low + offset[rank]; r < low + offset[rank] + size; r++){
			fflush(stdout);
			rcost = cost[low][r] + cost[r+1][high] + probSum[low];
			if(rcost < bestcost){
				bestcost = rcost;
				bestroot = r;
				MPI_Bcast(&bestcost, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
				MPI_Bcast(&bestroot, 1, MPI_INT, 0, MPI_COMM_WORLD);
			}
		}
                MPI_Send(&size, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
}

void printRoot(int** ro, int lo, int hi){
	printf("Root of tree spanning %d-%d is %d\n", lo, hi, ro[lo][hi+1]);
	fflush(stdout);
	if(lo < ro[lo][hi+1]-1)
		printRoot(ro, lo, ro[lo][hi+1]-1);
	if(ro[lo][hi+1] < hi-1)
		printRoot(ro, ro[lo][hi+1]+1, hi);
}
