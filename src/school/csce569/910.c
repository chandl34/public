#include <mpi.h>
#include <stdio.h>
#include <math.h>


void manager();
void worker();

int rank, p;
long v, start, incr;
MPI_Status status;
enum{NEED_WORK, PERFECT};

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	incr = 5*(p-1);

	if(rank == 0)
		manager();
	else
		worker();

	MPI_Finalize();
	return 0;
}


void manager(){
	start = 2;
	int count = 0;
	int src, tag;
	while(count < 8){
		MPI_Recv(&v, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		tag = status.MPI_TAG;
		src = status.MPI_SOURCE;
		if(tag == NEED_WORK){
			MPI_Send(&start, 1, MPI_INT, src, NEED_WORK, MPI_COMM_WORLD);
			start += incr;
		}
		else{
			printf("Perfect number %i is %li\n", count+1, v);
			fflush(stdout);
			count++;
		}
	}
	printf("Shutting down...\n");
	fflush(stdout);
}

void worker(){
	long temp, sq;

	while(1){
                MPI_Send(&v, 1, MPI_INT, 0, NEED_WORK, MPI_COMM_WORLD);
                MPI_Recv(&start, 1, MPI_INT, MPI_ANY_SOURCE, NEED_WORK, MPI_COMM_WORLD, &status);
	
		for(int i = start; i < start + incr; i++){
			temp = pow(2, i) - 1;
			sq = ceil(sqrt(temp));
			for(int j = sq; j > 1; j--){
				if(temp%j == 0){ // Not prime
					temp = 0;
					break;
				}
			}		
			if(temp != 0){				
				v = temp*(pow(2, i-1));
                		MPI_Send(&v, 1, MPI_INT, 0, PERFECT, MPI_COMM_WORLD);
			}	
		}			
	}
}
