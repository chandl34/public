#ifndef MODELWRAPPER_H_
#define MODELWRAPPER_H_

#include "../io/Reader.h"

class ModelWrapper{
public:
	ModelWrapper(){model = NULL;}
	ModelWrapper(const char* fn){model = NULL; filename = fn;}
	virtual ~ModelWrapper(){delete model;}

	void draw(float x, float y, float z){model->draw(x, y, z);}
	void draw(float x, float y, float z, bool dark){model->draw(x, y, z, dark);}

	void loadRotateModel(int);
	
	Model* getModel(){return model;}
		
private:
	friend class boost::serialization::access;

	template<class Archive>
	void serialize(Archive & ar, const unsigned int version){
		ar & filename;
	}
	
	Model* model;
	string filename;
	
};

#endif /*MODELWRAPPER_H_*/
