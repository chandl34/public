/*
 *   C program that uses the Monte Carlo method to solve the neutron
 *   transport problem posed in Section 10.5.1.
 *
 *   Programmed by Michael J. Quinn
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define C  2.0
#define CS 1.5
#define CC (C - CS)
#define CCC CC/C
#define PI 3.1415926

int main (int argc, char *argv[])
{
   clock_t t = clock()/1000000;
   int h;
   double l;
   int i, its;
   double x;
   double d;
   int active;
   unsigned short xi[3];
   int refl, abs, trans;

   xi[0] = 0;
   xi[1] = 1;
   xi[2] = 2;

   its = 100000000; /* Book says 10 million tests */

   omp_set_num_threads(atoi(argv[1]));

   ///////------#pragma omp parallel for private(h, i, d, x, active, refl, abs, trans)
   for(h = 1; h <= 10; h++){
       refl = 0;
       abs = 0;
       trans = 0;

       #pragma omp parallel for private(i, d, x, active) reduction(+:refl) reduction(+:trans) reduction(+:abs) schedule(dynamic, 50000)
       for(i = 1; i <= its; i++){
           d = 0.0;	
           x = 0.0;

           active = 1;
	   while(active){
	       x += -(1.0/C)*log(erand48(xi))*cos(d);
	       if(x < 0.0){
		   refl++;
		   active = 0;
	       }
	       else if(x >= h){
		   trans++;
		   active = 0;
	       }
	       else if(erand48(xi) < CCC){
		   abs++;
		   active = 0;
	       }
	       d = erand48(xi)*PI;
 	   }
       }
       printf("H = %d, Reflected     Absorbed      Transmitted\n", h);
       printf("%14.2f%14.2f%14.2f\n\n",
              (100.0*refl)/(float)its,
              (100.0*abs)/(float)its,
              (100,0*trans)/(float)its);
       printf("Time so far:  %i seconds.\n", clock()/1000000 - t);
   }
   printf("Completed in %i seconds.\n", clock()/1000000 - t);
}

