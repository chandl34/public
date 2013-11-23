// Jonathan Chandler
// Animal.C

#include "Animal.h"

Animal::Animal(int x1, int y1, int t1, Grassland * g1){
	x = x1;
	y = y1;
	born = lastEat = t1;
	g = g1;
}
