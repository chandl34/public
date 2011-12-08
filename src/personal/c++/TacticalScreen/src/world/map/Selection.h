#ifndef SELECTION_H_
#define SELECTION_H_

#include "../../models/types/mapModels/DoorModel.h"
#include "../characters/Character.h"

class Selection{
public:
	Selection();
	virtual ~Selection();
	
	void setCoord(Coordinate*);	
	void setCharacter(Character*);	
	void setDoor(DoorModel*);
	void setType(int);	
	
	DoorModel* getDoor();
	Coordinate* getCoord();
	int getType();
	Vertex* getCenter();
		
private:
	Coordinate* coord;
	Character* character;
	DoorModel* door;
	int type;
};

#endif /*SELECTION_H_*/
