#ifndef DOORMODEL_H_
#define DOORMODEL_H_

#include <boost/serialization/utility.hpp>
#include <FL/Gl.H>
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
	
	void load();
	void draw(float, float, float);
	
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
	
};

#endif /*DOORMODEL_H_*/
