/*
 *  Pathing.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/21/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Pathing.h"

#include "AStarNode.h"
#include "Directions.h"
#include "GridBlock.h"
#include "Unit.h"

#include "LevelMap.h"


AStarNode* Pathing::_node[MAP_BLOCK_X][MAP_BLOCK_Y];
Heap Pathing::_openHeap(true);
GLshort Pathing::_open;
GLshort Pathing::_closed;


Pathing::Pathing()
{
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			_node[i][j] = new AStarNode(Coord2d<GLshort>(i, j));
	}
	reset();
}


Pathing::~Pathing()
{
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			delete _node[i][j];
	}
}



Directions* Pathing::getDirections(Unit* u, const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal)
{	
	double timer = [[NSDate date] timeIntervalSince1970];
	
	Directions* path = NULL;
	
	AStarNode* n = _node[start[X]][start[Y]];		
	n->setStatus(_open);
	n->setParent(NULL);
	n->setDistance(0);
	n->setEstimate(findEstimate(n->getPathCoord(), _node[goal[X]][goal[Y]]->getPathCoord()));
	n->findPriority();
	_openHeap.push(n);		
	
	AStarNode* temp;
	double dist;
	GLshort blocked;
	Coord2d<GLshort> next;
	bool success = false;	
	
	while(!_openHeap.isEmpty()){
		n = (AStarNode*)_openHeap.pop();
		n->setStatus(_closed);
		if(n->equals(goal[X], goal[Y])){
			success = true;
			break;
		}		
		
		for(GLshort i = 0; i < PATH_DIRS; ++i){
			next[X] = n->getCoord(X) + DIR[n->getCoord(Y)%2][i][X];
			next[Y] = n->getCoord(Y) + DIR[n->getCoord(Y)%2][i][Y];
			blocked = canGoTo(u, n->getCoord(), next, i);
			if(blocked != BLOCKED){	
				temp = _node[next[X]][next[Y]];
				dist = n->getDistance() + MOVE_COST[i % 2];
				if(blocked == BLOCKED_BY_DOOR)
					dist += TOGGLE_COST;				
				if(temp->getStatus() != _open){
					temp->setStatus(_open);
					temp->setParent(n);
					temp->setDirection(i);		
					temp->setEstimate(findEstimate(temp->getPathCoord(), 
												   _node[goal[X]][goal[Y]]->getPathCoord()));
					temp->setDistance(dist);
					temp->findPriority();			
					_openHeap.push(temp);
				}
				else if(dist < temp->getDistance()){	
					temp->setParent(n);
					temp->setDirection(i);
					temp->setDistance(dist);
					temp->findPriority();	
					_openHeap.reheap(temp->getNode());
				}
			}
		}
	}	
	
	if(success)
		path = new Directions(n);
	
	// Clean up
	_open += 2;
	_closed += 2;
	if(_closed > 32000)
		reset();
	
	_openHeap.clear();
	
	timer = [[NSDate date] timeIntervalSince1970] - timer;
	printf("Finding path took %f seconds\n", timer);
	
	return path;
}


double Pathing::findEstimate(const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal)
{
	GLshort dx = abs(start[X] - goal[X]);
	GLshort dy = abs(start[Y] - goal[Y]);
	return min(dx, dy) * MOVE_COST[ORTH] + abs(dx - dy) * MOVE_COST[DIAG]; 
}


GLshort Pathing::canGoTo(Unit* u, const Coord2d<GLshort>& start, const Coord2d<GLshort>& goal, GLshort dir)
{		
	LevelMap* levelMap = LevelMap::getInstance();
	GridBlock* goalBlock = levelMap->getBlockByIso(goal[X], goal[Y]);	
	
	// Check if goal is reachable (this code should be impossible to run)
	if(goalBlock == NULL)
		return BLOCKED;
	
	// Check if goal has already been checked by A* and closed
	if(_node[goal[X]][goal[Y]]->getStatus() == _closed)
		return BLOCKED;
	
	// Check if the goal is completely blocked by an object
	if(goalBlock->isBlocked(ALL_DIR, WALLS_ONLY) || goalBlock->hasVisibleUnit(u))
		return BLOCKED;
	
	GridBlock* startBlock = levelMap->getBlockByIso(start[X], start[Y]);	
	GLshort blockedByDoor = NOT_BLOCKED;
	
	// Check simple directions
	if(startBlock->isBlocked(dir, WALLS_ONLY))
		return BLOCKED;
	if(startBlock->isBlocked(dir, DOORS_ONLY)){
		//if(u->getTeamID() == PLAYER)
		//	return BLOCKED;
		//else 
		if(u->findToggleBlock(startBlock, dir) == NULL)
			return BLOCKED;
		else
			blockedByDoor = BLOCKED_BY_DOOR;
	}
	
	GLshort oppDir = (dir + 4) % PATH_DIRS;
	if(goalBlock->isBlocked(oppDir, WALLS_ONLY))
		return BLOCKED;
	if(goalBlock->isBlocked(oppDir, DOORS_ONLY)){
		//if(u->getTeamID() == PLAYER)
		//	return BLOCKED;
		//else 
		if(u->findToggleBlock(startBlock, dir) == NULL)
			return BLOCKED;
		else
			blockedByDoor = BLOCKED_BY_DOOR;
	}
	
	GridBlock* tempBlock;
	switch(dir){
		case LEFT:
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][UP_LEFT][X],
												start[Y] + DIR[start[Y] % 2][UP_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(DOWN, WALLS_AND_DOORS))
				return BLOCKED;
			
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][DOWN_LEFT][X],
												start[Y] + DIR[start[Y] % 2][DOWN_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(UP, WALLS_AND_DOORS))
				return BLOCKED;
			break;
			
		case RIGHT:	
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][UP_RIGHT][X],
												start[Y] + DIR[start[Y] % 2][UP_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(DOWN, WALLS_AND_DOORS))
				return BLOCKED;	
			
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][DOWN_RIGHT][X],
												start[Y] + DIR[start[Y] % 2][DOWN_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(UP, WALLS_AND_DOORS))
				return BLOCKED;
			break;			
			
		case UP:
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][UP_LEFT][X],
												start[Y] + DIR[start[Y] % 2][UP_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(RIGHT, WALLS_AND_DOORS))
				return BLOCKED;
			
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][UP_RIGHT][X],
												start[Y] + DIR[start[Y] % 2][UP_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(LEFT, WALLS_AND_DOORS))
				return BLOCKED;
			break;
			
		case DOWN:
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][DOWN_LEFT][X],
												start[Y] + DIR[start[Y] % 2][DOWN_LEFT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(RIGHT, WALLS_AND_DOORS))
				return BLOCKED;
			
			tempBlock = levelMap->getBlockByIso(start[X] + DIR[start[Y] % 2][DOWN_RIGHT][X],
												start[Y] + DIR[start[Y] % 2][DOWN_RIGHT][Y]);
			if(tempBlock != NULL && tempBlock->isBlocked(LEFT, WALLS_AND_DOORS))
				return BLOCKED;
			break;
			
	}	
	
	return blockedByDoor;
}


void Pathing::reset()
{
	_open = -32000;
	_closed = _open + 1;
	
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			_node[i][j]->setStatus(_open - 1);
	}
}
