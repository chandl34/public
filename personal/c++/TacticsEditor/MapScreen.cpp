/*
 *  MapScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MapScreen.h"

#include "LevelMap.h"

#include "ImageStorage.h"
#include "Options.h"
#include "MapIO.h"


MapScreen::MapScreen()
: SaveableScreen(true)
{
	printf("Building LevelMap...\n");
	levelMap = loadMap("../../Maps/blank.map");
}

MapScreen::~MapScreen()
{
	delete levelMap;	
}



//---- IO ----//
string MapScreen::getFolder()
{
	return "../../Maps/";
}

string MapScreen::getFilter()
{
	return ".map";
}

void MapScreen::save(const string& str)
{
	if(levelMap != NULL)	
		saveMap(str.c_str(), levelMap);
}
void MapScreen::load(const string& str)
{
	LevelMap* lm = levelMap;
	levelMap = NULL;
	delete lm;
	
	levelMap = loadMap(str.c_str());
}


//---- DRAW ----//
void MapScreen::draw(bool step)
{
	if(levelMap != NULL)	
		levelMap->draw(step);
}
