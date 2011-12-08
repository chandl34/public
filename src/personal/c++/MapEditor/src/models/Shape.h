#ifndef SHAPE_H_
#define SHAPE_H_

#include <boost/serialization/vector.hpp>
#include "Triangle.h"

class Shape{
public:
	Shape(){}
	virtual ~Shape();
	
	Vertex* getVertex(int i){return vert[i];}
	size_t getVertexCount(){return vert.size();}
	Triangle* getTriangle(int i){return tri[i];}
	size_t getTriangleCount(){return tri.size();}
	float* getColor(){return color;}
	
	void addVertex(Vertex* v){vert.push_back(v);}
	void addTriangle(Triangle* t){tri.push_back(t);}
	void setColor(float* f){color = f;}
	
	void draw(float, float, float);	

	void rotateY(float, float, float, float);
	void mirror();
	void invert();
	void shift();

	float findAverage(int);
	
private:
	vector<Vertex*> vert;
	vector<Triangle*> tri;
	float* color;
	
};

#endif /*SHAPE_H_*/
