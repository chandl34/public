#include "Pathing.h"
#include "../World.h"

float** Pathing::moveSpeed;

Pathing::Pathing(){
	openHeap = new MinHeap();

	node = new AStarNode**[LEVEL_LENGTH + 1];
	for(int i = 0; i < LEVEL_LENGTH + 1; i++){
		node[i] = new AStarNode*[LEVEL_LENGTH + 1];
		for(int j = 0; j < LEVEL_LENGTH + 1; j++){
			if(World::getCoord(i, j) == NULL) 
				node[i][j] = NULL;	
			else
				node[i][j] = new AStarNode(World::getCoord(i, j), 32767);
		}
	}	
	closed = 32765; open = 32766;

	moveCost = new int*[3];
	moveCost[ORTH] = new int[2];
	moveCost[ORTH][WALK] = 2; moveCost[ORTH][RUN] = 1;
	moveCost[DIAG] = new int[2];
	moveCost[DIAG][WALK] = 3; moveCost[DIAG][RUN] = 2;
	moveCost[JUMP] = new int[2];
	moveCost[JUMP][WALK] = 6; moveCost[JUMP][RUN] = 6;

	moveSpeed = new float*[3];
	moveSpeed[ORTH] = new float[2];
	moveSpeed[ORTH][WALK] = 0.1f; moveSpeed[ORTH][RUN] = 0.2f;
	moveSpeed[DIAG] = new float[2];
	moveSpeed[DIAG][WALK] = 0.07071f; moveSpeed[DIAG][RUN] = 0.14142f;
	moveSpeed[JUMP] = new float[2];
	moveSpeed[JUMP][WALK] = 0.05f; moveSpeed[JUMP][RUN] = 0.05f;
}

Pathing::~Pathing(){
	for(int i = 0; i < LEVEL_LENGTH + 1; i++){
		for(int j = 0; j < LEVEL_LENGTH + 1; j++){
			if(node[i][j] != NULL)
				delete node[i][j];
		}
		delete [] node[i];
	}
	delete [] node;
	delete openHeap;
	
	for(int i = 0; i < 3; i++){
		delete [] moveCost[i];
		delete [] moveSpeed[i];
	}		
	delete [] moveCost;
	delete [] moveSpeed;
}

void Pathing::reset(){
	closed = 32765; open = 32766;

	for(int i = 0; i < LEVEL_LENGTH + 1; i++){
		for(int j = 0; j < LEVEL_LENGTH + 1; j++){
			if(node[i][j] != NULL)
				node[i][j]->setStatus(32767);
		}
	}
}

bool Pathing::isOpen(int x, int y){		
	if(node[x][y]->getStatus() == open)
		return true;
	return false;
}

bool Pathing::isClosed(int x, int y){		
	if(node[x][y]->getStatus() <= closed)
		return true;
	return false;
}

bool Pathing::hasCharacter(int x, int y){
	if(map->getBlock(x, y)->getCharacter() == NULL)
		return false;
#ifdef CHARMOVED
	path->addCharLoc(node[x][y]->getCoord());
#endif //CHARMOVED
	node[x][y]->setStatus(closed);
	return true;
}

