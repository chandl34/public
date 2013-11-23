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
#include "BlockCursor.h"
#include "Object.h"

class GridBlock;


class LevelMap : public BaseScreen{
public:
	LevelMap();
	~LevelMap();
	
	void init();
	
	//--- GENERAL ---//		
	static GridBlock* getBlockByIso(GLshort, GLshort);
	static GridBlock* getBlockByPath(GLshort, GLshort);
	static GridBlock* getBlockBy3D(GLshort, GLshort);
	static GridBlock* getSelectedBlock();
	
	static void moveCursor(GLshort);
	
	//---- DRAW ----//
	void draw(bool);								// Defined in LevelMapDraw.mm
	
	static void refresh();
	
	//--- CONTROLS ---//
	void keyDown(GLshort);
	void push(GLshort, const Coord2d<GLshort>&);							
	void move(GLshort, const Coord2d<GLshort>&);							
	bool release(GLshort, const Coord2d<GLshort>&);			
	
private:
	//--- GENERAL ---//
	static Camera camera;	
	static GridBlock* gridBlock[MAP_BLOCK_X][MAP_BLOCK_Y];
	static GridBlock* sBlock;						// Selected gridBlock
	static BlockCursor cursor;	
	
	static void selectBlock(GridBlock*);	
	GridBlock* getBlockByOffset(GLshort, GLshort) const;
	static void centerView(GLshort, GLshort);
	
	//---- DRAW ----//	
	Coord2d<GLshort> bl;								// Previous bottom left corner stored	
	
	GLuint** groundStripVert;						// Vertical strips of ground, used for faster drawing
	GLuint groundStripTexCoord;					// Texture coordinates for ground	
	
	GLuint staticObjTexVert;
	GLuint staticObjTexCoord;
	
	static bool redraw;								// Redraw the entire map, if true
	static bool store;								// Store the map, if true
	static bool resort;
	GLuint screenTex;									// glReadPixels texture of the screen's ground
	void* screenData;									// Pixel data generated from glReadPixels
	
	ObjectList objList;	
	
	void drawWithBuffers(bool);					// Fastest form of drawing
	void drawWithHalfBlend(bool);					// Medium spend drawing - kept for testing purposes
	void drawWithFullBlend(bool);					// Slow drawing speed - kept for testing purposes	
	
	void createScreenTex();							// glReadPixels to store the current screen
	void drawScreenTex();							// Draw the previously stored screen glReadPixels data
	
	void drawOverlays(bool);			
	void drawObjects(bool);							// Gather, sort, and draw objects on screen
	
	//--- TOUCH ---//
	GLshort touchCount;							
	Coord2d<GLshort> startPoint[2];					// Where touch started
	Coord2d<GLshort> lastPoint[2];					// Where touch ended
	bool drag;										// If touch is a drag
	double actionDelay;								// Time it takes for a 'touch' to become a 'press'
	double timePushed;								// Time touch began
};

#endif
