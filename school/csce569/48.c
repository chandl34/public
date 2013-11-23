#include <mpi.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char** argv){
	clock_t t = clock()/1000;
	int max = 1000000;
	int pValue, pTotal, total;
	int rank, p, old;
	int endPrime;
	int ready = 0, active = 0;
	MPI_Status status;		

	MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &p);	

		int size = max/p;
		int value[size];
		int start = rank*size;
		int firstvalue;
		enum{PRIME, NOTPRIME};	
		
		for(int i = 0; i < size; i++)
			value[i] = PRIME;
                if(rank == 0){
               		value[0] = NOTPRIME;
                        value[1] = NOTPRIME;
                        pValue = 2;
                        ready = 1;
                        for(int i = 1; i < p; i++){
                                MPI_Send(&pValue, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                	        MPI_Send(&ready, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                                MPI_Send(&active, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
                	}			
                }
	
		while(active == 0){
			if(ready == 0){
				MPI_Recv(&pValue, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
				MPI_Recv(&ready, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &status);
				MPI_Recv(&active, 1, MPI_INT, MPI_ANY_SOURCE, 2, MPI_COMM_WORLD, &status);
				//printf("Process %i is using prime number %i.\n", rank, pValue);
				//fflush(stdout);
			}			
			else{
				ready = 0;
				// find first value
				if(rank == 0)
					firstvalue = pValue + pValue;
				else{					
					for(int i = 0; i < size; i++){
						if((i + start)%pValue == 0){
							firstvalue = i;
							break;
						}
					}
				}				
				// mark non-primes				
				for(int i = firstvalue; i < size; i += pValue)
					value[i] = NOTPRIME;
				if(rank == 0){		
					ready = 1;
					old = pValue;
					// Find next value
					for(int i = pValue + 1; i < size; i++){
                                     		if(value[i] == PRIME){
							pValue = i;
						 	break;
						}
					}
					if(pValue > 1000 || pValue == old)	// We're done here
						active = 1;
                                       	for(int i = rank + 1; i < p; i++){                    						
						MPI_Send(&pValue, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
                                                MPI_Send(&ready, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
                                        	MPI_Send(&active, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
					}
				}					
			}		
		}		
		// Find total of current process
		pTotal = 0;
		for(int i = 3; i < size; i += 2){
			if(value[i] == PRIME && value[i-2] == PRIME)
				pTotal++;
		}
		if(rank != p - 1){
			int temp = size - 1;
			if(size % 2 == 1)
				temp--;
			if(value[temp] == PRIME)
				endPrime = 1;
			else
				endPrime = 0;
			MPI_Send(&endPrime, 1, MPI_INT, rank+1, 3, MPI_COMM_WORLD);

		}
		if(rank > 0){
			endPrime = -1;
			while(endPrime == -1)
				MPI_Recv(&endPrime, 1, MPI_INT, MPI_ANY_SOURCE, 3, MPI_COMM_WORLD, &status);
			if(endPrime == 1 && value[1] == PRIME)
				pTotal++;		
		}
//		printf("Process %i had %i consective odd primes.\n", rank, pTotal);
//		fflush(stdout);

		MPI_Reduce(&pTotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
			
		if(rank == 0){
			printf("Total consecutive odd primes:  %i\n", total);
			fflush(stdout);
			printf("Process took %i milliseconds.\n", clock()/1000 - t);
			fflush(stdout);                  
		}
	MPI_Finalize();
	
	return 0;
}
