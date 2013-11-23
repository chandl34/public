#ifndef WALL_H_
#define WALL_H_

#include "../Selection.h"
#include "../../../models/types/mapModels/BreakableModel.h"
#include "../../../gl/ID.h"

class Wall{
public:
	Wall();
	virtual ~Wall();
	void load(Coordinate*, map<int, Selection*>&);
	
	BreakableModel* getFrame();
	BreakableModel* getWindow();
	DoorModel* getDoor();
	int getBlockingDoors();

	void incrBlockingDoor(bool);
	bool passable();
	
	void draw(int, int, int, int);	
		
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & frame;	
		ar & window;
		ar & door;
	}
	
	BreakableModel* frame;	
	BreakableModel* window;
	DoorModel* door;
	int blockingDoors;
	int id;	
};

#endif /*WALL_H_*/
