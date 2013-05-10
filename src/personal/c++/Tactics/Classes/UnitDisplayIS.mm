/*
 *  UnitDisplayIS.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/4/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "UnitDisplayIS.h"

#include "Unit.h"


UnitDisplayIS::UnitDisplayIS(GLshort lx, GLshort rx, GLshort ty) 
: StatDisplay<Unit>(lx, rx, ty){
	GLshort y = _topY;
	
	_text.push_back(TextLine());
	_text[NAME_STR].addString(" ", Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[STR_STR].addString("Strength", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[STR_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[AGI_STR].addString("Agility", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[AGI_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[ACC_STR].addString("Accuracy", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[ACC_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[REA_STR].addString("Reactions", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[REA_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 20;
	
	_text.push_back(TextLine());
	_text[STAT_STR].addString("Stats", Coord2d<double>(_centerX, y), CENTERED);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[BATTLE_STR].addString("Battles", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[BATTLE_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[KILL_STR].addString("Kills", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[KILL_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[RATE_STR].addString("Hit Rate", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[RATE_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
	y -= 10;
	
	_text.push_back(TextLine());
	_text[IMP_STR].addString("Improvement", Coord2d<double>(_leftX, y), ALIGN_LEFT);
	_text[IMP_STR].addString(" ", Coord2d<double>(_rightX, y), ALIGN_RIGHT);
}


//--- GENERAL ---//	
void UnitDisplayIS::update(Unit* u){
	_text[NAME_STR].setString("The Man");
	
	_text[STR_STR].setString("66", 1);
	_text[AGI_STR].setString("77", 1);
	_text[ACC_STR].setString("96", 1);
	_text[REA_STR].setString("25", 1);
	
	
	_text[BATTLE_STR].setString("12", 1);
	_text[KILL_STR].setString("56", 1);
	_text[RATE_STR].setString("87%", 1);
	_text[IMP_STR].setString("12%", 1);
}
