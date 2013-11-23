#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
		
	clock_t t = clock()/1000;
	int rank, p, pValue, total;
	
	MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &p);		

		pValue = rank + 1;
		MPI_Reduce(&pValue, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
		if(rank == 0){
			printf("Total:  %i\nCalculated:  %i\n", total, p*(p+1)/2);
			fflush(stdout);
			printf("Process took %u milliseconds.\n", clock()/1000 - t);
			fflush(stdout);
		}
	MPI_Finalize();
	
	return 0;
}
