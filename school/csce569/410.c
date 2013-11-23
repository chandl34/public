#include <mpi.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int main(int argc, char** argv){
	clock_t t = clock()/1000;
	int highest = 989898;
	int smallest = 101010;
	int count = highest - smallest;
	int pTotal = 0, total = 0;
	int rank, p;
	int a, b, c, d, e, f;
	int boundL, boundH;
	int sum;
	
	MPI_Init(&argc, &argv);
		MPI_Comm_rank(MPI_COMM_WORLD, &rank);
		MPI_Comm_size(MPI_COMM_WORLD, &p);	
		
		int size = ceil(((float)count)/p);
		
		boundL = smallest + rank*size; 
		boundH = boundL + size;
		if(boundH >= highest)
			boundH = highest + 1;
		a = boundL / 100000;
		b = (boundL % 100000) / 10000;
		c = (boundL % 10000) / 1000;
		d = (boundL % 1000) / 100;
		e = (boundL % 100) / 10;
		f = boundL % 10;
		for(int i = boundL; i < boundH;){
			sum = a + b + c + d + e + f;
 		        //if(f<15){printf("%i %i %i %i %i %i\n", a, b, c, d, e , f);fflush(stdout);}
			if(a == b){
				b++;
				i += 10000;
			}
			else if(b == c){
				c++;
				i += 1000;
			}
			else if(c == d){
				d++;
				i += 100;
			}
			else if(d == e){
				e++;
				i += 10;
			}
			else{ 					
                       		if(sum == 7 || sum == 11 || sum == 13);
				else if(e != f)
					pTotal++;
				f++;	
				i++;						
			}	
			if(f == 10){
				e++;
				f = 0;
			}
			if(e >= 10){
				d++;
				e = e - 10;
			}
			if(d >= 10){
				c++;
				d = d - 10;
			}
			if(c >= 10){
				b++;
				c = c - 10;
			}
			if(b >= 10){
				a++;
				b = b - 10;
			}
		}

		
 //               printf("Process %i found %i combinations.\n", rank, pTotal);
//                fflush(stdout);


		MPI_Reduce(&pTotal, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);	
	
			
	
		if(rank == 0){
			printf("Total combinations:  %i\n", total);
			fflush(stdout);
			printf("Process took %i milliseconds.\n", clock()/1000 - t);
			fflush(stdout);                  
		}
	MPI_Finalize();
	
	return 0;
}
