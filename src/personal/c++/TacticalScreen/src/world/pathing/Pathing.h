#ifndef PATHING_H_
#define PATHING_H_

#include "heap/MinHeap.h"
#include "PathingInstructions.h"
#include "../map/LevelMap.h"

class Pathing{
public:
	Pathing();
	virtual ~Pathing();

	PathingInstructions* aStarPath(Coordinate*, Coordinate*, int);	
	static float getMovementSpeed(int, int);

	enum{WALK, RUN};
	enum{ORTH, DIAG, JUMP};
	
private:
	void reset();
	bool isOpen(int, int);
	bool isClosed(int, int);
	bool hasCharacter(int, int);
	int canGoTo(Coordinate*, Direction*);
	int findEstimate(Coordinate*, Coordinate*);
	int getMovementCost(int);
	
	int closed, open;
	
	int** moveCost;
	static float** moveSpeed;
	int currentSpeed;
	bool stopped;
	int fx, fy;
	LevelMap* map;
	AStarNode*** node;
	PathingInstructions* path;
	MinHeap* openHeap;
};

#endif /*PATHING_H_*/
