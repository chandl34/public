#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "../../containers/CharacterModelContainer.h"
#include "../../models/types/mapModels/DoorModel.h"
#include "../pathing/Pathing.h"

class Character{
public:
	Character(int, int, int);
	virtual ~Character();
	Selection* init(int, int);
	
	void setMap(LevelMap*, Coordinate*);
	void setLocation(Coordinate*);
	void setDestination(Coordinate*);
	void setLookDir(int);
	void setVisible(int);
	void setDoorToOpen(DoorModel*);
	
	Direction* getLookDir();
	CharacterModel* getCharModel();
	Coordinate* getCoord();
	int getType();
	int getVisible();
	void lookAt(Coordinate*);	
	void shootAt(Vertex*);
	void findVisible();
	bool isSeen(Character*);

	void checkView();
	void clearSeen();
	void draw();		
	
private:
	void move();
	void shoot();
	Direction* dirTo(Coordinate*);
	void stopMoving();	
	void turn();
	void turn(Direction*);	
	
	LevelMap* map;
	int* id;
	
	CharacterModel* model;
	int gender;
	int type;
	int visible;
	int index;  			// Index of this model in the Container
	set<Character*> seen;

	PathingInstructions* path;
	Coordinate* loc;		// Current location
	Coordinate* dest;		// Final destination of path
	Coordinate* destChange;	// New destination in queue
	int* dist;	     		// Distance to next block in path
	float* actual;   		// Actual map position
	bool stopping, jumping, turning;

	Vertex* target;  		// Shooting at this
	int lookIncr;			// Increment to find look faster

	DoorModel* door;  		// Door to toggle
	Direction* targetLook;	// Index of desired look
	Direction* lookDir;   	// Direction character is looking
	int walkingDir;			// Orthogonal or diagonal

	int walkingSpeed;		// Walking, running, or jumping
	float speed;			// Actual speed across map
	int wsChange;			// New speed in queue
	

};

#endif /*CHARACTER_H_*/
