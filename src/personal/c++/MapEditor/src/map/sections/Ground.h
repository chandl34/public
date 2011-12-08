#ifndef GROUND_H_
#define GROUND_H_

#include <boost/serialization/vector.hpp>
#include "../../models/types/mapModels/UnbreakableModel.h"

class Ground{
public:
	Ground();
	virtual ~Ground();

	void setGround(UnbreakableModel* m);
	void setGrass(UnbreakableModel* m);
	void addDebris(UnbreakableModel* m);
	void clear();
	
	void load();
	void draw(int, int);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & ground;
		ar & grass;
		ar & debris;
	}
	
	UnbreakableModel* ground;
	UnbreakableModel* grass;
	vector<UnbreakableModel*> debris;
	
};

#endif /*GROUND_H_*/
