/*
 *  PopupMenu.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PopupMenu.h"

#include "Icon.h"
#include "Image.h"

#include "ImageStorage.h"


PopupMenu::PopupMenu(const Coord2d<double>& loc, 
					 const Size2d<GLshort>& dim, 
					 const Size2d<GLshort>& bsize) 
: button(NULL, loc)
,  menu(Coord2d<double>(loc[X], loc[Y] + bsize[Y]), dim, bsize)
{	
	//--- GENERAL ---//	
	expanded = false;
	
	//---- TOUCH ----//
	timePushed = -1;
	actionDelay = 0.5;
}


//--- GENERAL ---//	
Button* PopupMenu::getButton(GLshort s){
	if(s == 0)
		return &button;
	else
		return menu.getButton(s - 1);
}


//---- DRAW ----//
void PopupMenu::draw(bool step){
	if(timePushed > 0 && time(0) - timePushed > actionDelay){
		timePushed = -1;
		expanded = true;
	}
	
	button.draw(step);
	if(expanded)
		menu.draw(step);
}


//---- TOUCH ----//
bool PopupMenu::isTouching(const Coord2d<GLshort>& p){
	return button.isTouching(p) || (expanded && menu.isTouching(p));
}

void PopupMenu::push(GLshort t, const Coord2d<GLshort>& p){
	button.push(t, p);
	if(button.getSelected())
		timePushed = time(0);	
}

void PopupMenu::move(GLshort t, const Coord2d<GLshort>& p){
	button.move(t, p);
	if(expanded)
		menu.move(t, p);
}

bool PopupMenu::release(GLshort t, const Coord2d<GLshort>& p){
	if(button.release(t, p))
		selected = 0;
	else if(expanded){
		selected = menu.getSelected();
		if(menu.release(t, p))
			++selected;
	}
	
	expanded = false;
	timePushed = -1;
	
	return selected >= 0;
}
