/*
 *  LevelMap.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 2/18/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "LevelMap.h"

#include "GridBlock.h"

#include "ImageStorage.h"

Camera LevelMap::camera;	
GridBlock* LevelMap::gridBlock[MAP_BLOCK_X][MAP_BLOCK_Y];
GridBlock* LevelMap::sBlock = NULL;	
BlockCursor LevelMap::cursor;

bool LevelMap::redraw;								
bool LevelMap::store;							
bool LevelMap::resort;


// TEMPORARY
#include "DoorObject.h"
#include "SideObject.h"


LevelMap::LevelMap() : BaseScreen(true){
	//--- GENERAL ---//	
	for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
		for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
			gridBlock[i][j] = new GridBlock(Coord2d<GLshort>(i, j));	
			gridBlock[i][j]->setGround(Object::create(ObjType(GROUND), 0));	
		}
	}		
	cursor.setCursorMode(MOVE);
	selectBlock(gridBlock[0][0]);
	
	
	//TEST MATERIAL
	{/*
	  for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
	  for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
	  gridBlock[i][j]->setGround(Object::create(ObjType(GROUND), 0));
	  }
	  
	  // Building 1 - west side
	  gridBlock[4][4]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[3][5]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[3][5]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3][5]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3][5]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[3][6]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[3][6]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3][6]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3][6]->setDoor(DoorObject::create(ObjType(DOOR), Side(LEFT_SIDE), Inner(OUTER), Hinge(RIGHT_HINGE), 0));
	  
	  gridBlock[2][7]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[2][7]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2][7]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2][7]->setDoor(DoorObject::create(ObjType(DOOR), Side(LEFT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[2][8]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[2][8]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2][8]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2][8]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[1][9]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 1 - south side
	  gridBlock[4][4]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[4][5]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[4][5]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[4][5]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[4][5]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[5][6]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[5][7]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[5][7]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5][7]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5][7]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[6][8]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[6][9]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[6][9]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[6][9]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[6][9]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));		
	  
	  gridBlock[7][10]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  // Building 1 - east side
	  gridBlock[7][11]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[7][12]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[7][12]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[7][12]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[7][12]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  
	  gridBlock[6][13]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[6][13]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][13]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][13]->setDoor(DoorObject::create(ObjType(DOOR), Side(LEFT_SIDE), Inner(INNER), Hinge(RIGHT_HINGE), 0));
	  
	  gridBlock[6][14]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[6][14]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][14]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][14]->setDoor(DoorObject::create(ObjType(DOOR), Side(LEFT_SIDE), Inner(INNER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[5][15]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[5][15]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5][15]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5][15]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[5][16]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 1 - north side
	  gridBlock[1][10]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[1][11]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[1][11]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[1][11]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[1][11]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));			
	  
	  gridBlock[2][12]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[2][13]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[2][13]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[2][13]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[2][13]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(INNER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[3][14]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[3][15]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[3][15]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[3][15]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[3][15]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));	
	  
	  gridBlock[4][16]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  
	  
	  // Building 2 - west side
	  gridBlock[9][20]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[9][19]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[9][19]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[9][19]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[9][19]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[10][18]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[10][17]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[8][21]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[8][22]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[8][22]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[8][22]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[8][22]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[7][23]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[7][24]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[6][25]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[6][25]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][25]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[6][25]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[6][26]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[5][27]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[5][27]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5][27]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5][27]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[5][28]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 2 - south side - west
	  gridBlock[10][17]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[11][18]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[11][18]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][18]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][18]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));	
	  
	  gridBlock[11][19]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[11][19]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][19]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][19]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[12][20]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[12][20]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[12][20]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[12][20]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[12][21]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  // Building 2 - inner east side
	  gridBlock[13][22]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[12][23]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[12][24]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[12][24]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[12][24]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[12][24]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[11][25]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[11][26]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[10][27]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[10][27]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[10][27]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[10][27]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[10][28]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[9][29]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 2 - inner south side
	  gridBlock[9][30]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[9][31]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[10][32]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[10][32]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[10][32]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[10][32]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[10][33]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[11][34]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[11][34]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][34]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][34]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[11][35]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[11][35]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][35]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][35]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(RIGHT_HINGE), 0));
	  
	  gridBlock[12][36]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[12][37]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[12][37]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[12][37]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[12][37]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[13][38]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[13][39]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  // Building 2 - inner west side
	  gridBlock[14][39]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[15][38]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[15][37]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[15][37]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[15][37]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[15][37]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[16][36]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[16][35]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[17][34]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[17][34]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[17][34]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[17][34]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[17][33]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[18][32]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 2 - south side - east
	  gridBlock[18][32]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[18][33]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[18][33]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[18][33]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[18][33]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));	
	  
	  gridBlock[19][34]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[19][34]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[19][34]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[19][34]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[19][35]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[19][35]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[19][35]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[19][35]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[20][36]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  // Building 2 - east side
	  gridBlock[20][37]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[20][38]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[19][39]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[19][39]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[19][39]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[19][39]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[19][40]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[18][41]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[18][42]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[18][42]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[18][42]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[18][42]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[17][43]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[17][44]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[16][45]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[16][45]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[16][45]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[16][45]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[16][46]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[15][47]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[15][47]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[15][47]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[15][47]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[15][48]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 2 - north side
	  gridBlock[4][29]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[5][30]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[5][31]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[5][31]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5][31]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5][31]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[6][32]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[6][33]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[7][34]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[7][34]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[7][34]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[7][34]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[7][35]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[8][36]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[8][37]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[8][37]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[8][37]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[8][37]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[9][38]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[9][39]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[10][40]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[10][40]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[10][40]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[10][40]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[10][41]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[11][42]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[11][43]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[11][43]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][43]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[11][43]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[12][44]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[12][45]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[13][46]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[13][46]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[13][46]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[13][46]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[13][47]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  gridBlock[14][48]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  
	  
	  // Building 3 - west side  +14 +6
	  GLshort i3 = 14;
	  GLshort j3 = 6;
	  gridBlock[4+i3][4+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[3+i3][5+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[3+i3][5+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3+i3][5+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[3+i3][5+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[3+i3][6+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));		
	  gridBlock[2+i3][7+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[2+i3][8+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[2+i3][8+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2+i3][8+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[2+i3][8+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[1+i3][9+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 3 - south side
	  gridBlock[4+i3][4+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[4+i3][5+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[4+i3][5+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[4+i3][5+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[4+i3][5+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[5+i3][6+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[5+i3][7+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[5+i3][7+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5+i3][7+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[5+i3][7+j3]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(OUTER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[6+i3][8+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[6+i3][9+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[6+i3][9+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[6+i3][9+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[6+i3][9+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));		
	  
	  gridBlock[7+i3][10+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  // Building 3 - east side
	  gridBlock[7+i3][11+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[7+i3][12+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[7+i3][12+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[7+i3][12+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[7+i3][12+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[6+i3][13+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  gridBlock[6+i3][14+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  gridBlock[5+i3][15+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(LEFT_SIDE), 0));		
	  gridBlock[5+i3][15+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5+i3][15+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(LEFT_SIDE), 0));
	  gridBlock[5+i3][15+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(LEFT_SIDE), 0));
	  
	  gridBlock[5+i3][16+j3]->addObject(SideObject::create(ObjType(WALL), Side(LEFT_SIDE), 0));
	  
	  // Building 3 - north side
	  gridBlock[1+i3][10+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[1+i3][11+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[1+i3][11+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[1+i3][11+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[1+i3][11+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));			
	  
	  gridBlock[2+i3][12+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[2+i3][13+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[2+i3][13+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[2+i3][13+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[2+i3][13+j3]->setDoor(DoorObject::create(ObjType(DOOR), Side(RIGHT_SIDE), Inner(INNER), Hinge(LEFT_HINGE), 0));
	  
	  gridBlock[3+i3][14+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  
	  gridBlock[3+i3][15+j3]->addObject(SideObject::create(ObjType(FRONT_FRAME), Side(RIGHT_SIDE), 0));		
	  gridBlock[3+i3][15+j3]->addObject(SideObject::create(ObjType(SIDE_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[3+i3][15+j3]->addObject(SideObject::create(ObjType(TOP_FRAME), Side(RIGHT_SIDE), 0));
	  gridBlock[3+i3][15+j3]->addObject(SideObject::create(ObjType(BOTTOM_FRAME), Side(RIGHT_SIDE), 0));	
	  
	  gridBlock[4+i3][16+j3]->addObject(SideObject::create(ObjType(WALL), Side(RIGHT_SIDE), 0));
	  // */}
	
	
	
	//---- DRAW ----//		
	// Pixel store variables
	refresh();
	glGenTextures(1, &screenTex);		
	screenData = malloc(512*512*4);
	
	
	//--- TOUCH ---//
	touchCount = 0;
	drag = false;	
	actionDelay = 0.5;
	timePushed = -1;	
}

