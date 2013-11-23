/*
 *  MainScreen.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/19/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "MainScreen.h"

#include "AimingScreen.h"
#include "CampaignMap.h"
#include "CampaignScreen.h"
#include "InventoryScreen.h"
#include "LoadScreen.h"
#include "MenuScreen.h"
#include "MiniMapScreen.h"
#include "SaveScreen.h"
#include "LevelScreen.h"
#include "TeamScreen.h"
#include "TitleScreen.h"

#include "MapIO.h"
#include "Options.h"
#include "SaveIO.h"


BaseScreen* MainScreen::_screen[BASE_SCREENS];
BaseScreen* MainScreen::_currentScreen;

SubScreen* MainScreen::_subScreen[SUB_SCREENS];
SubScreen* MainScreen::_currentSubScreen;

string MainScreen::_save[8];


#include "MemCheck.h"
#include "LevelMap.h"



MainScreen::MainScreen()
: BaseScreen(true)
{
	freeMemory();
	
	// Setup random number generator
	srand([[NSDate date] timeIntervalSince1970]);
	
	// OpenGL
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glClearColor(1.0, 0.0, 0.0, 0.0);	
	
	glEnable(GL_TEXTURE_2D);		
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
	// this is initializing containers... todo: make a cleaner way to do this
	tempInit();
	
	
	printf("\n//--- BUILDING SCREENS ---//\n");
	// Create screens
	_screen[TITLE_SCREEN] = new TitleScreen();
	_screen[CAMPAIGN_SCREEN] = new CampaignScreen();
	_screen[LEVEL_SCREEN] = new LevelScreen();
	_currentScreen = _screen[TITLE_SCREEN];
	
	// Create subScreens
	_subScreen[MENU_SCREEN] = new MenuScreen();
	_subScreen[LOAD_SCREEN] = new LoadScreen();
	_subScreen[SAVE_SCREEN] = new SaveScreen();
	_subScreen[OPTIONS_SCREEN] = NULL;
	
	_subScreen[TEAM_SCREEN] = new TeamScreen();
	
	_subScreen[AIMING_SCREEN] = new AimingScreen();
	_subScreen[INVENTORY_SCREEN] = new InventoryScreen();
	_subScreen[MINI_MAP_SCREEN] = new MiniMapScreen();	
	_currentSubScreen = NULL;
	
	// FPS
	_frames = 0;
	_totalFrames = 0;
	_lastTime = 0;
	_timeElapsed = 0;

	
	//---- IO ----//
	_save[0] = "auto";	
	_save[1] = "game1";
	_save[2] = "game2";
	_save[3] = "game3";
	_save[4] = "game4";
	_save[5] = "game5";
	_save[6] = "game6";
	_save[7] = "game7";
	
	
	freeMemory();
}

MainScreen::~MainScreen()
{
	for(GLshort i = 0; i < BASE_SCREENS; ++i)
		delete _screen[i];
	
	for(GLshort i = 0; i < SUB_SCREENS; ++i)
		delete _subScreen[i];
}


//---- GENERAL ----//
void MainScreen::setScreen(GLshort i)
{
	_currentScreen = _screen[i];
}

void MainScreen::setSubScreen(GLshort i)
{
	_currentSubScreen = _subScreen[i];
	_currentSubScreen->open();
}

void MainScreen::saveData(GLshort i)
{			
	//LevelScreen* tacticalScreen = (LevelScreen*)screen[LEVEL_SCREEN];
	saveGame(_save[i]);
	printf("Finished Saving Game\n");	
}

void MainScreen::loadData(GLshort i)
{
	// Clear Data
	CampaignScreen* campaignScreen = (CampaignScreen*)_screen[CAMPAIGN_SCREEN];
	campaignScreen->setCampaignMap(NULL);	
	LevelScreen* levelScreen = (LevelScreen*)_screen[LEVEL_SCREEN];
	levelScreen->setLevelMap(NULL);
	
	// Load Data
	bool isInBattle = loadGame(_save[i]);
	
	// Set Data
	campaignScreen->setCampaignMap(CampaignMap::getInstance());	
	if(!isInBattle)
		setScreen(CAMPAIGN_SCREEN);
	else{
		LevelMap* levelMap = LevelMap::getInstance();
		levelScreen->setLevelMap(levelMap);
		levelMap->initLevel(false);
		setScreen(LEVEL_SCREEN);
	}
	printf("Finished Loading Game\n");	
}

void MainScreen::newGame()
{
	// Clear Data
	CampaignScreen* campaignScreen = (CampaignScreen*)_screen[CAMPAIGN_SCREEN];
	campaignScreen->setCampaignMap(NULL);
	
	// todo: remove... just for testing for now
	CampaignMap* campaignMap = CampaignMap::getInstance();
	campaignMap->tempInit();
	campaignMap->initCampaign(true);
	
	campaignScreen->setCampaignMap(campaignMap);
	setScreen(CAMPAIGN_SCREEN);
}

void MainScreen::newBattle(const string& mapName, Team* aTeam, Team* dTeam)
{
	// Clear Data
	LevelScreen* levelScreen = (LevelScreen*)_screen[LEVEL_SCREEN];	
	levelScreen->setLevelMap(NULL);
	
	LevelMap* levelMap = loadMap(mapName);
	levelScreen->setLevelMap(levelMap);	
	levelMap->initLevel(true);
	setScreen(LEVEL_SCREEN);
								  
	printf("Finished Loading Map\n");	
}


//---- DRAW ----//
void MainScreen::draw(bool step)
{
	resetView();
	if(_currentSubScreen != NULL)
		_currentSubScreen->draw(step);
	else
		_currentScreen->draw(step);
	_currentScreen->drawOther(step);
}

void MainScreen::draw()
{
//	glClear(GL_COLOR_BUFFER_BIT);	// not needed? - fps improvement is microscopic by removing it
	
//	double timer = [[NSDate date] timeIntervalSince1970];
	
	++_totalFrames;

	//----- SHOW FPS -----//
	if(SHOW_FPS){
		double time = [[NSDate date] timeIntervalSince1970];
		_timeElapsed += time - _lastTime;
		_lastTime = time;		
		++_frames;
		
		if(_timeElapsed > 2){		
			printf("FPS: %.1f\n", _frames/_timeElapsed);		
			_frames = 0;
			_timeElapsed = 0;
		}
	}
	
	//----- DRAW SCREEN -----//
	draw(_totalFrames % 5  == 0);
	
//	timer = [[NSDate date] timeIntervalSince1970] - timer;
//	printf("Frame took %f seconds\n", timer);
}


//--- TOUCH ---//
void MainScreen::push(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL){
		if(_currentSubScreen->isTouching(p))
			_currentSubScreen->push(t, p);
		else{
			//currentSubScreen->close();
			_currentSubScreen = NULL;
		}
	}
	else
		_currentScreen->push(t, p);
}

void MainScreen::move(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL)
		_currentSubScreen->move(t, p);
	else
		_currentScreen->move(t, p);
}

bool MainScreen::release(GLshort t, const Coord2d<GLshort>& p)
{
	if(_currentSubScreen != NULL){
		if(_currentSubScreen->release(t, p)){
			//currentSubScreen->close();
			_currentSubScreen = NULL;
		}
		return true;
	}
	else
		return _currentScreen->release(t, p);
}	
