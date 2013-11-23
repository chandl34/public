/*
 *  MapIO.mm
 *  TacticsEditor
 *
 *  Created by Jonathan Chandler on 11/29/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "MapIO.h"

#include "DoorObject.h"
#include "GridBlock.h"
#include "LevelMap.h"
#include "SideObject.h"

#include "Options.h"

// KEY:
// g => GridBlock (1 param)
//-- o => Object (3 - 4 params)
//-- d => Door (7 params)


// LOAD
void loadBlockObjects(ifstream& file, GridBlock* gb)
{
	char cont;
	file >> cont;	
	int v[7];
	file >> v[6];
	gb->setGround(Object::create(ObjType(GROUND), v[6]));
	
	for(file >> cont; !file.eof() && cont != 'g'; file >> cont){
		if(cont == 'o'){
			file >> v[0];		// modelType
			file >> v[1];		// objType
			file >> v[6];		// index
			if(v[0] == CONST_MODEL)
				gb->addObject(Object::create(ObjType(v[1]), v[6]));
			else if(v[0] == SIDE_MODEL){
				file >> v[2];	// side
				gb->addObject(SideObject::create(ObjType(v[1]), Side(v[2]), v[6]));
			}
			else{
				printf("ERROR: Invalid data\n");
				return;
			}
		}
		else if(cont == 'd'){
			file >> v[0];	// modelType
			file >> v[1];	// objType
			file >> v[6];	// index
			file >> v[2];	// side
			file >> v[3];	// inner
			file >> v[4];	// hinge
			file >> v[5];	// open
			gb->setDoor(DoorObject::create(ObjType(DOOR), Side(v[2]), Inner(v[3]), Hinge(v[4]), v[6]));
			if(v[5])
				gb->toggleDoor();
		}		
		else{
			printf("ERROR: Invalid data\n");
			return;
		}
	}
	
	if(cont == 'g'){
		int pos = file.tellg();
		file.seekg(pos - 1);
	}
}

LevelMap* loadMap(const string& filename)
{
	printf("Loading %s.map...\n", filename.c_str());
	NSString* path = [[NSBundle mainBundle] pathForResource:[NSString stringWithUTF8String:filename.c_str()] ofType:@"map"];
	
	ifstream file;
	file.open([path UTF8String]);
	
	if(file.fail()){
		printf("Failed to load %s.map!\n", filename.c_str());
		return NULL;
	}
	
	LevelMap* levelMap = LevelMap::getInstance();		
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
			loadBlockObjects(file, levelMap->getBlockByIso(i, j));
	}
	if(USE_BUFFERS)
		levelMap->buildBuffers();
	
	file.close();
	return levelMap;
}