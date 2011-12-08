#ifndef VECTOR_H_
#define VECTOR_H_

#include "Vertex.h"

class Vector{
public:
	Vector(float, float, float);
	Vector(Vertex*, Vertex*);
	virtual ~Vector(){delete [] coord;}

	float get(int c){return coord[c];}
	void set(int c, float v){coord[c] = v;}
	void set(float x, float y, float z){coord[X] = x; coord[Y] = y; coord[Z] = z;}
	
	float dotProduct(Vector*);
	Vector* crossProduct(Vector*);
	float magnitude();
	void normalize();
	Vector* getNormal(Vector*);

	void draw(float, float, float, Vertex*);

	void rotateY(float, float);
	void mirror();
	void invert(){coord[Z] = -coord[Z];}
	
	static Vector SUN;
		
private:	
	float* coord;
	
};

#endif /*VECTOR_H_*/
