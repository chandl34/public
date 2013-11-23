#include <mpi.h>
#include <stdio.h>
#include <math.h>


void manager();
void worker();

int rank, p;
double bound[2];
double data[2];
MPI_Status status;
enum{NEED_WORK, NEW_BOUND};

int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &p);

	if(rank == 0)
		manager();
	else
		worker();

	MPI_Finalize();
	return 0;
}


void manager(){
	bound[0] = 0.0;
	bound[1] = 1.0;

	data[0] = bound[0]; 		// start point
	data[1] = bound[1]/10.0;	// increment (done ten times)
	
	double buffer[2];
	int src, tag;
	int count = 0;

	while((bound[1]-bound[0]) >= pow(10.0,-11.0)){
		if(count == 10){
//			printf("Waiting for bound\n");
//			fflush(stdout);
			MPI_Recv(&buffer, 2, MPI_DOUBLE, MPI_ANY_SOURCE, NEW_BOUND, MPI_COMM_WORLD, &status);
			count = 0;
		}
		else
			MPI_Recv(&buffer, 2, MPI_DOUBLE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		src = status.MPI_SOURCE;
		tag = status.MPI_TAG;
		if(tag == NEED_WORK){
			MPI_Send(&data, 2, MPI_DOUBLE, src, NEW_BOUND, MPI_COMM_WORLD);
			data[0] += data[1];
			count++;		
		}
		else if(tag == NEW_BOUND){
			bound[0] = buffer[0];
			bound[1] = buffer[1];
			data[0] = bound[0];
			data[1] /= 100.0;
			count = 0;
			printf("New bounds are [%1.12f, %1.12f]\n", bound[0], bound[1]);
			fflush(stdout);	
		}
	}
	printf("Shutting down...\n");
	fflush(stdout);
	data[0] = -1;
	for(int i = 1; i < p; i++)
		MPI_Send(&data, 2, MPI_DOUBLE, i, NEW_BOUND, MPI_COMM_WORLD);
}

void worker(){
	int pos;
	double prev, curr;
	while(1){
		MPI_Send(&bound, 2, MPI_DOUBLE, 0, NEED_WORK, MPI_COMM_WORLD);
		MPI_Recv(&data, 2, MPI_DOUBLE, MPI_ANY_SOURCE, NEW_BOUND, MPI_COMM_WORLD, &status);
		if(data[0] < 0)
			break;
		bound[0] = data[0];
		bound[1] = data[0] + data[1]; // don't need to do this
		data[1] /= 10.0f;		
		
//		printf("%i is testing its bounds: [%f, %f]\n", rank, bound[0], bound[1]);
//		fflush(stdout);

		for(int i = 0; i < 11; i++){
			curr = -2.0;
			for(int j = 0; j < 1000; j++){
				curr += sind(pow(bound[0]+data[1]*i, j+1));
			}	
			
//			printf("Current value: %f\n", curr);
//			fflush(stdout);

			if(i == 1){	// tests if going in wrong direction
				if(pos == 1 && curr > prev)
					break;
				if(pos == 0 && curr < prev)
					break;
			}			
			if(i > 0){
				if((pos == 1 && curr < 0) || (pos == 0 && curr > 0)){
					bound[0] += data[1]*(i-1);
					bound[1] = bound[0] + data[1];
//					printf("Found new bound\n");
//					fflush(stdout);
					MPI_Send(&bound, 2, MPI_DOUBLE, 0, NEW_BOUND, MPI_COMM_WORLD);	
					break;
				}
			}
			if(curr < 0)
				pos = 0;
			else
				pos = 1;
			prev = curr;
		}
	}
}
