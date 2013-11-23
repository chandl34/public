#ifndef COORDINATE_H_
#define COORDINATE_H_

#include "../../Include.h"

class Coordinate{
public:
	Coordinate(int x, int y){coord = new int[2]; coord[X] = x; coord[Y] = y;}
	virtual ~Coordinate(){delete [] coord;}
	
	void set(int x, int y){coord[X] = x;  coord[Y] = y;}	
	int get(int c){return coord[c];}
		
private:
	int* coord;
	
};

#endif /*COORDINATE_H_*/
