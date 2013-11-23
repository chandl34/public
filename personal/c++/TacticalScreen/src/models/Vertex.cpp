#include "Vertex.h"

Vertex::Vertex(float x, float y, float z){
	coord = new float[3];
	coord[X] = x;
	coord[Y] = y;
	coord[Z] = z;
}

void Vertex::rotateY(float s, float c, float centX, float centZ){
	coord[X] -= centX;
	coord[Z] -= centZ;
	float x = coord[X];
	float z = coord[Z];	
	z = coord[X]*c + coord[Z]*s;
	x = coord[X]*s - coord[Z]*c;
	coord[X] = x + centX;
	coord[Z] = z + centZ;
}

void Vertex::mirror(){
	float tempX = coord[X];	
	coord[X] = 1 - coord[Z];
	coord[Z] = 1 - tempX;	
}
