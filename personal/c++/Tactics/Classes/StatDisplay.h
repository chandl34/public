/*
 *  StatDisplay.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/9/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef STAT_DISPLAY_H_
#define STAT_DISPLAY_H_

#include "Drawable.h"

#include "TextLine.h"


template<class T>
class StatDisplay : public Drawable{
public:
	StatDisplay(GLshort lx, GLshort rx, GLshort ty){
		_leftX = lx;
		_rightX = rx;
		_centerX = (lx + rx) / 2.0;
		_topY = ty;
	}
	
	void clear(){
		_text.clear();
	}
	
	//--- GENERAL ---//	
	virtual void update(T*) = 0;
	
	//--- DRAW ---//
	virtual void draw(bool step){
		for(GLshort i = 0; i < _text.size(); ++i)
			_text[i].draw(step);
	}
	
protected:
	//--- GENERAL ---//
	vector<TextLine> _text;
	GLshort _leftX;
	GLshort _centerX;
	GLshort _rightX;
	GLshort _topY;
};

#endif
