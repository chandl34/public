#ifndef DIRECTION_H_
#define DIRECTION_H_

#include "../../Include.h"

class Direction{
public:
	Direction(int, int, int, float, float);
	virtual ~Direction();
	
	int get(int);
	int getIndex();
	float getSin();
	float getCos();
	
private:
	int* dir;
	int index;
	float sine, cosine;
};

#endif /*DIRECTION_H_*/
