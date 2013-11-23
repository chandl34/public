#ifndef MODEL_H_
#define MODEL_H_

#include "Shape.h"

class Model{
public:
	Model(){}
	virtual ~Model();
	
	Shape* getShape(int i){return sh.at(i);}
	size_t getShapeCount(){return sh.size();}
	Vertex* getCenter(){return center;}
	
	void addShape(Shape* s){sh.push_back(s);}
	
	void draw(float, float, float);

	void rotateY(float, float, float, float);
	void mirror();
	void invert();
	void shift();
	void angle(bool, bool, bool, int, Vertex*);
	
	void findCenter();
	
private:
	vector<Shape*> sh;
	Vertex* center;
	
};

#endif /*MODEL_H_*/
