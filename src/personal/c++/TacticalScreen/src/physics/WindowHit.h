#ifndef WINDOWHIT_H_
#define WINDOWHIT_H_

#include "../models/types/mapModels/BreakableModel.h"
#include "../world/map/Coordinate.h"

class WindowHit{
public:
	WindowHit(int, Coordinate*, BreakableModel*);
	virtual ~WindowHit();
	
	int getTime();
	Vertex* getCenter();
	void breakWindow();
	
private:
	int time;
	Vertex* center;
	BreakableModel* model;
};

#endif /*WINDOWHIT_H_*/
