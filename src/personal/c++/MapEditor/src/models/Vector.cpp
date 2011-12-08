#include "Vector.h"

Vector Vector::SUN = Vector(0.4f, -0.735f, -0.55f);

Vector::Vector(float x, float y, float z){
	coord = new float[3];
	coord[X] = x;
	coord[Y] = y;
	coord[Z] = z;
}

Vector::Vector(Vertex* v2, Vertex* v1){
	coord = new float[3];
	for(int i = 0; i < 3; i++)
		coord[i] = v2->get(i) - v1->get(i);
}

float Vector::dotProduct(Vector* v){
	return coord[X] * v->coord[X] + coord[Y] * v->coord[Y] + coord[Z] * v->coord[Z];
}

Vector* Vector::crossProduct(Vector* v){
	float x = coord[Y] * v->coord[Z] - coord[Z] * v->coord[Y];
	float y = coord[Z] * v->coord[X] - coord[X] * v->coord[Z];
	float z = coord[X] * v->coord[Y] - coord[Y] * v->coord[X];	
	return new Vector(x, y, z);
}

float Vector::magnitude(){
	return sqrt(coord[X] * coord[X] + coord[Y] * coord[Y] + coord[Z] * coord[Z]);
}

void Vector::normalize(){
	float m = magnitude();
	coord[X] /= m;
	coord[Y] /= m;
	coord[Z] /= m;
}

Vector* Vector::getNormal(Vector* v){
	Vector* normal = crossProduct(v);
	normal->normalize();
	return normal;
}

void Vector::draw(float x, float y, float z, Vertex* v){	
	glColor3f(0.5f, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(x + v->get(X), v->get(Y), z + v->get(Z));
	glVertex3f(x + v->get(X) + coord[X], y + v->get(Y) + coord[Y], z + v->get(Z) + coord[Z]);
	glEnd();
}

void Vector::rotateY(float s, float c){
	float x = coord[X];
	float z = coord[Z];	
	z = coord[X]*c + coord[Z]*s;
	x = coord[X]*s - coord[Z]*c;
	coord[X] = x;
	coord[Z] = z;
}

void Vector::mirror(){
	float tempX = coord[X];	
	coord[X] = -coord[Z];
	coord[Z] = -tempX;	
}
