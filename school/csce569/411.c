#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv){
	clock_t t = clock()/1000;
	int rank, p;
	int max = 1000000;
	double iMax = 1.0/max;		
	double area;
	double ysum;
	double xi;
	
	MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &p);	
	
		int size = max/p;
		int offset = size*rank;
		int cap = offset + size;
		
		ysum = 0.0;
		for(int i = offset; i < cap; i++){
			xi = iMax*((double)i + 0.5);	
			ysum += 4.0 / (1.0 + xi*xi);
		}	
						
//              printf("Process %i found %i combinations.\n", rank, pTotal);
//              fflush(stdout);

		MPI_Reduce(&ysum, &area, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);			
	
		if(rank == 0){
			area *= iMax;
			printf("Pi:  %13.11f\n", area);
			fflush(stdout);
			printf("Process took %i milliseconds.\n", clock()/1000 - t);
			fflush(stdout);                  
		}
	MPI_Finalize();
	
	return 0;
}
