/*
 *  ComplexMenu.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ComplexMenu.h"


ComplexMenu::~ComplexMenu(){
	for(GLshort i = 0; i < selectable.size(); ++i)
		delete selectable[i];
}


//--- GENERAL ---//
GLshort ComplexMenu::getSelectedOption() const{
	if(selected == -1)
		return -1;
	else
		return selectable[selected]->getSelected();
}

void ComplexMenu::addSelectable(Selectable* m){
	selectable.push_back(m);
}

Button* ComplexMenu::getButton(GLshort o, GLshort s){
	if(o >= 0 && o < selectable.size())
		return selectable[o]->getButton(s);	
	return NULL;
}

Button* ComplexMenu::getButton(GLshort s){
	printf("ERROR:  ComplexMenu::getButton(GLshort) should not be called!\n"); // todo:  make this workable?
	return NULL;
}

//---- DRAW ----//
void ComplexMenu::draw(bool step){
	for(GLshort i = 0; i < selectable.size(); ++i)
		selectable[i]->draw(step);
}


//---- TOUCH ----//
bool ComplexMenu::isTouching(const Coord2d<GLshort>& p){	
	for(GLshort i = 0; i < selectable.size(); ++i){
		if(selectable[i]->isTouching(p))
			return true;
	}
	return false;
}

void ComplexMenu::push(GLshort t, const Coord2d<GLshort>& p){	
	selected = -1;
	for(GLshort i = 0; i < selectable.size(); ++i){
		if(selectable[i]->isTouching(p)){
			selected = i;
			selectable[selected]->push(t, p);
			break;
		}
	}
}

void ComplexMenu::move(GLshort t, const Coord2d<GLshort>& p){	
	if(selected == -1)
		push(t, p);
	else if(selectable[selected]->isTouching(p))
		selectable[selected]->move(t, p);
	else{
		selectable[selected]->release(t, p);
		selected = -1;
		push(t, p);
	}
}

bool ComplexMenu::release(GLshort t, const Coord2d<GLshort>& p){
	if(selected == -1)
		return false;
	return selectable[selected]->release(t, p);
}
