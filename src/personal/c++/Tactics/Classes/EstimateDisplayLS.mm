/*
 *  EstimateDisplayLS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "EstimateDisplayLS.h"

#include "Unit.h"

#include "String.h"


EstimateDisplayLS::EstimateDisplayLS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Unit>(lx, rx, ty){
	_text.push_back(TextLine());
	_text[0].addString(" ", Coord2d<double>(_centerX, _topY), CENTERED);
}


void EstimateDisplayLS::update(Unit* sUnit){
	GLshort est = sUnit->getEstimateTU();	
	if(est != _prevEst)
		_text[0].setString(numToString(est, 3));
	
	_prevEst = est;
	_prevTU = sUnit->getTU();
}

//---- DRAW ----//
void EstimateDisplayLS::draw(bool step){
	if(_prevEst > 0){
		if(_prevEst > _prevTU)
			glColor4f(1.0f, 0.0f, 0.0f, 1.0f);		
		StatDisplay<Unit>::draw(step);		
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);		
	}
}