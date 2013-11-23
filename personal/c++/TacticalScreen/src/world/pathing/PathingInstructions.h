#ifndef PATHINGINSTRUCTIONS_H_
#define PATHINGINSTRUCTIONS_H_

#include "AStarNode.h"

class LevelMap;

class PathingInstructions{
public:
	PathingInstructions(LevelMap*);
	virtual ~PathingInstructions();
	
	void pushPath(AStarNode*);
	void addCharLoc(Coordinate*);
	
	bool charMoved();
	AStarNode* getNext();
	AStarNode* peek();
	bool isEmpty();
		
private:
	LevelMap* map;
	stack<AStarNode*>* destination;
	list<Coordinate*>* charList;
	
};

#include "../map/LevelMap.h"

#endif /*PATHINGINSTRUCTIONS_H_*/
