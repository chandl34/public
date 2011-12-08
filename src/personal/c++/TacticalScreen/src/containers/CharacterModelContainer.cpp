#include "CharacterModelContainer.h"

vector<CharacterModel*>** CharacterModelContainer::model;

CharacterModelContainer::CharacterModelContainer(){
	model = new vector<CharacterModel*>*[2];        // Male/Female	
	for(size_t i = 0; i < 2; i++)
		model[i] = new vector<CharacterModel*>[8];
}

CharacterModelContainer::~CharacterModelContainer(){
	for(size_t i = 0; i < 2; i++){
		for(size_t j = 0; j < 8; j++){
			for(size_t k = 0; k < model[i][j].size(); k++)
				delete model[i][j].at(k);
		}
		delete [] model[i];
	}
	delete [] model;	
}

void CharacterModelContainer::load(){
	for(size_t i = 0; i < 2; i++){
		for(size_t j = 0; j < 8; j++){	
			for(size_t k = 0; k < model[i][j].size(); k++)
				model[i][j].at(k)->loadRotateModel(j);
		}
	}
}

CharacterModel* CharacterModelContainer::open(int gender, int dir, int i){
	if(model[gender][dir].size() == 0)
		return NULL;
	return model[gender][dir].at(i);
}
