#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vector.h"

class Triangle{	
public:
	Triangle(Vertex*, Vertex*, Vertex*, float*);
	virtual ~Triangle(){delete [] vert; delete normal;}
	
	Vertex* get(int a){return vert[a];}
	float* getColor(){return color;}
	float getShade(){return -normal->dotProduct(&Vector::SUN);}
	
	void draw(float, float, float);
	void draw(float, float, float, bool);

	void rotateY(float, float);
	void mirror();
	void invert();
	
	enum{R, G, B};

private:	
	Vertex** vert;
	Vector* normal;
	float* color;
	float light;
	static const float dark = 0.6f;
	
};

#endif /*TRIANGLE_H_*/
