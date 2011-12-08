#ifndef READER_H_
#define READER_H_

#include "../models/Model.h"

class Reader{
public:
	Reader(){}
	virtual ~Reader(){}
    static Model* readOBJ(const char*);
    
private:
	static void readModel();
	static void readShape();
	static void readHeader(){for(int i = 0; i < 4; i++) skipLine();}
	static void readVertices();
	static void readColor();
	static void readFaces();	
	
	static void skipLine(){file.ignore(999, '\n');}
	
    static ifstream file; 	
    static Model* model;	
    static Shape* shape;
    static Triangle* triangle;
    static float* coord;
    static float* color;
    static int* face;
    static float scale;
    
};

#endif /*READER_H_*/
