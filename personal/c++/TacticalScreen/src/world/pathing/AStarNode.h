#ifndef ASTARNODE_H_
#define ASTARNODE_H_

#include "../map/Coordinate.h"
#include "Direction.h"

class Node;

class AStarNode{
public:
	AStarNode(Coordinate*, int);
	virtual ~AStarNode();

	int getEstimate();
	void setEstimate(int);	
	int getPriority();
	void findPriority();
	int getDistance();	
	void setDistance(int);
	AStarNode* getParent();
	void setParent(AStarNode*);
	bool hasJumped();
	void setJumped(bool);
	Direction* getDirection();
	void setDirection(Direction*);
	
	int getStatus();
	void setStatus(int);	
	Coordinate* getCoord();
	
	void setNode(Node*);
	Node* getNode();
		
private:	
	int changed();
	
	int status;
	bool jumped;
	int priority, estimate, distance;  // Priority = Estimate + Distance
	AStarNode* parent;          	   // A*  :  F = G + H
	Coordinate* coord;
	Direction* dir;
	Node* node;
	
};

#include "heap/Node.h"

#endif /*ASTARNODE_H_*/
