/*
 *  View.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 9/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef VIEW_H_
#define VIEW_H_

#include "Drawable.h"

#include "GridBlock.h"
#include "Icon.h"

class Unit;


typedef map<GridBlock*, GLshort> BlockLOS;

enum{FRONTAL, PERIPHERAL};
const GLshort SIGHT_RANGE[] = {9, 5};

enum{TURNED, MOVED, MAP_CHANGED, STANCE_CHANGED};


class View : public Drawable{
public:
	View();
	
	//--- GENERAL ---//
	void findLOS(const GridBlock*, Dir, GLshort, bool);
	
	bool canSee(GridBlock*);
	bool couldSee(GridBlock*);
	bool inScope(GridBlock*);
	
	void addLOS();
	void removeLOS();
	
	//---- DRAW ----//	
	void draw(bool);
	
private:
	list<Icon> _view;
	BlockLOS _viewLOS[VIEWS];
	static list<Coord2d<GLshort> > _viewTemplate;
	static Coord2d<GLshort> _templateBase;
	
	void findBlockLOS(const GridBlock*, const GridBlock*, GLshort, bool);
	
	GLshort getLOS(GLshort, GridBlock*);
};



// Non-member functions
#endif

