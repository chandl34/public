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
#include "Camera.h"
#include "GridBlock.h"
#include "Pathing.h"
#include "Bullet.h"


class LevelMap : public Screen{
public:
	LevelMap();
	~LevelMap();
	
	//--- GENERAL ---//
	GridBlock* getSelectedBlock() const;			
	static GridBlock* getBlockByIso(GLshort, GLshort);
	static GridBlock* getBlockBy3D(GLshort, GLshort);
	
	//---- DRAW ----//
	void draw(bool);								// Defined in LevelMapDraw.mm
	
	//- PROJECTILE -//
	static void addProjectile(const Object*, const Object*);	
	
	//--- TOUCH ---//
	bool isLocked() const;							// Is the game locked from input?
	bool push(GLshort, const Coord2d<GLshort>&);							
	void move(GLshort, const Coord2d<GLshort>&);							
	void release(GLshort, const Coord2d<GLshort>&);			
	
	//---- UNIT ----//		
	void addUnit(Unit*, GLshort, GLshort);
	Unit* getSelectedUnit();
	void setUnitMode(GLshort);						// Select the mode
	void unitAction();								// Take an action	
	
private:
	//--- GENERAL ---//
	Camera camera;	
	static GridBlock* gridBlock[MAP_BLOCK_X][MAP_BLOCK_Y];
	Pathing pathing;								// Pathing specific for this LevelMap
	Icon* cursor;	// FIX THIS SHIT UP LATER GOAUSDFOUASFJKLDJFLKDSF
	GridBlock* sBlock;								// Selected gridBlock
	
	GridBlock* getBlockByOffset(GLshort, GLshort) const;
	void selectBlock(GridBlock*);
	
	//---- DRAW ----//
	Coord2d<GLshort> bl;							// Previous bottom left corner stored	
	GLuint** groundStripVert;						// Vertical strips of ground, used for faster drawing
	GLuint groundStripTexCoord;						// Texture coordinates for ground	
	bool redraw;									// Redraw the entire map, if true
	bool store;										// Store the map, if true
	GLuint screenTex;								// glReadPixels texture of the screen's ground
	void* screenData;								// Pixel data generated from glReadPixels
			
	void drawWithBuffers(bool);						// Fastest form of drawing
	void drawWithHalfBlend(bool);					// Medium spend drawing - kept for testing purposes
	void drawWithFullBlend(bool);					// Slow drawing speed - kept for testing purposes	
	void drawObjects(bool);							// Gather, sort, and draw objects on screen
	void createScreenTex();							// glReadPixels to store the current screen
	void drawScreenTex();							// Draw the previously stored screen glReadPixels data
	
	//--- ISO SORTING ---//	
	list<Object*> objList;						
	
	//- PROJECTILE -//
	static Bullet* bullet;
	
	//--- TOUCH ---//
	GLshort touchCount;							
	Coord2d<GLshort> startPoint[2];					// Where touch started
	Coord2d<GLshort> lastPoint[2];					// Where touch ended
	bool drag;										// If touch is a drag
	double actionDelay;								// Time it takes for a 'touch' to become a 'press'
	double timePushed;								// Time touch began
	
	//---- UNIT ----//
	vector<Unit*> unit;								// Units on this map
	Unit* sUnit;									// Selected unit	
	GLshort unitMode;								// Mode units are in (ie Look, Move, Use)	
};

#endif
