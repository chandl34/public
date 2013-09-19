/*
 *  ModelStorage.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/18/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "ModelStorage.h"

#include "Model.h"

#include "Model.h"


Model* ModelStorage::constModel[CONST_MODELS]; 
Model* ModelStorage::sideModel[SIDE_MODELS][2]; 	
Model* ModelStorage::rotateModel[ROTATE_MODELS][STANCES][PATH_DIRS]; 
Model* ModelStorage::doorModel[DOOR_MODELS][2][2][2][2]; 	


ModelStorage::~ModelStorage(){	
	GLshort i, j, k, l, m;
	for(i = 0; i < CONST_MODELS; ++i)
		delete constModel[i];
	
	for(i = 0; i < SIDE_MODELS; ++i){
		for(j = 0; j < 2; ++j)
			delete sideModel[i][j];
	}
	
	for(i = 0; i < ROTATE_MODELS; ++i){
		for(j = 0; i < STANCES; ++j){
			for(k = 0; k < PATH_DIRS; ++k)
				delete rotateModel[i][j][k];
		}
	}
	
	for(i = 0; i < DOOR_MODELS; ++i){
		for(j = 0; j < 2; ++j){				// side 
			for(k = 0; k < 2; ++k){			// open
				for(l = 0; l < 2; ++l){		// inner
					for(m = 0; m < 2; ++m)	// hinge
						delete doorModel[i][j][k][l][m];
				}
			}
		}
	}
}


// ConstObject
Model* ModelStorage::getConstModel(const ObjType& ot){
	return constModel[ot];
}

void ModelStorage::setConstModel(const ObjType& ot, Model* m){
	constModel[ot] = m;
}


// SideObject
Model* ModelStorage::getSideModel(const ObjType& ot, const Side& si){
	return sideModel[ot][si];
}

void ModelStorage::setSideModel(const ObjType& ot, Model* m){
	sideModel[ot][0] = m;
	sideModel[ot][1] = new Model(*m);
	sideModel[ot][1]->flip();
}


// RotateObject
Model* ModelStorage::getRotateModel(const ObjType& ot, bool alt, const Dir& dir){
	return rotateModel[ot][alt][dir];
}

void ModelStorage::setRotateModel(const ObjType& ot, bool alt, Model* m){
	rotateModel[ot][alt][0] = m;
	
	//	cout << "0:  (" << m->getRelativeLoc(X, Dimension(MINIMUM)) << ", " << m->getRelativeLoc(X, Dimension(MAXIMUM)) << ")" << endl;
	//	cout << "0:  (" << m->getRelativeLoc(Y, Dimension(MINIMUM)) << ", " << m->getRelativeLoc(Y, Dimension(MAXIMUM)) << ")" << endl << endl;
	///*
	Model* tm;
	double shX, shY;
	for(GLshort i = 1; i < PATH_DIRS; ++i){
		tm = new Model(*m);
		shX = tm->getRelativeLoc(X, Dimension(MIDDLE));
		shY = tm->getRelativeLoc(Y, Dimension(MIDDLE));		
		tm->shift(-shX, -shY);	
		tm->rotateZ(M_PI_4 * i);
		tm->shift(shX, shY);
		rotateModel[ot][alt][i] = tm;
		
		//	cout << i << ":  (" << tm->getRelativeLoc(X, Dimension(MINIMUM)) << ", " << tm->getRelativeLoc(X, Dimension(MAXIMUM)) << ")" << endl;
		//	cout << i << ":  (" << tm->getRelativeLoc(Y, Dimension(MINIMUM)) << ", " << tm->getRelativeLoc(Y, Dimension(MAXIMUM)) << ")" << endl << endl;
	}
	// */
}


// DoorObject
Model* ModelStorage::getDoorModel(const ObjType& ot, const Side& si, const Inner& inn, const Hinge& hin, const Open& op){
	return doorModel[ot][si][inn][hin][op];
}

