#ifndef READER_H_
#define READER_H_

#include "../models/Model.h"

class Reader{
public:
	Reader(){}
	virtual ~Reader(){}
    Model* readOBJ(const char*);
    
private:
	void readModel();
	void readShape();
	void readHeader(){for(int i = 0; i < 4; i++) skipLine();}
	void readVertices();
	void readColor();
	void readFaces();	
	
	void skipLine(){file.ignore(999, '\n');}
	
    ifstream file; 	
	Model* model;	
	Shape* shape;
	Triangle* triangle;
	float* coord;
	float* color;
	int* face;
	float scale;
    
};

#endif /*READER_H_*/
