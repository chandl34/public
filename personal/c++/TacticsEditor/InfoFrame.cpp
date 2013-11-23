/*
 *  InfoFrame.cpp
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "InfoFrame.h"


InfoFrame::InfoFrame(int x, int y, int w, int h) 
: Fl_Gl_Window(x, y, w, h)
{
	infoScreen = NULL;
	Fl::add_timeout(1.0 / FRAMES_PER_SECOND, Timer_CB, (void*)this);
}

InfoFrame::~InfoFrame(){
	delete infoScreen;
}

void InfoFrame::init()
{
	infoScreen = new InfoScreen();
}


//---- GENERAL ----//
void InfoFrame::Timer_CB(void *userdata)
{
	InfoFrame *glwin = (InfoFrame*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0 / FRAMES_PER_SECOND, Timer_CB, userdata);
}


//---- DRAW ----//
void InfoFrame::draw()
{
	if (!valid()) {
		valid(1);
		init();
	}
	
	infoScreen->draw();
}

