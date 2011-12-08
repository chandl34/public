#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <math.h>


int rank, p;
int max = 50000;
MPI_Status status;

int main(int argc, char** argv){
        clock_t t;	

        MPI_Init(&argc, &argv);
                MPI_Comm_rank(MPI_COMM_WORLD, &rank);
                MPI_Comm_size(MPI_COMM_WORLD, &p);		
		
		clock_t t2 = clock();
		double total = 0;
		for(int i = 0; i < max; i++){
			if(rank == 0){	
				t = clock();
				MPI_Send(&p, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
				MPI_Recv(&p, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
				total += (clock() - t);
			}	
			else{
				MPI_Recv(&p, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
				MPI_Send(&p, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}			
		}
		t2 = clock() - t2;
		if(rank ==  0){
			total = total/max;
			printf("Average time of %f microseconds in %i iterations\n", t2, max);
			fflush(stdout);
		}		
	
                MPI_Finalize();
                return 0;
}




