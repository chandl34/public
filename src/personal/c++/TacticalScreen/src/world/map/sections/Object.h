#ifndef OBJECT_H_
#define OBJECT_H_

#include "../../../models/types/mapModels/BreakableModel.h"

class Object{
public:
	Object();
	virtual ~Object();
	void load();
	
	bool accessible();
	bool jumpable();
	bool jumpable(int);
	
	BreakableModel* getModel();
	
	void draw(int, int, int, int);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & object;
	}
	
	BreakableModel* object;	
	
};

#endif /*OBJECT_H_*/
