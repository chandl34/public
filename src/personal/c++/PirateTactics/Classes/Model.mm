/*
 *  Model.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Model.h"
#include "HitTest.h"


Model::Model(){	
	
}

Model::Model(const Model& s){
	GLshort i, j;
	//--- GENERAL ---//
	for(i = 0; i < s.tri.size(); i++)
		tri.push_back(new Triangle(*s.tri[i]));
	
	for(i = 0; i < s.vert.size(); i++)
		vert.push_back(new Vertex(*s.vert[i]));
	
	//--- ISO SORTING ---//	
	for(i = 0; i < 3; i++){	
		for(j = 0; j < 3; j++)
			range[i][j] = s.range[i][j];		
	}
	
	//--- PATHING ---//
	for(i = 0; i < s.block.size(); i++)
		block.push_back(s.block[i]);
}


Model::~Model(){
	GLshort i;
	//--- GENERAL ---//
	for(i = 0; i < tri.size(); i++)
		delete tri[i];
	
	for(i = 0; i < vert.size(); i++)
		delete vert[i];
}


//--- GENERAL ---//
void Model::addTriangle(GLshort f0, GLshort f1, GLshort f2){
	tri.push_back(new Triangle(f0, f1, f2));
}

void Model::addVertex(Vertex* v){
	vert.push_back(v);
}


//--- ISO SORTING ---//	
// This method assumes it is called after all Models are completely built
GLfloat Model::getRange(GLshort c, GLshort m) const{
	return range[c][m];
}

void Model::findRange(){
	GLshort i, j;		
	for(i = 0; i < 3; i++){
		range[i][MIN_C] = vert[0]->getLoc(i);
		range[i][MAX_C] = vert[0]->getLoc(i);
		for(j = 1; j < vert.size(); j++){
			range[i][MIN_C] = min(range[i][MIN_C], vert[j]->getLoc(i));
			range[i][MAX_C] = max(range[i][MAX_C], vert[j]->getLoc(i));
		}
		range[i][MID_C] = (range[i][MIN_C] + range[i][MAX_C])/2.0f;
	}
}


//-- HIT DETECTION --//
bool Model::detectHit(const Ray& r, const Vertex& o, GLfloat& t) const{
	for(GLshort i = 0; i < tri.size(); i++){
		if(rayInTriangle(r, 
						 *vert[tri[i]->getVert(0)], 
						 *vert[tri[i]->getVert(1)], 
						 *vert[tri[i]->getVert(2)], 
						 o, t))
			return true;
	}
	return false;
}


//--- MORPH ---//
void Model::flip(){
	GLshort i;
	for(i = 0; i < vert.size(); i++)
		vert[i]->flip();
	
	findRange();
		
	for(i = 0; i < block.size(); i++){
		switch(block[i]){
			case LEFT:
				block[i] = RIGHT;
				break;
			case RIGHT:
				block[i] = LEFT;
				break;
			case DOWN_LEFT:
				block[i] = DOWN_RIGHT;
				break;
			case DOWN_RIGHT:
				block[i] = DOWN_LEFT;
				break;
			case UP_LEFT:
				block[i] = UP_RIGHT;
				break;				
		}	
	}
}

void Model::shift(GLfloat x, GLfloat y){
	GLshort i;
	for(i = 0; i < vert.size(); i++)
		vert[i]->shift(x, y);
	
	findRange();
}

void Model::rotateZ(GLfloat t){
	GLshort i;
	for(i = 0; i < vert.size(); i++)
		vert[i]->rotateZ(t);
	
	findRange();
}


//--- PATHING ---//
bool Model::blocks(GLshort dir) const{
	if(block.size() == 0)
		return false;
	
	if(block[0] == ALL_DIR)
		return true;	
	
	for(GLshort i = 0; i < block.size(); i++){
		if(block[i] == dir)
			return true;
	}
	return false;
}

void Model::addBlockedDir(GLshort dir){
	block.push_back(dir);
}
