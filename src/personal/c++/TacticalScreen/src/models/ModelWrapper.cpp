#include "ModelWrapper.h"
#include "../world/World.h"

void ModelWrapper::loadRotateModel(int dir){
	model = Reader::readOBJ(filename.c_str());
	model->rotateY(World::getDir(dir)->getSin(), 
			World::getDir(dir)->getCos(), 0.5f, 0.5f);
	model->findCenter();
}
