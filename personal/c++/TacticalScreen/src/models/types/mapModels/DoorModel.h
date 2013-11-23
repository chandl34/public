#ifndef DOORMODEL_H_
#define DOORMODEL_H_

#include "../../../containers/MapModelContainer.h"
#include "../../Model.h"
	
class DoorModel{
public:
	DoorModel();
	DoorModel(bool, bool, bool, int, int);
	virtual ~DoorModel();
	
	bool getMirror();
	bool getShift();
	bool getInvert();
	int getAngle();
	int getIndex();
	Vertex* getCenter();
	Model* getModel();
	
	void setMotion(int);
	void load();
	void draw(float, float, float);
	
	enum{CLOSING, STEADY, OPENING};
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & mirror;
		ar & shift;
		ar & invert;
		ar & angle;
		ar & index;
	}
	
	Model* model;
	bool mirror, shift, invert;
	int angle, index;
	int motion;
	
};

#endif /*DOORMODEL_H_*/
