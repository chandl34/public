#ifndef CHARACTERMODEL_H_
#define CHARACTERMODEL_H_

#include "../models/ModelWrapper.h"

class CharacterModel{
public:
	CharacterModel();
	virtual ~CharacterModel();

	ModelWrapper* getModelWrapper(int);
	void loadRotateModel(int);
	
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		for(int i = 0; i < 8; i++)
			ar & model[i];
	}
	
	ModelWrapper** model;
};

#endif /*CHARACTERMODEL_H_*/
