#ifndef UNBREAKABLEMODEL_H_
#define UNBREAKABLEMODEL_H_

#include "../../../containers/MapModelContainer.h"
#include "../../Model.h"
	
class UnbreakableModel{
public:
	UnbreakableModel();
	UnbreakableModel(int, bool, int);
	virtual ~UnbreakableModel();
	
	int getType();
	bool getMirror();
	int getIndex();
	Vertex* getCenter();
	Model* getModel();
	
	void load();
	void draw(float, float, float);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & type;
		ar & mirror;
		ar & index;
	}
	
	Model* model;
	bool mirror;
	int type, index;
	
};

#endif /*UNBREAKABLEMODEL_H_*/