LevelMap::~LevelMap()
{
	GLshort i, j;
	
	//--- GENERAL ---//
	for(i = 0; i < MAP_BLOCK[X]; ++i){
		for(j = 0; j < MAP_BLOCK[Y]; ++j)
			delete gridBlock[i][j];
	}
	
	//---- DRAW ----//
	for(i = 0; i < 2; ++i){
		glDeleteBuffers(MAP_BLOCK[X], groundStripVert[i]);
		delete [] groundStripVert[i];
	}
	delete [] groundStripVert;
	glDeleteBuffers(1, &groundStripTexCoord);
	
	glDeleteBuffers(1, &staticObjTexVert);
	glDeleteBuffers(1, &staticObjTexCoord);
	
	glDeleteTextures(1, &screenTex);
	free(screenData);		
}

void LevelMap::init()
{
	//--- OBJECT BUFFERS ---//
	{
		for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
			for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j)
				gridBlock[i][j]->isoSort(objList);
		}
		
		// Add static object data to buffers
		glGenBuffers(1, &staticObjTexVert);	
		glGenBuffers(1, &staticObjTexCoord);	
		
		vector<GLshort> tempTexVert;
		vector<GLfloat> tempTexCoord;
		for(ObjectList::iterator iter = objList.begin(); iter != objList.end(); ++iter)
			(*iter)->buildBuffers(staticObjTexVert, tempTexVert, staticObjTexCoord, tempTexCoord);
		cout << "objs: " << objList.size() << endl;
		objList.clear();	
		
		// Copy the data to arrays -- C11 gets past this.  maybe I can find that in later versions of XCode?  todo:  check that out
		GLshort sztv = tempTexVert.size();	
		GLshort tempTexVertArray[sztv];
		for(GLshort i = 0; i < sztv; ++i)
			tempTexVertArray[i] = tempTexVert[i];	
		glBindBuffer(GL_ARRAY_BUFFER, staticObjTexVert);
		glBufferData(GL_ARRAY_BUFFER, sztv * sizeof(GLshort), tempTexVertArray, GL_STATIC_DRAW);
		
		GLshort sztc = tempTexCoord.size();
		GLfloat tempTexCoordArray[sztc];
		for(GLshort i = 0; i < sztc; ++i)
			tempTexCoordArray[i] = tempTexCoord[i];
		glBindBuffer(GL_ARRAY_BUFFER, staticObjTexCoord);
		glBufferData(GL_ARRAY_BUFFER, sztc * sizeof(GLfloat), tempTexCoordArray, GL_STATIC_DRAW);
	}
	
	//--- GROUND BUFFERS ---//
	{
		GLshort sz = 8*ceil(MAP_BLOCK[Y]/2.0);
		GLshort sz2 = 8*MAP_BLOCK[Y]/2;
		
		groundStripVert = new GLuint*[2];// bottom and top overlay
		for(GLshort i = 0; i < 2; ++i){
			groundStripVert[i] = new GLuint[MAP_BLOCK[X]];
			glGenBuffers(MAP_BLOCK[X], groundStripVert[i]);	
		}	
		glGenBuffers(1, &groundStripTexCoord);
		
		GLshort offset;	
		GLshort vertTemp[sz]; 
		GLshort vertTemp2[sz2]; 
		GLfloat texCoordTemp[sz];
		GLshort* blockVert = ImageStorage::getVerts(Size2d<GLshort>(BLOCK_SIZE_ISO[MAX_ZOOM][X], 
																						BLOCK_SIZE_ISO[MAX_ZOOM][Y]));
		
		// This is the default size of ground blocks.  may need to change later
		GLfloat* blockTexCoord = ImageStorage::getTexCoords(Coord2d<GLfloat>(0.625f, 0.625f));		
		
		for(GLshort i = 0; i < MAP_BLOCK[X]; ++i){
			offset = 0;
			for(GLshort j = 0; j < MAP_BLOCK[Y]; ++j){
				if(j % 2 == 0){
					for(GLshort k = 0; k < 8; ++k){
						vertTemp[offset + k] = gridBlock[i][j]->getOffset(k % 2) + blockVert[k];
						if(i == 0)			// Assume this tajes the same time whether this is there or not, I can change this up kater to save time
							texCoordTemp[offset + k] = blockTexCoord[k];	
					}	
				}
				else{// if(i < MAP_BLOCK[X] - 1){	// Cuts out extra end piece - temporariky removed cause regukar draw doesn't ignore this
					for(GLshort k = 0; k < 8; ++k)					
						vertTemp2[offset + k] = gridBlock[i][j]->getOffset(k % 2) + blockVert[k];
					offset += 8;
				}		
			}			
			glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[0][i]);
			glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLshort), vertTemp, GL_STATIC_DRAW);	
			//	if(i < MAP_BLOCK[X] - 1){				 - temporariky removed cause regukar draw doesn't ignore this										
			glBindBuffer(GL_ARRAY_BUFFER, groundStripVert[1][i]);
			glBufferData(GL_ARRAY_BUFFER, sz2*sizeof(GLshort), vertTemp2, GL_STATIC_DRAW);		
			//	}
		}
		glBindBuffer(GL_ARRAY_BUFFER, groundStripTexCoord);
		glBufferData(GL_ARRAY_BUFFER, sz*sizeof(GLfloat), texCoordTemp, GL_STATIC_DRAW);
		
		// Restore the previous state -- may be able to remove when the game is closer to being finished
		glBindBuffer(GL_ARRAY_BUFFER, 0);	
	}
}



