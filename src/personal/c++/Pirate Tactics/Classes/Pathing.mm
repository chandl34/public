/*
 *  Pathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Pathing.h"
#include "LevelMap.h"

AStarNode* Pathing::node[MAP_BLOCK_X][MAP_BLOCK_Y];
Heap Pathing::openHeap(true);
GLshort Pathing::open;
GLshort Pathing::closed;

Pathing::Pathing(){
	for(GLshort i = 0; i < MAP_BLOCK[X]; i++){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; j++)
			node[i][j] = new AStarNode(Coord2d<GLshort>(i, j));
	}
	reset();
}

Pathing::~Pathing(){
	for(GLshort i = 0; i < MAP_BLOCK[X]; i++){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; j++)
			delete node[i][j];
	}
}


Directions* Pathing::getDirections(const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal){	
	Directions* path = NULL;
		
	AStarNode* n = node[start[X]][start[Y]];		
	n->setStatus(open);
	n->setParent(NULL);
	n->setDistance(0);
	n->setEstimate(findEstimate(n->getPathCoord(), node[goal[X]][goal[Y]]->getPathCoord()));
	n->findPriority();
	openHeap.push(n);	
	
	/*
	cout << "pc:  (" << node[goal[X]][goal[Y]]->getPathCoord()[X] << ", " << node[goal[X]][goal[Y]]->getPathCoord()[Y] << ")" << endl;
	cout << "rl:  (" << node[goal[X]][goal[Y]]->getCoord()[X] << ", " << node[goal[X]][goal[Y]]->getCoord()[Y] << ")" << endl;
	
	
	GLshort x = node[goal[X]][goal[Y]]->getPathCoord()[X];
	GLshort y = node[goal[X]][goal[Y]]->getPathCoord()[Y];
	
	LevelMap::getBlockBy3D(x*BLOCK_SIZE_3D[X], 
							y*BLOCK_SIZE_3D[Y]);	// MIDDLE
	*/
	
	
	AStarNode* temp;
	GLfloat dist;
	Coord2d<GLshort> next;
	bool success = false;	
	
	while(!openHeap.isEmpty()){
		n = (AStarNode*)openHeap.pop();
		n->setStatus(closed);
		if(n->equals(goal[X], goal[Y])){
			success = true;
			break;
		}		
		for(GLshort i = 0; i < PATH_DIRS; i++){
			next[X] = n->getCoord(X) + DIR[n->getCoord(Y)%2][i][X];
			next[Y] = n->getCoord(Y) + DIR[n->getCoord(Y)%2][i][Y];
			if(canGoTo(n->getCoord(), next, i)){	
				temp = node[next[X]][next[Y]];
				dist = n->getDistance() + MOVE_COST[i%2];
				if(temp->getStatus() != open){
					temp->setStatus(open);
					temp->setParent(n);
					temp->setDirection(i);		
					temp->setEstimate(findEstimate(temp->getPathCoord(), 
												   node[goal[X]][goal[Y]]->getPathCoord()));
					temp->setDistance(dist);
					temp->findPriority();
					openHeap.push(temp);
				}
				else if(dist < temp->getDistance()){	
					temp->setParent(n);
					temp->setDirection(i);
					temp->setDistance(dist);
					temp->findPriority();	
					openHeap.reheap(temp->getNode());
				}
			}
		}
	}	
	
	if(success)
		path = new Directions(n);
	
	// Clean up
	open += 2;
	closed += 2;
	if(closed > 32000)
		reset();
	
	openHeap.clear();
	
	return path;
}

GLfloat Pathing::findEstimate(const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal){
	GLshort dx = abs(start[X] - goal[X]);
	GLshort dy = abs(start[Y] - goal[Y]);
	return min(dx, dy)*MOVE_COST[ORTH] + abs(dx - dy)*MOVE_COST[DIAG]; 
}
	
bool Pathing::canGoTo(const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal, GLshort dir){		
	GridBlock* goalBlock = LevelMap::getBlockByIso(goal[X], goal[Y]);	
	
	// Check if goal is reachable (this code should be impossible to run)
	if(goalBlock == NULL)
		return false;
	
	// Check if goal has already been checked by A* and closed
	if(node[goal[X]][goal[Y]]->getStatus() == closed)
		return false;
	
	// Check if the goal is completely blocked by an object
	if(goalBlock->isBlocked(ALL_DIR) || goalBlock->hasVisibleUnit())
		return false;
	
	GridBlock* tempBlock;
	GridBlock* startBlock = LevelMap::getBlockByIso(start[X], start[Y]);	
	
	// Check simple directions
	if(startBlock->isBlocked(dir))
		return false;
	if(goalBlock->isBlocked((dir + 4)%PATH_DIRS))
		return false;
	
	switch(dir){
		// Check complex directions
		case LEFT:
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][UP_LEFT][X],
												start[Y] + DIR[start[Y]%2][UP_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(DOWN))
				return false;
			break;
			
		case RIGHT:	
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][UP_RIGHT][X],
												start[Y] + DIR[start[Y]%2][UP_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(DOWN))
				return false;	
			break;			
			
		// Check more complex directions
		case UP:
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][UP_LEFT][X],
												start[Y] + DIR[start[Y]%2][UP_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(RIGHT))
				return false;
			
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][UP_RIGHT][X],
												start[Y] + DIR[start[Y]%2][UP_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(LEFT))
				return false;
			break;
			
		case DOWN:
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][DOWN_LEFT][X],
												start[Y] + DIR[start[Y]%2][DOWN_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(RIGHT))
				return false;
			
			tempBlock = LevelMap::getBlockByIso(start[X] + DIR[start[Y]%2][DOWN_RIGHT][X],
												start[Y] + DIR[start[Y]%2][DOWN_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(LEFT))
				return false;
			break;
			
	}	
	
	return true;
}

void Pathing::reset(){
	open = -32000;
	closed = open + 1;
		
	for(GLshort i = 0; i < MAP_BLOCK[X]; i++){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; j++)
			node[i][j]->setStatus(open - 1);
	}
}