void ModelStorage::setDoorModel(const ObjType& ot, Model* m){
	Model* tm;
	double shX, shY;
	
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
	shX = tm->getRelativeLoc(X, Dimension(MINIMUM));
	shY = tm->getRelativeLoc(Y, Dimension(MINIMUM));	
	tm->shift(-shX, -shY);
	tm->rotateZ(-M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(DOWN);
	tm->addBlockedDir(RIGHT);
	tm->addBlockedDir(DOWN_RIGHT);
	doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][OPEN] = tm;				// 3  (0, 0, 1, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1);
	doorModel[ot][RIGHT_SIDE][OUTER][LEFT_HINGE][OPEN] = tm;				// 4  (1, 0, 1, 1)
	
	
	// MIN_X, MAX_Y HINGE
	tm = new Model(*doorModel[ot][LEFT_SIDE][OUTER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][LEFT_SIDE][OUTER][LEFT_HINGE][CLOSED] = tm;				// 5  (0, 0, 0, 0)
	
	tm = new Model(*doorModel[ot][RIGHT_SIDE][OUTER][RIGHT_HINGE][CLOSED]);	
	doorModel[ot][RIGHT_SIDE][OUTER][LEFT_HINGE][CLOSED] = tm;				// 6  (1, 0, 0, 0)
	
	tm = new Model(*m);
	shX = tm->getRelativeLoc(X, Dimension(MINIMUM));
	shY = tm->getRelativeLoc(Y, Dimension(MAXIMUM));	
	tm->shift(-shX, -shY);
	tm->rotateZ(M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(UP);
	tm->addBlockedDir(LEFT);
	tm->addBlockedDir(UP_LEFT);
	doorModel[ot][LEFT_SIDE][OUTER][LEFT_HINGE][OPEN] = tm;					// 7  (0, 0, 0, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1);
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
	shX = tm->getRelativeLoc(X, Dimension(MAXIMUM));
	shY = tm->getRelativeLoc(Y, Dimension(MINIMUM));	
	tm->shift(-shX, -shY);
	tm->rotateZ(M_PI_2);
	tm->shift(shX, shY);
	tm->addBlockedDir(DOWN);
	tm->addBlockedDir(RIGHT);
	tm->addBlockedDir(DOWN_RIGHT);
	doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][OPEN] = tm;				// 11  (0, 1, 1, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1);
	doorModel[ot][RIGHT_SIDE][INNER][LEFT_HINGE][OPEN] = tm;				// 12  (1, 1, 1, 1)
	
	
	
	// MAX_X, MAX_Y HINGE
	tm = new Model(*doorModel[ot][LEFT_SIDE][INNER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][LEFT_SIDE][INNER][LEFT_HINGE][CLOSED] = tm;				// 12  (0, 1, 0, 0)
	
	tm = new Model(*doorModel[ot][RIGHT_SIDE][INNER][RIGHT_HINGE][CLOSED]);
	doorModel[ot][RIGHT_SIDE][INNER][LEFT_HINGE][CLOSED] = tm;				// 13  (1, 1, 0, 0)
	
	tm = new Model(*m);	
	tm->shift(2, 0);
	shX = tm->getRelativeLoc(X, Dimension(MAXIMUM));
	shY = tm->getRelativeLoc(Y, Dimension(MAXIMUM));	
	tm->shift(-shX, -shY);
	tm->rotateZ(-M_PI_2);
	tm->shift(shX, shY);	
	tm->addBlockedDir(UP);
	tm->addBlockedDir(LEFT);
	tm->addBlockedDir(UP_LEFT);
	doorModel[ot][LEFT_SIDE][INNER][LEFT_HINGE][OPEN] = tm;					// 14  (0, 1, 0, 1)
	
	tm = new Model(*tm);
	tm->flip();
	//tm->shift(0, 0.1);
	doorModel[ot][RIGHT_SIDE][INNER][RIGHT_HINGE][OPEN] = tm;				// 15  (1, 1, 0, 1)
	
	
	delete m;	// Clear memory, since this is never aliased
}
