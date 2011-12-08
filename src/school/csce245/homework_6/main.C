// Jonathan Chandler
// main.C

#include "Item.h"
#include "PQ.h"
#include "Grassland.h"

int main(int argc, char ** argv){
	if(argc != 4){
		cout << "Incorrect input format.  Should be:  project6.exe #wolf #activeRabbits #lazyRabbits" << endl;
		exit(-1);
	}
	//
	//int i = 5, j = 2500, k = 2500;	
	//Grassland * g;
	//
	//for(; i < 5000; i += 5){
	//	for(; j < 4000 && k < 4000; j+=50, k+=50){
	//		for(;k < 10000; k+=25){
	//			g = new Grassland(i, j, k);
	//			delete g;
	//		}						
	//	}
	//}
	//

	Grassland * g = new Grassland(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	delete g;
	return 0;
}
