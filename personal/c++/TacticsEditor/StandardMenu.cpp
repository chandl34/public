/*
 *  StandardMenu.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "StandardMenu.h"

#include "Button.h"
#include "Icon.h"
#include "Image.h"

#include "HitTest.h"
#include "ImageStorage.h"


StandardMenu::StandardMenu(const Coord2d<double>& loc, 
						   const Size2d<GLshort>& dim, 
						   const Size2d<GLshort>& bsize
						   ) : button(dim[X]), totalSize(bsize[X]*dim[X], bsize[Y]*dim[Y]){		
	//--- GENERAL ---//		
	for(GLshort i = 0; i < dim[X]; ++i){
		for(GLshort j = 0; j < dim[Y]; ++j){
			button[i].push_back(Button(NULL, Coord2d<double>(loc[X]+i*bsize[X], 
															 loc[Y]+j*bsize[Y])));
		}
	}
}


//--- GENERAL ---//	
Button* StandardMenu::getButton(GLshort s){
	GLshort x = s % button.size();
	GLshort y = s / button.size();
	if(y < button[0].size())
		return &button[x][y];	
	return NULL;
}


//---- DRAW ----//
void StandardMenu::draw(bool step){
	for(GLshort i = 0; i < button.size(); ++i){
		for(GLshort j = 0; j < button[i].size(); ++j)
			button[i][j].draw(step);
	}
}


//---- TOUCH ----//
bool StandardMenu::isTouching(const Coord2d<GLshort>& p){
	return pointInQuad(p, button[0][0].getOffset(), totalSize);
}

void StandardMenu::push(GLshort t, const Coord2d<GLshort>& p){
	if(!isTouching(p))
		selected = -1;
	else{	
		GLshort x = (p[X] - button[0][0].getOffset(X))/button[0][0].getSize(X);
		GLshort y = (p[Y] - button[0][0].getOffset(Y))/button[0][0].getSize(Y);	
		if(!button[x][y].isEnabled())
			selected = -1;
		else{
			selected = x + y * button.size();		
			button[x][y].push(t, p);	
		}
	}
}

void StandardMenu::move(GLshort t, const Coord2d<GLshort>& p){
	GLshort oldb = selected;
	push(t, p);
	if(oldb != -1 && oldb != selected)
		button[oldb % button.size()][oldb / button.size()].select(false);
}

bool StandardMenu::release(GLshort t, const Coord2d<GLshort>& p){
	if(selected != -1){
		button[selected % button.size()][selected / button.size()].release(t, p);
		return true;
	}
	return false;
}
