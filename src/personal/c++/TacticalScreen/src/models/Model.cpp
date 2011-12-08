#include "Model.h"

Model::Model(){
	center = NULL;
}

Model::~Model(){
	for(size_t i = 0; i < sh.size(); i++)
		delete sh.at(i);
	delete center;
}

void Model::draw(float x, float y, float z){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->draw(x, y, z);
}

void Model::draw(float x, float y, float z, bool dark){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->draw(x, y, z, dark);
}

void Model::rotateY(float s, float c, float centX, float centZ){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->rotateY(s, c, centX, centZ);	
}

void Model::mirror(){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->mirror();
}

void Model::invert(){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->invert();
}

void Model::shift(){
	for(size_t i = 0; i < sh.size(); i++)
		sh.at(i)->shift();
}

void Model::angle(bool m, bool s, bool i, int a, Vertex* v){
	int temp = m + s + i;
	if(temp == 1 || temp == 3) // CCW
		temp = -1;
	else					   // CW
		temp = 1;
	if(a == HALFOPEN)
		rotateY(M_PI_4, M_PI_4*temp, v->get(X), v->get(Z));
	else
		rotateY(0, temp, v->get(X), v->get(Z));
}

void Model::findCenter(){
	float x = 0, y = 0, z = 0;
	for(size_t i = 0; i < sh.size(); i++){
		x += sh.at(i)->findAverage(X);
		y += sh.at(i)->findAverage(Y);
		z += sh.at(i)->findAverage(Z);
	}
	x /= sh.size();
	y /= sh.size();
	z /= sh.size();
	
	center = new Vertex(x, y, z);
}
