/*
 *  SaveIO.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 11/30/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "SaveIO.h"

#include "Ammo.h"
#include "EnemyTeam.h"
#include "EnemyUnit.h"
#include "Camera.h"
#include "CampaignMap.h"
#include "DoorObject.h"
#include "Faction.h"
#include "Grenade.h"
#include "GridBlock.h"
#include "Gun.h"
#include "InfiniteItemContainer.h"
#include "Item.h"
#include "Level.h"
#include "LevelMap.h"
#include "Memory.h"
#include "MainScreen.h"
#include "Unit.h"

#include "MapIO.h"


typedef map<Coord2d<GLshort>, Unit*> UnitLocMap;


// KEY:
// u => Unit (2 + 7 params)
// d => Door (2 + 1 params)
// i => Item (2 + 4-6 params)
// m => Memory (2 + 3 params)


//--- LOAD ---//
/*
void loadData(ifstream& file)
{
	CampaignMap* campaign = CampaignMap::getInstance();	
	Level* sLevel = campaign->getSelectedLevel();
	LevelMap* levelMap = loadMap(sLevel->getTag().c_str());
	
	GLshort i[9];	
	file >> i[0];		// zoom
	file >> i[1];		// viewX
	file >> i[2];		// viewY
	
	Camera* camera = levelMap->getCamera();
	camera->setZoom(i[0]);
	camera->setView(X, i[1]);
	camera->setView(Y, i[2]);
	
	GridBlock* gb;
	const DoorObject* door;
	Unit* unit;
	Item* item;
	ItemContainerType* cont;
	
	MemoryMap* unhandled = Unit::getUnhandledMemories();
	unhandled->clear();	// todo: maybe make this non-static?  all static members are dangerous
	
	char type;
	file >> type;	
	for(file >> type; !file.eof(); file >> type){
		file >> i[0];	// gbX
		file >> i[1];	// gbY
		gb = levelMap->getBlockByIso(i[0], i[1]);
		
		if(type == 'f')
			return;
		else if(type == 'd'){
			door = gb->getDoor();
			file >> i[2];	// open
			if(i[2] != door->isOpen())		// toggle door if state is different
				gb->toggleDoor();			
		}
		else if(type == 'u'){
			file >> i[2];	// dir
			file >> i[3];	// index
			file >> i[4];	// teamName
			file >> i[5];	// currHP
			file >> i[6];	// maxHP
			file >> i[7];	// currTU
			file >> i[8];	// maxTU
			if(i[4] == PLAYER)
				unit = Unit::create(ObjType(UNIT), Dir(i[2]), i[3], HP(i[6]), TU(i[8]));
			else
				unit = EnemyUnit::create(ObjType(UNIT), Dir(i[2]), i[3], HP(i[6]), TU(i[8]));
			unit->setHP(i[5]);
			unit->setTU(i[7]);
			levelMap->addUnit(unit, i[4], gb->getCoordIso(X), gb->getCoordIso(Y));
		}
		else if(type == 'i'){
			file >> i[2];	// container
			if(i[2] == 0){	// ground container		
				cont = gb->getContainer();
				i[3] = 0;
				i[4] = 0;
				file >> i[5];  // type
				file >> i[6];  // index			
			}			
			else{				// unit container
				unit = gb->getUnit();
				cont = unit->getContainer(i[2] - 1);
				file >> i[3];  // locX
				file >> i[4];  // locY	
				file >> i[5];  // type
				file >> i[6];  // index		
			}
			
			if(i[5] == ITEM)
				item = Item::create(ItemType(i[5]), i[6]);
			else if(i[5] == AMMO){
				item = Ammo::create(ItemType(i[5]), i[6]);
				file >> i[7];
				((Ammo*)item)->setAmmo(i[7]);
			}
			else if(i[5] == GRENADE)
				item = Grenade::create(ItemType(i[5]), i[6]);
			else if(i[5] == GUN){
				item = Gun::create(ItemType(i[5]), i[6]);
				file >> i[7];
				((Gun*)item)->setAmmo(i[7]);
			}
			
			cont->setItem(item, i[3], i[4]);
		}	
		else if(type == 'm'){
			file >> i[2];	// remX
			file >> i[3];	// remY
			file >> i[4];	// timer
			unit = gb->getUnit();
			gb = levelMap->getBlockByIso(i[2], i[3]);
			(*unhandled)[unit] = Memory(gb, i[4]);
		}
	}	
}
*/

