#include "Character.h"
#include "../World.h"

Coordinate* Character::getCoord(){return loc;}

void Character::setLocation(Coordinate* c){
	map->getBlock(loc)->setCharacter(NULL);
	map->getBlock(c)->setCharacter(this);
	loc = c;	
}

void Character::setDestination(Coordinate* c){
	if(path == NULL){
		dest = c;
		walkingSpeed = Pathing::WALK;
		path = World::getPathing()->aStarPath(loc, dest, walkingSpeed);
		if(path != NULL)
			turn(path->peek()->getDirection());		
	}	
	else if(!jumping){
		if(c != dest){
			if(walkingSpeed == Pathing::RUN)
				speed *= 0.75f;
			wsChange = Pathing::WALK;
		}
		else if(walkingSpeed == Pathing::WALK){
			speed *= 1.5f;
			wsChange = Pathing::RUN;
		}
		else
			return;

		destChange = c;
	}
}

void Character::stopMoving(){
	if(!stopping){
		stopping = true;
		dest = loc;
		if(walkingSpeed == Pathing::RUN)
			speed *= 0.5f;
	}
}

void Character::move(){
	float halfSpeed = speed/2 + EPSILON;
	// Successfully reached next block?
	if((actual[X] > loc->get(X) - halfSpeed && actual[X] < loc->get(X) + halfSpeed) &&
			(actual[Y] > loc->get(Y) - halfSpeed && actual[Y] < loc->get(Y) + halfSpeed)){ 
		checkView();
		actual[X] = loc->get(X);
		actual[Y] = loc->get(Y);
		jumping = false;
		stopping = false;
		//Do tests for reactions/mines/etc here

		// New destination?
		if(destChange != NULL){		
			PathingInstructions* tempPI = World::getPathing()->aStarPath(loc, destChange, wsChange);
			if(tempPI != NULL){
				turn(tempPI->peek()->getDirection());	
				walkingSpeed = wsChange;
				dest = destChange;
				if(path != NULL)
					delete path;
				path = tempPI;
			}
			destChange = NULL;
		}
		// Reached destination?
		if(dest == loc){
			if(path != NULL){
				delete path;
				path = NULL;
			}			
			return;
		}	
		// Turning?
		if(path->peek()->getDirection() != lookDir){
			if(turning){
				turn();
				return;
			}
			else
				setLookDir(path->peek()->getDirection()->getIndex());
		}

		Coordinate* next = path->getNext()->getCoord();	
		// Another character is in the way? 
		if(map->getBlock(next)->getCharacter() != NULL){
			delete path;
			path = World::getPathing()->aStarPath(loc, dest, walkingSpeed);
			if(path == NULL)
				return;
		}   
#ifdef CHARMOVED
		if(path->charMoved()){
			delete path;
			path = World::getPathing()->aStarPath(loc, dest, walkingSpeed);
			if(path == NULL)
				return;
		}
#endif
		dist[X] = next->get(X) - loc->get(X);
		dist[Y] = next->get(Y) - loc->get(Y);
		if(abs(dist[X]) == 2 || abs(dist[Y]) == 2){
			walkingDir = Pathing::JUMP;
			jumping = true;			
		}
		else if(dist[X] == 0 || dist[Y] == 0)
			walkingDir = Pathing::ORTH;
		else
			walkingDir = Pathing::DIAG;
		speed = Pathing::getMovementSpeed(walkingDir, walkingSpeed);
		setLocation(next);
	}	
	actual[X] += dist[X]*speed;
	actual[Y] += dist[Y]*speed;
}
