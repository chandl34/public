#ifndef WALL_H_
#define WALL_H_

#include "../../models/types/mapModels/BreakableModel.h"
#include "../../models/types/mapModels/DoorModel.h"

class Wall{
public:
	Wall();
	virtual ~Wall();

	void setFrame(BreakableModel*);
	void setWindow(BreakableModel*);	
	void setDoor(DoorModel*);
	void clear();

	int getType();
	int getMirror();
	int getInvert();
	int getShift();
	int getAngle();
	int getFrameCondition();
	int getWindowCondition();

	void load();
	void draw(int, int);
		
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
};

#endif /*WALL_H_*/
