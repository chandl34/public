/*
 *  EstimateDisplayLS.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef ESTIMATE_DISPLAY_T_S_H_
#define ESTIMATE_DISPLAY_T_S_H_

#include "StatDisplay.h"

class Unit;


class EstimateDisplayLS : public StatDisplay<Unit>{
public:
	EstimateDisplayLS(GLshort, GLshort, GLshort);
	
	//--- GENERAL ---//	
	void update(Unit*);
	
	//---- DRAW ----//
	void draw(bool);
	
private:
	//--- GENERAL ---//
	GLshort _prevEst;
	GLshort _prevTU;
};

#endif