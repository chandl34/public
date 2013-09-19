/*
 *  MapIO.cpp
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


// SAVE
void saveBlockData(ofstream& file, GridBlock* gb)
{
	GLshort type;
	const Object* obj;
	const SideObject* sobj;
	const DoorObject* dobj;
	const ObjectList* objList;
	
	obj = gb->getGround();
	file << "g " << obj->getIndex() << " ";
	
	objList = gb->getObjects();
	for(ObjectList::const_iterator iter = objList->begin(); iter != objList->end(); ++iter){
		obj = *iter;
		type = obj->getModelType();
		file << "o " << type << " " << obj->getObjType() << " " << obj->getIndex() << " ";
		if(type == SIDE_MODEL){
			sobj = (SideObject*)obj;
			file << sobj->getSide() << " ";			
		}	
	}
	
	dobj = gb->getDoor();
	if(dobj != NULL){
		file << "d " << type << " " << dobj->getObjType() << " " << dobj->getIndex() << " ";
		file << dobj->getSide() << " ";
		file << dobj->isInner() << " " << dobj->getHinge() << " " << dobj->isOpen() << " ";
	}
}

void saveMap(const char* filename, LevelMap* levelMap)
{
	printf("Saving file: %s\n", filename);	
	ofstream file;
	file.open(filename);
	
	if(file.fail()){
		printf("Failed to load %s!\n", filename);
		return;
	}
	
	for(GLshort i = 0; i < MAP_BLOCK[X]; i++){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; j++){
			saveBlockData(file, LevelMap::getBlockByIso(i, j));
			file << "\n";
		}
		file << "\n";
	}
	
	file.close();
}

// LOAD
void loadBlockData(ifstream& file, GridBlock* gb)
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

LevelMap* loadMap(const char* filename)
{
	printf("Loading file: %s\n", filename);
	ifstream file;
	file.open(filename);
	
	if(file.fail()){
		printf("Failed to load %s!\n", filename);
		return NULL;
	}
	
	LevelMap* levelMap = new LevelMap();	
	for(GLshort i = 0; i < MAP_BLOCK[X]; i++){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; j++)
			loadBlockData(file, LevelMap::getBlockByIso(i, j));
	}
	
	levelMap->init();
	return levelMap;
}