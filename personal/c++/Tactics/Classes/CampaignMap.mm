/*
 *  CampaignMap.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 12/1/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "CampaignMap.h"

#include "Color.h"
#include "EnemyTeam.h"
#include "Faction.h"
#include "Level.h"

#include "ImageStorage.h"


#include "EnemyUnit.h"
#include "Grenade.h"
#include "Gun.h"


CampaignMap* CampaignMap::_campaignMap = NULL;


CampaignMap* CampaignMap::getInstance()
{
	if(_campaignMap == NULL)
		_campaignMap = new CampaignMap();
	return _campaignMap;
}

CampaignMap::CampaignMap()
: MapScreen(false)
{
	printf("Building CampaignMap...\n");
	
	//---- GENERAL ----//
	_inBattle = false;
	
	//---- LEVEL ----//
	_tLevel = NULL;
	
	// TEMP!!!!111 -- defaults for levels
	Image* img;
	Level* level;
	
	img = new Image(Size2d<GLshort>(50, 50), 0);
	ImageStorage::addImage(img);
	
	level = new Level(0, "test", "The_Bowl");
	level->setImage(img);
	_level.push_back(level);
	
	level = new Level(1, "test", "EZ_Pay");
	level->setImage(img);
	level->setOffset(0, 50);
	_level.push_back(level);
	
	level = new Level(2, "test", "Shit_Stain");
	level->setImage(img);
	level->setOffset(50, 0);
	_level.push_back(level);	
}

CampaignMap::~CampaignMap()
{
	cout << "Deleting campaign map\n";
	_campaignMap = NULL;
	
	for(GLshort i = 0; i < _level.size(); ++i)
		delete _level[i];
	
	for(GLshort i = 0; i < _faction.size(); ++i)
		delete _faction[i];
}


void CampaignMap::tempInit()
{
	// TESTING !!!
	
	Faction* faction;
	Team* team;
	
	Unit* u;
	ItemContainerType* cont;
	Item* item;
	
	// Create good faction
	faction = Faction::create(_faction.size(), "Ball_Busters", Color(0, 1, 0.25, 1));
	_faction.push_back(faction);	
	
	team = Team::create(faction, _level[0]);
	_level[0]->setTeam(OWNER, team);
	
	// PLAYER unit with pistol and rifle and grenade
	u = Unit::create(ObjType(UNIT), faction->getID(), Dir(DOWN_LEFT), 0, HP(25), TU(25));		
	cont = u->getContainer(0);
	item = Item::create(ItemType(GUN), 0);
	cont->setItem(item, 0);
	cont = u->getContainer(3);
	item = Item::create(ItemType(GRENADE), 0);
	if(!cont->setItem(item, 1, 0))
		printf("ERROR:  Could not place item!!!\n");
	cont = u->getContainer(6);
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 0))
		printf("ERROR:  Could not place item!!!\n");	
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 1))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 2))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(GUN), 1);
	if(!cont->setItem(item, 1, 0))
		printf("ERROR:  Could not place item!!!\n");	
	team->addUnit(u);
	
	// PLAYER unit with pistol
	u = Unit::create(ObjType(UNIT), faction->getID(), Dir(DOWN_LEFT), 0, HP(25), TU(25));	
	cont = u->getContainer(0);
	item = Item::create(ItemType(GUN), 0);
	cont->setItem(item, 0);
	cont = u->getContainer(6);
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 0))
		printf("ERROR:  Could not place item!!!\n");	
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 1))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 2))
		printf("ERROR:  Could not place item!!!\n");
	team->addUnit(u);
	
	team = Team::create(faction, _level[1]);
	_level[1]->setTeam(OWNER, team);
	
	// PLAYER unit with pistol and grenade
	u = Unit::create(ObjType(UNIT), faction->getID(), Dir(DOWN_LEFT), 0, HP(25), TU(25));		
	cont = u->getContainer(0);
	item = Item::create(ItemType(GUN), 0);
	cont->setItem(item, 0);
	cont = u->getContainer(3);
	item = Item::create(ItemType(GRENADE), 0);
	if(!cont->setItem(item, 1, 0))
		printf("ERROR:  Could not place item!!!\n");
	cont = u->getContainer(6);
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 0))
		printf("ERROR:  Could not place item!!!\n");	
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 1))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 2))
		printf("ERROR:  Could not place item!!!\n");	
	team->addUnit(u);
	
	
	// Create enemy faction
	faction = Faction::create(_faction.size(), "Bunch_o'_Assholes", Color(1, 0.25, 0.25, 1));
	_faction.push_back(faction);
	
	team = Team::create(faction, _level[2]);
	_level[2]->setTeam(OWNER, team);
	
	// ENEMY unit with pistol
	u = Unit::create(ObjType(UNIT), faction->getID(), Dir(DOWN_LEFT), 0, HP(25), TU(25));	
	cont = u->getContainer(0);
	item = Item::create(ItemType(GUN), 0);
	cont->setItem(item, 0);
	cont = u->getContainer(6);
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 0))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 1))
		printf("ERROR:  Could not place item!!!\n");
	item = Item::create(ItemType(AMMO), 0);
	if(!cont->setItem(item, 0, 2))
		printf("ERROR:  Could not place item!!!\n");
	team->addUnit(u);		
}


void CampaignMap::initCampaign(bool isNew)
{
	if(isNew)
		_faction[PLAYER]->newTurn();
}


//---- GENERAL ----//
bool CampaignMap::inBattle() const
{
	return _inBattle;
}

void CampaignMap::setInBattle(bool b)
{
	_inBattle = b;
}


//---- LEVEL ----//
Level* CampaignMap::getLevel(GLshort i)
{
	return _level[i];
}

Level* CampaignMap::getLevelByOffset(GLshort x, GLshort y)
{
	Coord2d<GLshort> p(x, y - MENU_SIZE[Y]);
	
	for(GLshort i = 0; i < _level.size(); ++i){
		if(_level[i]->isTouching(p))
			return _level[i];
	}
	return NULL;
}

Level* CampaignMap::getSelectedLevel()
{
	Team* sTeam = getSelectedTeam();
	if(sTeam == NULL)
		return NULL;
	return sTeam->getLevel();
}

Level* CampaignMap::getTargetLevel()
{
	return _tLevel;
}


void CampaignMap::selectLevel(Level* level)
{
	Team* sTeam = level->getPlayerTeam();
	selectTeam(sTeam);
}

void CampaignMap::targetLevel(Level* level)
{
	_tLevel = level;
	selectTarget(_tLevel);
}


//---- FACTION ----//
Faction* CampaignMap::getFaction(GLshort i)
{
	return _faction[i];
}

void CampaignMap::addFaction(Faction* f)
{
	_faction.push_back(f);
}

