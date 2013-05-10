/*
 *  Model.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Model.h"

#include "Hit.h"
#include "Ray.h"
#include "Vector.h"

#include "HitTest.h"
#include "Math.h"


Model::Model(){
	dimensionsKnown = false;
}

// Special copy constructor needed, since Triangles use pointers
Model::Model(const Model& m){
	GLshort i, j;
	
	//--- GENERAL ---//
	vert = m.vert; 
	
	for(i = 0; i < m.tri.size(); ++i)
		tri.push_back(IndexedTriangle(m.tri[i], &vert));
	
	//--- ISO SORTING ---//	
	for(i = 0; i < 3; ++i){
		for(j = 0; j < 3; ++j)
			loc[i][j] = m.loc[i][j];
	}
	
	dimensionsKnown = m.dimensionsKnown;
	
	//--- PATHING ---//
	block = m.block;	
}


//--- GENERAL ---//
void Model::addVertex(double x, double y, double z){
	vert.push_back(Vertex(x, y, z));
}

void Model::addTriangle(GLshort v0, GLshort v1, GLshort v2){
	tri.push_back(IndexedTriangle(v0, v1, v2, &vert));
}

//--- ISO SORTING ---//	
void Model::findDimensions(){
	set<double> vertd[3];
	for(GLshort i = 0; i < vert.size(); ++i){
		vertd[X].insert(vert[i].getLoc(X));
		vertd[Z].insert(vert[i].getLoc(Z));
	}
	
	loc[X][MINIMUM] = *vertd[X].begin();
	loc[X][MAXIMUM] = *vertd[X].rbegin();
	
	loc[Z][MINIMUM] = *vertd[Z].begin();
	loc[Z][MAXIMUM] = *vertd[Z].rbegin();
	
	for(GLshort i = 0; i < vert.size(); ++i){
		if(compare(vert[i].getLoc(X), loc[X][MINIMUM]) == 0)
			vertd[Y].insert(vert[i].getLoc(Y));
	}
	
	loc[Y][MINIMUM] = *vertd[Y].begin();
	loc[Y][MAXIMUM] = *vertd[Y].rbegin();
	
	for(GLshort i = 0; i < 3; ++i)
		loc[i][MIDDLE] = (loc[i][MINIMUM] + loc[i][MAXIMUM]) / 2.0;
	
	dimensionsKnown = true;
}

// This method assumes it is called after all Models are completely built
double Model::getRelativeLoc(GLshort c, const Dimension& m){
	if(!dimensionsKnown)
		findDimensions();
	return loc[c][m];
}


//-- HIT DETECTION --//
bool Model::detectHit(const Ray& r, const Vertex& o, Hit& hit) const{
	for(GLshort i = 0; i < tri.size(); ++i){		
		if(rayInTri(r, tri[i], o, hit))
			return true;
	}
	return false;
}


//--- MORPH ---//
void Model::flip(){
	GLshort i;
	for(i = 0; i < vert.size(); ++i)
		vert[i].flip();
	
	for(i = 0; i < tri.size(); ++i)
		tri[i].flip();
	
	dimensionsKnown = false;
		
	for(i = 0; i < block.size(); ++i){
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

void Model::shift(double x, double y, double z){
	GLshort i;
	for(i = 0; i < vert.size(); ++i)
		vert[i].shift(x, y, z);
	
	dimensionsKnown = false;
}

void Model::rotateX(double xRot){
	GLshort i;
	for(i = 0; i < vert.size(); ++i)
		vert[i].rotateX(xRot);
	
	dimensionsKnown = false;
}

void Model::rotateY(double yRot){
	GLshort i;
	for(i = 0; i < vert.size(); ++i)
		vert[i].rotateY(yRot);
	
	dimensionsKnown = false;
}

void Model::rotateZ(double zRot){
	GLshort i;
	for(i = 0; i < vert.size(); ++i)
		vert[i].rotateZ(zRot);
	
	dimensionsKnown = false;
}


//--- PATHING ---//
bool Model::blocks(GLshort dir) const{
	if(block.size() == 0)
		return false;
	
	if(block[0] == ALL_DIR)
		return true;	
	
	for(GLshort i = 0; i < block.size(); ++i){
		if(block[i] == dir)
			return true;
	}
	return false;
}

void Model::addBlockedDir(GLshort dir){
	block.push_back(dir);
}
