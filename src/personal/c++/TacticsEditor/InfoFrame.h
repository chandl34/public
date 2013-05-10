/*
 *  InfoFrame.h
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef INFO_FRAME_H_
#define INFO_FRAME_H_

#include "InfoScreen.h"


class InfoFrame : public Fl_Gl_Window{
public:
	InfoFrame(int, int, int, int);
	virtual ~InfoFrame();
	
private:
	void init();		
	static void Timer_CB(void*);
	
	//---- GENERAL ----//	
	InfoScreen* infoScreen;
	
	//---- DRAW ----//
	void draw();	
	
	//---- CONTROLS ----//
	int handle(int e);
	GLshort key;
};

#endif 


