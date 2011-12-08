#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;


int main(int argc, char* argv[]){
	if(argc != 3){
		printf("Format: mapMaker xValue yValue\n");
		return -1;
	}

	srandom(time(0));

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	int total = x*y;
	printf("Making %i random values for map.txt\n", total);		
        
	ofstream out;
	out.open("map.txt");

	out << x << " " << y << " ";
	
	for(int i = 0; i < total; i++)
		out << random()%10 << " ";
	
	out.close();
	return 0;
}
