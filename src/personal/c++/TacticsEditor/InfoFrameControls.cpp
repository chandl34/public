/*
 *  InfoFrameControls.cpp
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/28/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "InfoFrame.h"


//---- CONTROLS ----//
int InfoFrame::handle(int e) {
	Coord2d<GLshort> p(Fl::event_x(), INFO_FRAME_SIZE[Y] - Fl::event_y());
	
	switch(e){
		case FL_FOCUS:
		case FL_UNFOCUS:
			return 1;
			
			// Keyboard
		case FL_KEYDOWN:
			if(key != Fl::event_key() || 
				key == 'a' || key == 's' ||
				key == 'd' || key == 'w'){
				key = Fl::event_key();
				infoScreen->keyDown(key);
			}
			break;
			
		case FL_KEYUP:
			key = -1;
			break;
			
			// Mouse
		case FL_PUSH:
			infoScreen->push(0, p);
			break;
			
		case FL_RELEASE:
			infoScreen->release(0, p);
			break;
			
		case FL_DRAG:
			infoScreen->move(0, p);
			break;
			
			//	case FL_MOUSEWHEEL:
			//		Mouse::mouseWheel(Fl::event_dy(), Fl::event_x(), Fl::event_y());
			//		break;
	}
	
	Fl_Gl_Window::handle(e);
	return 1;
}
