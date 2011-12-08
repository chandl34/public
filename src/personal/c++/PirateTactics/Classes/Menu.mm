/*
 *  Menu.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Menu.h"
#include "HitTest.h"
#include "ImageContainer.h"


Menu::Menu(const Coord2d<GLshort>& loc, 
		   const Size2d<GLshort>& dim, 
		   const Size2d<GLshort>& bsize
		   ) : dimension(dim), totalSize(bsize[X]*dim[X], bsize[Y]*dim[Y]){	
	
	// TEMPORARY!!@!@!@!!11
	Image* img = new Image(bsize, 0);	
	ImageContainer::addImage(img);
	
	
	//--- GENERAL ---//		
	button = new Button**[dimension[X]];
	for(GLshort i = 0; i < dimension[X]; i++){
		button[i] = new Button*[dimension[Y]];
		for(GLshort j = 0; j < dimension[Y]; j++)
			button[i][j] = new Button(new Icon(img, Coord2d<GLfloat>(loc[X]+i*bsize[X], 
																	 loc[Y]+j*bsize[Y])));
	}
	
	selected = 0;
}

Menu::~Menu(){
	//--- GENERAL ---//	
	for(GLshort i = 0; i < dimension[X]; i++){
		button[i] = new Button*[dimension[Y]];
		for(GLshort j = 0; j < dimension[Y]; j++)
			delete button[i][j];
		delete [] button[i];
	}
	delete [] button;
}


//--- GENERAL ---//
GLshort Menu::getDimension(GLshort c) const{
	return dimension[c];
}

GLshort Menu::getSelected() const{
	return selected;
}


//---- DRAW ----//
void Menu::draw(bool step){
	for(GLshort i = 0; i < dimension[X]; i++){
		for(GLshort j = 0; j < dimension[Y]; j++)
			button[i][j]->draw(step);
	}
}


//---- TOUCH ----//
bool Menu::push(const Coord2d<GLshort>& p){
	selected = pointInQuad(p, button[0][0]->getOffset(), totalSize);
	if(selected){
		GLshort x = (p[X] - button[0][0]->getOffset(X))/button[0][0]->getSize(X);
		GLshort y = (p[Y] - button[0][0]->getOffset(Y))/button[0][0]->getSize(Y);
		selected += x + y*dimension[X];		
		button[x][y]->select(true);
	}	
	return selected;
}

void Menu::move(const Coord2d<GLshort>& p){
	GLshort temp = selected;	
	push(p);	// selected = newValue
	if(temp && temp != selected)
		button[(temp-1)%dimension[X]][(temp-1)/dimension[X]]->select(false);
}

void Menu::release(const Coord2d<GLshort>& p){
	if(selected){
		button[(selected-1)%dimension[X]][(selected-1)/dimension[X]]->select(false);
		selected = false;
	}
}
