#ifndef BLOCK_H_
#define BLOCK_H_

#include "../Include.h"

class Block{
public:
	Block(int, int);
	virtual ~Block();
	
	void draw();
	
private:
	int x, z;
};

#endif /*BLOCK_H_*/