int Pathing::canGoTo(Coordinate* start, Direction* direction){
	int x = start->get(X);
	int y = start->get(Y);
	int dx = direction->get(X);
	int dy = direction->get(Y);
	fx = x + dx;
	fy = y + dy;
	
	if(node[fx][fy] == NULL || isClosed(fx, fy) || hasCharacter(fx, fy))
		return -1;		

	if(!map->getBlock(fx, fy)->accessible()){
		if(map->getBlock(fx, fy)->jumpable()){  // Trying to cross a fence?
				if(dx == 0 || dy == 0){ // Going orthogonal direction?
					int fx2 = x + dx + dx, fy2 = y + dy + dy;
					if(!isClosed(fx2, fy2) && !hasCharacter(fx2, fy2) && 
							map->getBlock(fx2, fy2)->accessible()){	// Other side is available?
						if(dx != 0 && map->getBlock(fx, fy)->jumpable(LEFT))
							return JUMP;
						else if(dy != 0 && map->getBlock(fx, fy)->jumpable(RIGHT))
							return JUMP;	
					}
				}
		}
		return -1;
	}

	if(dx == -1){ // Wall in the way left or right?
		if(!map->getBlock(x, y)->passable(LEFT) || 
				(map->getBlock(x, fy) != NULL && !map->getBlock(x, fy)->passable(LEFT)))
			return -1;
	}
	else if(dx == 1){
		if(!map->getBlock(fx, fy)->passable(LEFT)||
				(map->getBlock(fx, y) != NULL && !map->getBlock(fx, y)->passable(LEFT))) 
			return -1;
	}
	if(dy == 1){ // Wall in the way forward or backward?
		if(!map->getBlock(x, y)->passable(RIGHT) || 
				(map->getBlock(fx, y) != NULL && !map->getBlock(fx, y)->passable(RIGHT)))
			return -1;
	}
	else if(dy == -1){
		if(!map->getBlock(fx, fy)->passable(RIGHT)||
				(map->getBlock(x, fy) != NULL && !map->getBlock(x, fy)->passable(RIGHT))) 
			return -1;
	}

	if(dx == 0 || dy == 0)
		return ORTH;
	return DIAG;
}

int Pathing::findEstimate(Coordinate* coord, Coordinate* goal){
	int dx = abs(coord->get(X) - goal->get(X));
	int dy = abs(coord->get(Y) - goal->get(Y));
	return min(dx, dy)*moveCost[DIAG][WALK] + abs(dx - dy)*moveCost[ORTH][WALK]; // Hardcoded WALK allows
}																				 // movement to be realistic

int Pathing::getMovementCost(int d){
	if(stopped)
		return moveCost[d][WALK];
	return moveCost[d][currentSpeed];
}

float Pathing::getMovementSpeed(int d, int s){
	return moveSpeed[d][s];
}

PathingInstructions* Pathing::aStarPath(Coordinate* start, Coordinate* goal, int s){
	map = World::getSelectedMap();
	if(!map->getBlock(goal)->accessible())
		return NULL;
	if(closed < -32766)
		reset();
	path = new PathingInstructions(map);
	AStarNode* n = node[start->get(X)][start->get(Y)];
	currentSpeed = s;
	stopped = true;

	n->setStatus(open);
	n->setParent(NULL);
	n->setDistance(0);
	n->setEstimate(findEstimate(start, goal));
	n->findPriority();
	n->setJumped(false);
	openHeap->push(n);
	
	int cost, i, dist;
	bool success = false;
	Direction* dir;

	while(!openHeap->isEmpty()){
		n = openHeap->pop();
		if(n->getCoord() == goal){
			success = true;
			break;
		}
		n->setStatus(closed);
		if(n->hasJumped())
			stopped = true;

		for(i = 0; i < 8; i++){
			dir = World::getDir(i);
			cost = canGoTo(n->getCoord(), dir);	
			if(cost != -1){						
				dist = n->getDistance() + getMovementCost(cost);
				if(cost == JUMP){
					fx += dir->get(X);
					fy += dir->get(Y);
				}					
				if(!isOpen(fx, fy)){
					node[fx][fy]->setStatus(open);
					node[fx][fy]->setParent(n);
					node[fx][fy]->setDirection(dir);
					node[fx][fy]->setEstimate(findEstimate(node[fx][fy]->getCoord(), goal));
					node[fx][fy]->setDistance(dist);
					node[fx][fy]->findPriority();
					node[fx][fy]->setJumped(cost == JUMP);
					openHeap->push(node[fx][fy]);
				}
				else if(dist < node[fx][fy]->getDistance()){
					node[fx][fy]->setParent(n);
					node[fx][fy]->setDirection(dir);
					node[fx][fy]->setDistance(dist);
					node[fx][fy]->findPriority();
					node[fx][fy]->setJumped(cost == JUMP);
					openHeap->reheap(node[fx][fy]->getNode());
				}
			}
		}
		stopped = false;
	}

	closed -= 2; open -= 2;	
	if(!success){
		delete path;
		return NULL;
	}
	else{
		cout << "Time Unit cost:  " << n->getDistance() << endl;
		openHeap->clear();
		path->pushPath(n);
		return path;
	}		
}