GridBlock* LevelMap::getSelectedBlock()
{	
	return sBlock;
}

GridBlock* LevelMap::getBlockByIso(GLshort i, GLshort j)
{
	if(i < 0 || j < 0 || i >= MAP_BLOCK[X] || j >= MAP_BLOCK[Y])
		return NULL;
	return gridBlock[i][j];
}

GridBlock* LevelMap::getBlockByPath(GLshort i, GLshort j)
{	
	// 2D path coords
	GLshort x = i;
	GLshort y = j - MAP_SIDE;	
	
	// 2D draw coords
	GLshort bX = (x - y) / 2.0;	
	GLshort bY = x + y;
	
	return getBlockByIso(bX, bY);
}

GridBlock* LevelMap::getBlockBy3D(GLshort i, GLshort j)
{	
	// 2D path coords
	GLshort x = i / BLOCK_SIZE_3D[X];
	GLshort y = j / BLOCK_SIZE_3D[Y] - MAP_SIDE;	
	
	// 2D draw coords
	GLshort bX = (x - y) / 2.0;	
	GLshort bY = x + y;
	
	return getBlockByIso(bX, bY);
}

GridBlock* LevelMap::getBlockByOffset(GLshort px, GLshort py) const
{
	px += camera.getView(X);	
	py += camera.getView(Y);
	
	GLshort blockX = px/(BLOCK_SIZE_ISO[camera.getZoom()][X]/2);
	GLshort blockY = py/(BLOCK_SIZE_ISO[camera.getZoom()][Y]/2);	
	GLshort remX = px%(BLOCK_SIZE_ISO[camera.getZoom()][X]/2);
	GLshort remY = py%(BLOCK_SIZE_ISO[camera.getZoom()][Y]/2);
	
	if((blockX + blockY)%2 == 0){  
		if(remY + remX/2 > BLOCK_SIZE_ISO[camera.getZoom()][Y]/2){
			++blockX;
			++blockY;
		}
	}
	else{
		if(remY - remX/2 > 0)
			++blockY;
		else
			++blockX;
	}	
	blockX /= 2;
	
	///*	
	cout << endl << "ISO:  (" << blockX << ", " << blockY << ")" << endl;
	
	GLshort pathX = blockX + blockY/2 + blockY%2;
	GLshort pathY = -blockX + blockY/2 + MAP_SIDE;	
	cout << "PATH:  (" << pathX << ", " << pathY << ")" << endl;
	//*/
	
	return getBlockByIso(blockX, blockY);
}


