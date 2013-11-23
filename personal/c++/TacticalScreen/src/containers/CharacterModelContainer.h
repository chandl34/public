#ifndef CHARACTERMODELCONTAINER_H_
#define CHARACTERMODELCONTAINER_H_

#include "../models/CharacterModel.h"

class CharacterModelContainer{
public:
	CharacterModelContainer();
	virtual ~CharacterModelContainer();

	static CharacterModel* open(int, int, int);
	static void load();
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		for(size_t i = 0; i < 2; i++){
			for(size_t j = 0; j < 8; j++)
				ar & model[i][j];
		}
	}

	static vector<CharacterModel*>** model;
};

#endif /*CHARACTERMODELCONTAINER_H_*/
