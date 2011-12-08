#ifndef MAP_H_
#define MAP_H_

#include "Block.h"

class Map{
public:
	Map(int, int);
	virtual ~Map();
	
	void draw();
	
	int getWidth(){return width;}
	int getHeight(){return height;}
	
private:
	int width, height;
	Block*** block;	
};

#endif /*MAP_H_*/
