/*
 *  ModelIO.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ModelIO.h"

#include "Model.h"


void skipLine(ifstream* file){
	file->ignore(999, '\n');
}

void skipHeader(ifstream* file){
	for(GLshort i = 0; i < 4; ++i) 
		skipLine(file);
}

void readVertices(ifstream* file, Model* s){
	char temp;	
	double coord[3];
	
	*file >> temp;
	while(temp == 'v'){	
		for(GLshort i = 0; i < 3; ++i)
			*file >> coord[i];
		s->addVertex(coord[X], coord[Y], coord[Z]);
		*file >> temp;
	}
}

void readFaces(ifstream* file, Model* s){
	GLshort face[3];
	char temp;	
	
	*file >> temp;
	while(temp == 'f'){
		for(GLshort i = 0; i < 3; ++i)
			*file >> face[i];
			s->addTriangle(face[0] - 1, face[1] - 1, face[2] - 1);
		*file >> temp;
	}	
}

void readShape(ifstream* file, Model* m){	
	readVertices(file, m);
	skipLine(file);		// Skip # verts
	skipLine(file);		// Skip blank line
	skipLine(file);		// Skip object name
	
	readFaces(file, m);
	skipLine(file);		// Skip # faces
}

Model* loadOBJ(const char* filename){
	printf("Loading %s.obj...\n", filename);
	string fn = "../../Models/";
	fn += filename;
	fn += ".obj";
	
	//char * dir = getcwd(NULL, 0); // Platform-dependent, see reference link below    
	//printf("Current dir: %s", dir);
	
	ifstream file;
	file.open(fn.c_str());
	//file.open("test.rtf");
	
	if(file.fail()){
		printf("Failed to load %s.obj!\n", filename);
		return NULL;
	}
	
	Model* m = new Model();
	
	while(true){
		skipHeader(&file);	
		if(file.eof())
			break;		
		readShape(&file, m);
	}	
	
	file.close();
	return m;
}
