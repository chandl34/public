/*
 *  LevelMap.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef LEVEL_MAP_H_
#define LEVEL_MAP_H_

#include "Screen.h"

#include "Memory.h"
#include "Pathing.h"
#include "Unit.h"
#include "Team.h"

class Projectile;
class GridBlock;
class Object;


class LevelMap : public MapScreen{
protected:
	LevelMap();
	
public:
	static LevelMap* getInstance();
	~LevelMap();
	
	//--- INIT ---//	
	void buildBuffers();
	void initLevel(bool); // TEMP -- REMOVE!!!
	
	//--- GENERAL ---//	
	Camera* getCamera();
	void centerView(GLshort, GLshort);
	bool onScreen(const Coord2d<GLshort>&);
	
	//---- GRIDBLOCK ----//
	GridBlock* getSelectedBlock();			
	GridBlock* getBlockByIso(GLshort, GLshort);
	GridBlock* getBlockByPath(GLshort, GLshort);
	GridBlock* getBlockBy3D(GLshort, GLshort);
	
	//---- DRAW ----//
	void draw(bool);								
	void drawMinimap(bool);
	
	//---- THREADING ----//
	void sendToBackground(ViewArgs&);
	static void* backgroundThread(void*);	
	
	//--- TOUCH ---//
	bool isLocked();								
	void push(GLshort, const Coord2d<GLshort>&);							
	void move(GLshort, const Coord2d<GLshort>&);							
	bool release(GLshort, const Coord2d<GLshort>&);			
	
	//---- PROJECTILES ----//	
	void addProjectile(Projectile*);
	
	//---- UNIT ----//		
	void addUnit(Unit*, GLshort, GLshort, GLshort);
	
	Unit* getSelectedUnit();
	void selectUnit(Unit*);
	void selectNextUnit();
	void selectPrevUnit();				
	
	//---- GAMEPLAY ----//		
	void confirmAction();	
	void setMode(GLshort);	
	void endTurn();
	
	//---- IO ----//	
	void saveData(ofstream&);
	
private:
	//--- GENERAL ---//
	static LevelMap* _levelMap;	
	
	//---- GRIDBLOCK ----//
	GridBlock* _gridBlock[MAP_BLOCK_X][MAP_BLOCK_Y];
	Pathing _pathing;											
	GridBlock* _sBlock;											
	
	GridBlock* getBlockByOffset(GLshort, GLshort) const;
	void selectBlock(GridBlock*);
	
	//---- THREADING ----//
	static bool _bgActive;
	static bool _bgKill;
	static pthread_t _bgthread;
	static pthread_cond_t _cond;
	static pthread_mutex_t _mutex;	
	static ViewArgs _viewArgs;

	//---- DRAW ----//
	Coord2d<GLshort> _bl;								
	
	GLuint** _groundStripVert;						
	GLuint _groundStripTexCoord;						
	
	GLuint _staticObjTexVert;
	GLuint _staticObjTexCoord;
	
	bool _redraw;								
	bool _store;								
	bool _storeMini;
	bool _resort;
	GLuint _screenTex;									
	void* _screenData;									
			
	void drawWithBuffers(bool);				
	void drawWithHalfBlend(bool);				
	void drawWithFullBlend(bool);				
	
	void createScreenTex();						
	void drawScreenTex();							
	
	void drawOverlays(bool);			
	void drawObjects(bool);							
				
	//--- ISO SORTING ---//	
	ObjectList _objList;						
	
	//---- PROJECTILES ----//	
	list<Projectile*> _proj;			
	
	//---- UNIT ----//	
	Team* _team[TEAMS_PER_FIGHT];				
	UnitList _dead;								
	
	void removeDead();
};

#endif
