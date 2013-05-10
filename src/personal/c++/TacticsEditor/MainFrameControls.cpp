/*
 *  MainFrameControls.mm
 *  TacticsMapEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainFrame.h"


//---- CONTROLS ----//
int MainFrame::handle(int e) {
	Coord2d<GLshort> p1(Fl::event_x(), MAIN_FRAME_SIZE[Y] - Fl::event_y());
	Coord2d<GLshort> p2(MAIN_FRAME_SIZE[X] - Fl::event_x(), Fl::event_y());
	
	switch(e){
		case FL_FOCUS:
		case FL_UNFOCUS:
			return 0;
			
			// Mouse
		case FL_PUSH:
			mainScreen->push(0, p1);
			if(Fl::event_button() == 3)
				mainScreen->push(1, p2);
			break;
			
		case FL_RELEASE:
			mainScreen->release(0, p1);
			if(Fl::event_button() == 3)
				mainScreen->release(1, p2);
			break;
			
		case FL_DRAG:
			mainScreen->move(0, p1);
			if(Fl::event_button() == 3)
				mainScreen->move(1, p2);
			break;
			
		//case FL_MOUSEWHEEL:
			//Mouse::mouseWheel(Fl::event_dy(), Fl::event_x(), Fl::event_y());
			//break;
	}
	
	Fl_Gl_Window::handle(e);
	return 1;
}
