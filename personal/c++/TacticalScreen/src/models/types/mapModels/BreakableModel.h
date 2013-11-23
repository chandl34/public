#ifndef BREAKABLEMODEL_H_
#define BREAKABLEMODEL_H_

#include "../../../containers/MapModelContainer.h"
#include "../../Model.h"

class BreakableModel{
public:
	BreakableModel();
	BreakableModel(int, bool, bool, int);
	virtual ~BreakableModel();
	
	int getType();
	bool getMirror();
	bool getCondition();
	int getIndex();
	Vertex* getCenter();
	Model* getModel();
	
	void breakModel();	
	void load();
	void draw(float, float, float);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & type;
		ar & mirror;
		ar & condition;
		ar & index;
	}
	
	Model* model;
	bool mirror, condition;
	int type, index;
	
};

#endif /*BREAKABLEMODEL_H_*/
