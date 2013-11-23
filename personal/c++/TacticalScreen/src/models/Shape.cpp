#include "Shape.h"

Shape::~Shape(){
	for(size_t i = 0; i < vert.size(); i++)
		delete vert.at(i);
	for(size_t i = 0; i < tri.size(); i++)
		delete tri.at(i);
	delete [] color;
}

void Shape::draw(float x, float y, float z){
	for(size_t i = 0; i < tri.size(); i++){
		if(tri.at(i)->getShade() > 0)
			tri.at(i)->draw(x, y, z);		
	}
}

void Shape::draw(float x, float y, float z, bool dark){
	for(size_t i = 0; i < tri.size(); i++){
		if(tri.at(i)->getShade() > 0)
			tri.at(i)->draw(x, y, z, dark);		
	}
}

void Shape::rotateY(float s, float c, float centX, float centZ){
	for(size_t i = 0; i < tri.size(); i++)
		tri.at(i)->rotateY(s, c);
	for(size_t i = 0; i < vert.size(); i++)
		vert.at(i)->rotateY(s, c, centX, centZ);	
}

void Shape::mirror(){
	for(size_t i = 0; i < tri.size(); i++)
		tri.at(i)->mirror();
	for(size_t i = 0; i < vert.size(); i++)
		vert.at(i)->mirror();		
}

void Shape::invert(){
	for(size_t i = 0; i < tri.size(); i++)
		tri.at(i)->invert();
	for(size_t i = 0; i < vert.size(); i++)
		vert.at(i)->invert();		
}

void Shape::shift(){
	for(size_t i = 0; i < vert.size(); i++)
		vert.at(i)->shift();		
}

float Shape::findAverage(int c){
	float a = 0;
	for(size_t i = 0; i < vert.size(); i++)
		a += vert.at(i)->get(c);
	a /= vert.size();
	return a;		
}