void LevelMap::selectBlock(GridBlock* gb)
{
	if(sBlock != gb){		
		cursor.setGridBlock(gb);
		
		if(sBlock != NULL)
			sBlock->select(false);
		sBlock = gb;
		if(sBlock != NULL)
			sBlock->select(true);
	}	
}

void LevelMap::moveCursor(GLshort i)
{
	GridBlock* gb = getBlockByIso(sBlock->getCoordIso(X) + 
											PATH_DIR[sBlock->getCoordIso(Y)%2][i][X], 
											sBlock->getCoordIso(Y) + 
											PATH_DIR[sBlock->getCoordIso(Y)%2][i][Y]);	
	if(gb != NULL){
		selectBlock(gb);
		
		switch(i){
			case DOWN_LEFT:
				if((sBlock->getOffset(X) + BLOCK_SIZE_ISO[MAX_ZOOM][X] / 2) * pow(2, camera.getZoom() - 2) < camera.getView(X) || 
					(sBlock->getOffset(Y) + BLOCK_SIZE_ISO[MAX_ZOOM][Y] / 2) * pow(2, camera.getZoom() - 2) < camera.getView(Y))
					centerView(sBlock->getOffset(X), sBlock->getOffset(Y));
				break;
				
			case UP_RIGHT:
				if((sBlock->getOffset(X) + BLOCK_SIZE_ISO[MAX_ZOOM][X] / 2) * pow(2, camera.getZoom() - 2) > camera.getView(X) + MAIN_FRAME_SIZE[X] || 
					(sBlock->getOffset(Y) + BLOCK_SIZE_ISO[MAX_ZOOM][Y] / 2) * pow(2, camera.getZoom() - 2) > camera.getView(Y) + MAIN_FRAME_SIZE[Y])
					centerView(sBlock->getOffset(X), sBlock->getOffset(Y));
				break;
				
			case DOWN_RIGHT:				
				if((sBlock->getOffset(X) + BLOCK_SIZE_ISO[MAX_ZOOM][X] / 2) * pow(2, camera.getZoom() - 2) > camera.getView(X) + MAIN_FRAME_SIZE[X] || 
					(sBlock->getOffset(Y) + BLOCK_SIZE_ISO[MAX_ZOOM][Y] / 2) * pow(2, camera.getZoom() - 2) < camera.getView(Y))
					centerView(sBlock->getOffset(X), sBlock->getOffset(Y));
				break;
				
			case UP_LEFT:				
				if((sBlock->getOffset(X) + BLOCK_SIZE_ISO[MAX_ZOOM][X] / 2) * pow(2, camera.getZoom() - 2) < camera.getView(X) || 
					(sBlock->getOffset(Y) + BLOCK_SIZE_ISO[MAX_ZOOM][Y] / 2) * pow(2, camera.getZoom() - 2) > camera.getView(Y) + MAIN_FRAME_SIZE[Y])
					centerView(sBlock->getOffset(X), sBlock->getOffset(Y));
				break;
		}
	}
}

void LevelMap::centerView(GLshort x, GLshort y)
{	
	refresh();
	camera.centerOn(x, y);	
	
}