void loadCampaignData(ifstream& file, UnitLocMap& unitMap)
{
	CampaignMap* campaign = CampaignMap::getInstance();
	Level* level;
	Faction* faction;
	Team* team;
	Unit* unit;
	Item* item;
	ItemContainerType* cont;
		
	char type;
	string text;	
	GLshort i[8];	
	GLfloat f[4];
	
	for(file >> type; !file.eof() && type != 'c'; file >> type){
		if(type == 'f'){				// Faction
			file >> i[0];				// id
			
			file.get();					// skip white space
			getline(file, text, ' ');	// name
			
			file >> f[0];				// colorR
			file >> f[1];				// colorG
			file >> f[2];				// colorB
			file >> f[3];				// colorA
			
			faction = Faction::create(i[0], text, Color(f[0], f[1], f[2], f[3]));
			campaign->addFaction(faction);
		}
		else if(type == 't'){			// Team
			file >> i[0];				// level id
			file >> i[1];				// intruder?
			
			level = campaign->getLevel(i[0]);
			team = Team::create(faction, level);
			level->setTeam(i[1], team);
		}
		else if(type == 'u'){			// Unit
			file >> i[0];				// gbX
			file >> i[1];				// gbY
			file >> i[2];				// dir
			file >> i[3];				// index
			file >> i[4];				// currHP
			file >> i[5];				// maxHP
			file >> i[6];				// currTU
			file >> i[7];				// maxTU
			
			unit = Unit::create(ObjType(UNIT), faction->getID(), Dir(i[2]), i[3], HP(i[5]), TU(i[7]));
			
			unit->setHP(i[4]);
			unit->setTU(i[6]);
			team->addUnit(unit);
			
			unitMap[Coord2d<GLshort>(i[0], i[1])] = unit;
		}
		else if(type == 'i'){			// Item
			file >> i[0];				// container
			file >> i[1];				// locX
			file >> i[2];				// locY
			file >> i[3];				// type
			file >> i[4];				// index
			
			item = Item::create(ItemType(i[3]), i[4]);
			if(i[3] == AMMO || i[3] == GUN){
				file >> i[5];			// ammoCount
				((Ammo*)item)->setAmmo(i[5]);				
			}
			
			cont = unit->getContainer(i[0]);
			cont->setItem(item, i[1], i[2]);
		}
	}
}

