/*
 *  ModelContainer.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ModelContainer.h"
#include "ImageContainer.h"


// ConstObject
vector<Image*> ModelContainer::constImage[CONST_MODELS];
Model* ModelContainer::constModel[CONST_MODELS]; 

// SideObject
vector<Image*> ModelContainer::sideImage[SIDE_MODELS][2];
Model* ModelContainer::sideModel[SIDE_MODELS][2]; 	

// RotateObject
vector<Image*> ModelContainer::rotateImage[ROTATE_MODELS][PATH_DIRS];
Model* ModelContainer::rotateModel[ROTATE_MODELS][PATH_DIRS]; 

// DoorObject
vector<Image*> ModelContainer::doorImage[DOOR_MODELS][2][2][2][2];
Model* ModelContainer::doorModel[DOOR_MODELS][2][2][2][2]; 	


ModelContainer::ModelContainer(){

}

ModelContainer::~ModelContainer(){	
	GLshort i, j, k, l, m;
	for(i = 0; i < CONST_MODELS; i++)
		delete constModel[i];
	
	for(i = 0; i < SIDE_MODELS; i++){
		for(j = 0; j < 2; j++)
			delete sideModel[i][j];
	}
	
	for(i = 0; i < ROTATE_MODELS; i++){
		for(j = 0; j < PATH_DIRS; j++)
			delete rotateModel[i][j];
	}
	
	for(i = 0; i < DOOR_MODELS; i++){
		for(j = 0; j < 2; j++){				// side 
			for(k = 0; k < 2; k++){			// open
				for(l = 0; l < 2; l++){		// inner
					for(m = 0; m < 2; m++)	// hinge
						delete doorModel[i][j][k][l][m];
				}
			}
		}
	}
}


// ConstObject
Image* ModelContainer::getConstImage(GLshort ot, GLshort is){
	return constImage[ot][is];
}

Model* ModelContainer::getConstModel(GLshort ot){
	return constModel[ot];
}

void ModelContainer::addConstImage(GLshort ot, Image* img){
	ImageContainer::addImage(img);
	constImage[ot].push_back(img);
}

void ModelContainer::setConstModel(GLshort ot, Model* m){
	constModel[ot] = m;
}


// SideObject
Image* ModelContainer::getSideImage(GLshort ot, GLshort flip, GLshort is){
	return sideImage[ot][flip][is];
}

Model* ModelContainer::getSideModel(GLshort ot, GLshort flip){
	return sideModel[ot][flip];
}

void ModelContainer::addSideImage(GLshort ot, GLshort flip, Image* img){
	ImageContainer::addImage(img);
	sideImage[ot][flip].push_back(img);
}

void ModelContainer::setSideModel(GLshort ot, Model* m){
	sideModel[ot][0] = m;
	sideModel[ot][1] = new Model(*m);
	sideModel[ot][1]->flip();
}


// RotateObject
Image* ModelContainer::getRotateImage(GLshort ot, GLshort rot, GLshort is){
	return rotateImage[ot][rot][is];
}

Model* ModelContainer::getRotateModel(GLshort ot, GLshort rot){
	return rotateModel[ot][rot];
}

void ModelContainer::addRotateImage(GLshort ot, GLshort rot, Image* img){
	ImageContainer::addImage(img);
	rotateImage[ot][rot].push_back(img);
}
void ModelContainer::setRotateModel(GLshort ot, Model* m){	
	rotateModel[ot][0] = m;
	
	//	cout << "(" << m->getRange(X, MIN_C) << ", " << m->getRange(X, MAX_C) << ")" << endl;
	//	cout << "(" << m->getRange(Y, MIN_C) << ", " << m->getRange(Y, MAX_C) << ")" << endl << endl;
	
	//	GLfloat shX, shY;
	for(GLshort i = 1; i < PATH_DIRS; i++){
		rotateModel[ot][i] = new Model(*m);	
		/*
		 shX = tm->getRange(X, MID_C);
		 shY = tm->getRange(Y, MID_C);		
		 tm->shift(-shX, -shY);		
		 tm->rotateZ(M_PI_4);
		 tm->shift(shX, shY);
		 model[ot][i] = tm;
		 
		 cout << "(" << tm->getRange(X, MIN_C) << ", " << tm->getRange(X, MAX_C) << ")" << endl;
		 cout << "(" << tm->getRange(Y, MIN_C) << ", " << tm->getRange(Y, MAX_C) << ")" << endl << endl;
		 */
	}
}


// DoorObject
Image* ModelContainer::getDoorImage(GLshort ot, GLshort si, GLshort inn, GLshort hin, GLshort op, GLshort is){
	return doorImage[ot][si][inn][hin][op][is];
}

Model* ModelContainer::getDoorModel(GLshort ot, GLshort si, GLshort inn, GLshort hin, GLshort op){
	return doorModel[ot][si][inn][hin][op];
}

