/*
 *  AStarNode.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef ASTARNODE_H_
#define ASTARNODE_H_

#include "HeapItem.h"


class AStarNode : public HeapItem{
public:
	AStarNode(const Coord2d<GLshort>&);
	virtual ~AStarNode();
	
	GLfloat getValue() const;
	
	GLfloat getEstimate() const;
	void setEstimate(GLfloat);	
	GLfloat getDistance() const;	
	void setDistance(GLfloat);
	GLfloat getPriority() const;
	void setPriority(GLfloat);	
	void findPriority();
		
	AStarNode* getParent() const;
	void setParent(AStarNode*);	
	GLshort getDirection() const;
	void setDirection(GLshort);	
	const Coord2d<GLshort>& getCoord() const;
	GLshort getCoord(GLshort) const;
	GLshort getPathCoord(GLshort) const;
	const Coord2d<GLshort>& getPathCoord() const;
	
	GLshort getStatus() const;
	void setStatus(GLshort);	
	
	bool equals(GLshort, GLshort) const;
	
private:	
	GLfloat priority, estimate, distance;	// Priority = Estimate + Distance
	AStarNode* parent;	
	GLshort dir;
	Coord2d<GLshort> coord;
	Coord2d<GLshort> pathCoord;
	GLshort status;	
};

#include "Node.h"

#endif