void loadLevelData(ifstream& file, UnitLocMap& unitMap)
{
	CampaignMap* campaign = CampaignMap::getInstance();	
	Team* sTeam = campaign->getSelectedTeam();
	Level* sLevel = sTeam->getLevel();
	LevelMap* levelMap = loadMap(sLevel->getTag().c_str());
	GridBlock* gb;
	const DoorObject* door;
	Unit* unit;
	Item* item;
	ItemContainerType* cont;
	
	MemoryMap* unhandled = Unit::getUnhandledMemories();
	unhandled->clear();	// todo: maybe make this non-static?
	
	char type;
	GLshort i[8];	
	
	// Camera
	file >> i[0];						// zoom
	file >> i[1];						// viewX
	file >> i[2];						// viewY
	
	Camera* camera = levelMap->getCamera();
	camera->setZoom(i[0]);
	camera->setView(X, i[1]);
	camera->setView(Y, i[2]);
	
	for(file >> type; !file.eof(); file >> type){
		file >> i[0];					// gbX
		file >> i[1];					// gbY
		gb = levelMap->getBlockByIso(i[0], i[1]);
		
		if(type == 'd'){				// Door
			file >> i[2];				// open?
			door = gb->getDoor();
			if(i[2] != door->isOpen())	
				gb->toggleDoor();			
		}
		else if(type == 'u'){			// Unit
			file >> i[2];				// kneeling?
			unit = unitMap[gb->getCoordIso()];
			if(i[2])
				unit->changeStance(NULL);
			unit->setBlock(gb);
			gb->setUnit(unit);
		}
		else if(type == 'i'){			// Item (on ground)
			file >> i[2];				// type
			file >> i[3];				// index	
			
			item = Item::create(ItemType(i[2]), i[3]);
			if(i[2] == AMMO || i[2] == GUN){
				file >> i[4];			// ammoCount
				((Ammo*)item)->setAmmo(i[5]);				
			}
			
			cont = gb->getContainer();
			cont->setItem(item);
		}	
		else if(type == 'm'){			// Memory
			file >> i[2];				// remX
			file >> i[3];				// remY
			file >> i[4];				// timer
			unit = gb->getUnit();		// Note: all units should have been placed already
			gb = levelMap->getBlockByIso(i[2], i[3]);
			(*unhandled)[unit] = Memory(gb, i[4]);
		}
	}	
}

bool loadGame(const string& filename)
{
	printf("Loading %s.sav...\n", filename.c_str());
	NSArray* searchPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
															   NSUserDomainMask, YES);
	NSString* docPath = [searchPaths objectAtIndex:0];
	string path([docPath UTF8String]);
	path += "/" + filename + ".sav";
	cout << "path: " << path << endl;
	
	ifstream file;
	file.open(path.c_str());
	
	if(file.fail()){
		printf("Failed to load %s.sav!\n", filename.c_str());
		return NULL;
	}
	
	GLshort i[2];
	file >> i[0];	// sLevel
	file >> i[1];	// inBattle?
	
	UnitLocMap unitMap;
	
	//--- CAMPAIGN ---//
	CampaignMap* campaign = CampaignMap::getInstance();
	loadCampaignData(file, unitMap);
	
	if(i[0] != -1){
		Level* sLevel = campaign->getLevel(i[0]);
		campaign->selectLevel(sLevel);
	}

	campaign->setInBattle(i[1]);
	
	if(i[1])
		loadLevelData(file, unitMap);
	
	file.close();
	
	return i[1];
}




// KEY:
// Campaign:
// f => faction
//
// LevelMap:
// u => Unit (2 + 7 params)
// d => Door (2 + 1 params)
// i => Item (2 + 4-6 params)
// m => Memory (2 + 3 params)