void ModelContainer::addDoorImage(GLshort ot, GLshort si, GLshort inn, GLshort hin, GLshort op, Image* img){
	ImageContainer::addImage(img);
	doorImage[ot][si][inn][hin][op].push_back(img);
}

void ModelContainer::setDoorModel(GLshort ot, Model* m){
	Model* tm;
	GLfloat shX, shY;
	
	// MIN_X, MIN_Y HINGE
	tm = new Model(*m);
	tm->addBlockedDir(DOWN);
	tm->addBlockedDir(LEFT);
	tm->addBlockedDir(DOWN_LEFT);
	doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][CLOSED] = tm;				// 1  (0, 0, 1, 0)
	
	tm = new Model(*tm);
	tm->flip();
	doorModel[ot][RIGHT_SIDE][OUTER][RIGHT_HINGE][CLOSED] = tm;				// 2  (1, 0, 1, 0)	
	
	tm = new Model(*m);
	shX = tm->getRange(X, MIN_C);
	shY = tm->getRange(Y, MIN_C);	
	tm->shift(-shX, -shY);
	tm->rotateZ(-M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(DOWN);
	tm->addBlockedDir(RIGHT);
	tm->addBlockedDir(DOWN_RIGHT);
	doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][OPEN] = tm;				// 3  (0, 0, 1, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1f);
	doorModel[ot][RIGHT_SIDE][OUTER][LEFT_HINGE][OPEN] = tm;				// 4  (1, 0, 1, 1)
	
	
	// MIN_X, MAX_Y HINGE
	tm = new Model(*doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][LEFT_SIDE][OUTER][LEFT_HINGE][CLOSED] = tm;				// 5  (0, 0, 0, 0)
	
	tm = new Model(*doorModel[ot][RIGHT_SIDE][OUTER][RIGHT_HINGE][CLOSED]);	
	doorModel[ot][RIGHT_SIDE][OUTER][LEFT_HINGE][CLOSED] = tm;				// 6  (1, 0, 0, 0)
	
	tm = new Model(*m);
	shX = tm->getRange(X, MIN_C);
	shY = tm->getRange(Y, MAX_C);	
	tm->shift(-shX, -shY);
	tm->rotateZ(M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(UP);
	tm->addBlockedDir(LEFT);
	tm->addBlockedDir(UP_LEFT);
	doorModel[ot][LEFT_SIDE][OUTER][LEFT_HINGE][OPEN] = tm;					// 7  (0, 0, 0, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1f);
	doorModel[ot][RIGHT_SIDE][OUTER][RIGHT_HINGE][OPEN] = tm;				// 8  (1, 0, 0, 1)	
	
	// MAX_X, MIN_Y HINGE
	tm = new Model(*doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][CLOSED]);
	tm->shift(2, 0);
	doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][CLOSED] = tm;				// 9  (0, 1, 1, 0)
	
	tm = new Model(*doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][CLOSED]);
	tm->flip();
	doorModel[ot][RIGHT_SIDE][INNER][RIGHT_HINGE][CLOSED] = tm;				// 10  (1, 1, 1, 0)
	
	tm = new Model(*m);	
	tm->shift(2, 0);
	shX = tm->getRange(X, MAX_C);
	shY = tm->getRange(Y, MIN_C);	
	tm->shift(-shX, -shY);
	tm->rotateZ(M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(DOWN);
	tm->addBlockedDir(RIGHT);
	tm->addBlockedDir(DOWN_RIGHT);
	doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][OPEN] = tm;				// 11  (0, 1, 1, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1f);
	doorModel[ot][RIGHT_SIDE][INNER][LEFT_HINGE][OPEN] = tm;				// 12  (1, 1, 1, 1)
	
	
	
	// MAX_X, MAX_Y HINGE
	tm = new Model(*doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][LEFT_SIDE][INNER][LEFT_HINGE][CLOSED] = tm;				// 12  (0, 1, 0, 0)
	
	tm = new Model(*doorModel[ot][RIGHT_SIDE][INNER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][RIGHT_SIDE][INNER][LEFT_HINGE][CLOSED] = tm;				// 13  (1, 1, 0, 0)
	
	tm = new Model(*m);	
	tm->shift(2, 0);
	shX = tm->getRange(X, MAX_C);
	shY = tm->getRange(Y, MAX_C);	
	tm->shift(-shX, -shY);
	tm->rotateZ(-M_PI_2);
	tm->shift(shX, shY);	
	tm->addBlockedDir(UP);
	tm->addBlockedDir(LEFT);
	tm->addBlockedDir(UP_LEFT);
	doorModel[ot][LEFT_SIDE][INNER][LEFT_HINGE][OPEN] = tm;					// 14  (0, 1, 0, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1f);
	doorModel[ot][RIGHT_SIDE][INNER][RIGHT_HINGE][OPEN] = tm;				// 15  (1, 1, 0, 1)
	
	
	delete m;	// Clear memory, since this is never aliased
}
