/*
 *  PopupMenu.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "PopupMenu.h"

PopupMenu::PopupMenu(Button* b, Menu* m){	
	//--- GENERAL ---//
	button = b;	
	menu = m;
	selected = 0;
	expanded = false;
	
	//---- TOUCH ----//
	timePushed = -1;
	actionDelay = 0.5f;
}

PopupMenu::~PopupMenu(){	
	//--- GENERAL ---//
	delete button;
	delete menu;
}


//--- GENERAL ---//
GLshort PopupMenu::getSelected() const{
	return selected;
}


//---- DRAW ----//
void PopupMenu::draw(bool step){
	if(timePushed > 0 && [[NSDate date] timeIntervalSince1970] - timePushed > actionDelay){
		timePushed = -1;
		expanded = true;
	}
	
	glMatrixMode(GL_MODELVIEW);
	button->draw(step);
	if(expanded)
		menu->draw(step);
}


//---- TOUCH ----//
bool PopupMenu::push(const Coord2d<GLshort>& p){
	bool s = button->push(p);
	if(s && !expanded){
		timePushed = [[NSDate date] timeIntervalSince1970];	
		button->select(true);
		selected = true;
	}
	return s;
}

void PopupMenu::move(const Coord2d<GLshort>& p){
	button->move(p);
	selected = button->isSelected();
	if(selected)
		menu->release(p);
	else if(expanded){
		menu->move(p);
		selected = menu->getSelected();
		if(selected)
			selected++;		// Hitting main button = 1, others = 2, 3, 4,...
	}
}

void PopupMenu::release(const Coord2d<GLshort>& p){
	if(button->isSelected())
		button->release(p);
	else if(expanded)
		menu->release(p);
	timePushed = -1;
	expanded = false;
	//printf("Menu item %i selected\n", selected);
}