//--- SAVE ---//
/*
void saveCampaignData(ofstream& file)
{
	// What makes a campaign?
	// Level Data
	// Factions
	// Teams
	// Units
	
	CampaignMap* campaign = CampaignMap::getInstance();
	vector<Faction>* faction;
}

void saveDoorData(ofstream& file, GridBlock* gb)
{
	// Add door states
	const DoorObject* door = gb->getDoor();
	if(door != NULL){
		file << "d " << gb->getCoordIso(X) << " " << gb->getCoordIso(Y) << " ";
		file << door->isOpen() << " ";			
	}
}

void saveOtherData(ofstream& file, GridBlock* gb)
{
	// Add units
	Unit* unit = gb->getUnit();
	if(unit != NULL){
		file << "u " << gb->getCoordIso(X) << " " << gb->getCoordIso(Y) << " "; 
		file << unit->getDir() << " " << unit->getIndex() << " " << unit->getFactionID() << " ";	
		file << unit->getHP() << " " << unit->getMaxHP() << " ";
		file << unit->getTU() << " " << unit->getMaxTU() << " ";
	}
	
	// Add items
	ItemMap itemMap;
	Item* item;
	Ammo* ammo;
	ItemContainerType* cont;
	for(GLshort i = 0; i <= INVENTORY_CONTAINERS; ++i){
		if(i == 0)
			cont = gb->getContainer();
		else if(unit == NULL)
			break;
		else
			cont = unit->getContainer(i - 1);
		
		itemMap.clear();
		cont->getAllItems(itemMap, false);
		
		for(ItemMap::iterator iter = itemMap.begin(); iter != itemMap.end(); ++iter){
			item = iter->first;
			file << "i " << gb->getCoordIso(X) << " " << gb->getCoordIso(Y) << " "; 
			file << i << " ";
			if(i > 0)
				file << iter->second[X] << " " << iter->second[Y] << " ";
			file << item->getType() << " " << item->getIndex() << " ";
			if(item->getType() == AMMO || item->getType() == GUN){
				ammo = (Ammo*)item;
				file << ammo->getAmmo() << " ";
			}
		}
	}	
}

void saveMemories(ofstream& file)
{
	// Collect all memories - reinterpret them so they'll be useable with replacement Unit objects
	LevelMap* levelMap = LevelMap::getInstance();
	MemoryMap* memory;// = levelMap->getMemories();
	MemoryMap* unhandled = Unit::getUnhandledMemories();
	Unit* u;
	GridBlock* gbReal;
	GridBlock* gbRem;
	for(MemoryMap::iterator iter = memory->begin(); iter != memory->end(); ++iter){
		u = iter->first;
		gbReal = u->getBlock();
		gbRem = iter->second.getBlock();
		file << "m " << gbReal->getCoordIso(X) << " " << gbReal->getCoordIso(Y) << " ";
		file << gbRem->getCoordIso(X) << " " << gbRem->getCoordIso(Y) << " ";
		file << iter->second.getTimer() << " ";
	}	
	for(MemoryMap::iterator iter = unhandled->begin(); iter != unhandled->end(); ++iter){
		u = iter->first;
		gbReal = u->getBlock();
		gbRem = iter->second.getBlock();
		file << "m " << gbReal->getCoordIso(X) << " " << gbReal->getCoordIso(Y) << " ";
		file << gbRem->getCoordIso(X) << " " << gbRem->getCoordIso(Y) << " ";
		file << iter->second.getTimer() << " ";
	}
}

void saveLevelData(ofstream& file)
{
	CampaignMap* campaign = CampaignMap::getInstance();
	Level* level = campaign->getSelectedLevel();
	file << level->getTag() << " \n";
	LevelMap* levelMap = LevelMap::getInstance();
	
	// Camera
	Camera* camera = levelMap->getCamera();
	file << camera->getZoom() << " " << camera->getRelativeView(X) << " " << camera->getRelativeView(Y) << " \n";
	
	// Doors
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
			saveDoorData(file, levelMap->getBlockByIso(i, j));
		}
	}
	
	// Units and Items
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
			saveOtherData(file, levelMap->getBlockByIso(i, j));
		}
	}
	
	// Memories
	saveMemories(file);
}
*/
void saveGame(const string& filename)
{
	printf("Saving %s.sav...\n", filename.c_str());
	NSArray* searchPaths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,
															   NSUserDomainMask, YES);
	NSString* docPath = [searchPaths objectAtIndex:0];
	string path([docPath UTF8String]);
	path += "/" + filename + ".sav";
	cout << "path: " << path << endl;
	
	ofstream file;
	file.open(path.c_str());
	
	if(file.fail()){
		printf("Failed to save %s.sav!\n", filename.c_str());
		return;
	}
	
	// Note: campaign data added second, so that I can add units directly
	
	//--- CAMPAIGN ---//		
	CampaignMap* campaign = CampaignMap::getInstance();
	Level* sLevel = campaign->getSelectedLevel();
	
	if(sLevel == NULL)
		file << -1;
	else
		file << sLevel->getID();
	file << " " << campaign->inBattle() << "\n";
	
	campaign->saveData(file);
	file << "\n";
	
	//--- LEVELMAP ---//
	if(campaign->inBattle()){
		LevelMap* levelMap = LevelMap::getInstance();
		levelMap->saveData(file);
		file << "\n";
	}
	
	file.close();
}
