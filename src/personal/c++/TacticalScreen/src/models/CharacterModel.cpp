#include "CharacterModel.h"

CharacterModel::CharacterModel(){
	model = new ModelWrapper*[8];
}

CharacterModel::~CharacterModel(){
	for(int i = 0; i < 8; i++)
		delete model[i];
	delete [] model;
}

ModelWrapper* CharacterModel::getModelWrapper(int i){return model[i];}

void CharacterModel::loadRotateModel(int dir){
	for(int i = 0; i < 8; i++)
		model[i]->loadRotateModel(dir);
}
