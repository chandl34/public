#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int rank, p;
long n, count, total, size;
double x, y, z;

int main(int argc, char* argv[]){

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	n = atoi(argv[1]);	
	size = n/p;


	if(rank == p-1)
		size += n%p;

	srandom(time(NULL));	
	unsigned short seed[3];
	seed[0] = random()%10000;
	seed[1] = random()%10000;
	seed[2] = random()%10000;

	count = 0;
	for(int i = 0; i < size; i++){
		x = erand48(seed);
		x -= (int)x;
		x += 4;
		y = erand48(seed);
		y -= (int)y;
		y += 3;
		z = erand48(seed);
		z -= (int)z;
		z += 7;
		if(z <= x+y)
			count++;	
	}
	MPI_Reduce(&count, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	if(rank == 0){
		printf("Final value:  %1.10f\n", total/(double)n);
		fflush(stdout);
	}
	MPI_Finalize();
	return 0;
}
