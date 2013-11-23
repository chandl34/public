#include "Reader.h"

ifstream Reader::file; 	
Model* Reader::model;	
Shape* Reader::shape;
Triangle* Reader::triangle;
float* Reader::coord;
float* Reader::color;
int* Reader::face;
float Reader::scale;
    
Model* Reader::readOBJ(const char* fileName){	
	file.open(fileName);
	if(file.fail()){
		cout << "Input file not found.  (" << fileName << ")" << endl;
		exit(-1);
	}
	
	scale = 0.1f;	
	face = new int[3];

	readModel();

	file.clear();
	file.close();

	delete [] face;
	return model;
}

void Reader::readModel(){
	model = new Model();
	while(true){
		readHeader();	
		if(file.eof())
			break;
		readShape();
	}
}

void Reader::readShape(){
	shape = new Shape;
	readVertices();
	readColor();
	readFaces();
	model->addShape(shape);
}

void Reader::readVertices(){
	char temp;	

	file >> temp;
	while(temp == 'v'){	
		coord = new float[3];
		for(int i = 0; i < 3; i++){
			file >> coord[i];
			coord[i] *= scale;
		}
		shape->addVertex(new Vertex(coord));
		file >> temp;
	}
	skipLine();
}

void Reader::readColor(){	
	color = new float[3];
	char temp;
	int c;

	for(int i = 0; i < 3; i++){
		file >> temp;
		file >> c;
		color[i] = c/255.0f;
	}	
	shape->setColor(color);
}

void Reader::readFaces(){
	char temp;	
	int v;

	file >> temp;
	while(temp == 'f'){
		file >> temp;
		for(int i = 0; i < 3; i++){
			file >> v;	
			file >> temp;
			face[i] = v;			
		}
		triangle = new Triangle(shape->getVertex(shape->getVertexCount() - face[0]), 
				shape->getVertex(shape->getVertexCount() - face[1]), 
				shape->getVertex(shape->getVertexCount() - face[2]), color);
		shape->addTriangle(triangle);
	}	
	skipLine();
}

