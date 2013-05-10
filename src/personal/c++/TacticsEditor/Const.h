/*
 *  Const.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 7/21/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef CONST_H_
#define CONST_H_


//---- GENERAL ----//
enum{X, Y, Z};

const GLshort MAIN_FRAME_SIZE[] = {960, 640};
const GLshort INFO_FRAME_SIZE[] = {120, 640};
const GLshort MENU_HEIGHT = 20;

const double EPSILON = 0.00000001;


//----- DRAW -----//
const GLshort DRAW_METHOD = GL_LINEAR;
const double STEP_DELAY = 3.0/60.0;  // 20 a second
const GLshort SCREEN_TEX_VERT[] = {
	512, 0,
	0, 0,
	512, 512,
	0, 512
	/*	0, 512,
	 0, 0,
	 512, 512,
	 512, 0*/
};

const GLshort FRAMES_PER_SECOND = 60;


//----- SCREENS -----//
enum{MAP_SCREEN};


//----- TOUCH -----//
const GLshort DRAG_THRESHOLD = 16;		// Limit to how much you can move your touch before it's considered a drag


//----- MAP -----//
const GLshort MAP_SIDE = 80;
const GLshort MAP_BLOCK_X = MAP_SIDE + 1;
const GLshort MAP_BLOCK_Y = MAP_SIDE*2 + 1;
const GLshort MAP_BLOCK[] = {MAP_BLOCK_X, MAP_BLOCK_Y};	// Extra end pieces are cut off

const GLshort BLOCK_SIZE_ISO[/*ZOOM*/][2] = {	
	20*pow(2, 0), 10*pow(2, 0),
	20*pow(2, 1), 10*pow(2, 1),
	20*pow(2, 2), 10*pow(2, 2)
};	


//--- 3D COORDS ---//
const GLshort BLOCK_SIZE_3D[] = {40, 40, 3*40};
const GLshort MAP_SIZE_3D[] = 
{BLOCK_SIZE_3D[X]*MAP_SIDE*2, 
	BLOCK_SIZE_3D[Y]*MAP_SIDE*2, 
	0};
const GLshort MAX_DISTANCE = MAP_BLOCK_Y*BLOCK_SIZE_3D[Y];

//--- MODEL ---//
enum{CONST_MODEL, ROTATE_MODEL, SIDE_MODEL, DOOR_MODEL};

const GLshort OBJECT_OPTIONS = 4;
enum{GROUND_S, WALL_S, WINDOW_S, DOOR_S};

const GLshort CONST_MODELS = 2;
enum{GROUND, PROJECTILE};

const GLshort SIDE_MODELS = 5;
enum{WALL, 
	FRONT_FRAME, SIDE_FRAME, TOP_FRAME, BOTTOM_FRAME};
enum{LEFT_SIDE, RIGHT_SIDE};

const GLshort DOOR_MODELS = 1;
enum{DOOR};
enum{CLOSED, OPEN};
enum{OUTER, INNER};
enum{LEFT_HINGE, RIGHT_HINGE};


//---- PATHING ----//
const GLshort PATH_DIRS = 8;
enum{DIAG, ORTH};
enum {DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, ALL_DIR};

const GLshort PATH_DIR[/* currentY % 2 */][PATH_DIRS][2] = {
	{-1, -1,// DOWN_LEFT
		-1, 0,	// LEFT	
		-1, 1,	// UP_LEFT
		0, 2,	// UP	
		0, 1,	// UP_RIGHT	
		1, 0,	// RIGHT	
		0, -1,	// DOWN_RIGHT	
		0, -2,},// DOWN	
	
	{0, -1,	// DOWN_LEFT
		-1, 0,	// LEFT	
		0, 1,	// UP_LEFT
		0, 2,	// UP	
		1, 1,	// UP_RIGHT		
		1, 0,	// RIGHT	
		1, -1,	// DOWN_RIGHT	
		0, -2,},// DOWN		
};


//----- ITEM -----//
const GLshort ITEM_TYPES = 5;
enum{ITEM, AMMO, GRENADE, GUN, ARMOR, ANY_ITEM};

const GLshort AMMO_TYPES = 2;
enum{AMMO_9MM, AMMO_7_62};

const GLshort UNIT_CONTAINERS = 7;
const GLshort GROUND_CONTAINER = 8;

const GLshort BACKPACK_SIZE_X = 10;
const GLshort BACKPACK_SIZE_Y = 6;
const GLshort BACKPACK_SIZE[] = {BACKPACK_SIZE_X, BACKPACK_SIZE_Y};

const GLshort GROUND_SIZE[] = {15, 4};

const GLshort ITEM_SLOT_SIZES = 5;
enum{IS_1_1, IS_1_2, IS_2_2, IS_3_3, IS_2_4};


//----- CAMERA -----//
const GLshort MAX_ZOOM = 2;

const GLshort MAP_SIZE_ISO[/*ZOOM*/][2] = {
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[0][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[0][Y],
	
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[1][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[1][Y],
	
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[2][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[2][Y],
};

const double MAP_OFFSET[2] = {
	BLOCK_SIZE_ISO[MAX_ZOOM][X]*(MAP_SIDE/2.0), 
	-BLOCK_SIZE_ISO[MAX_ZOOM][Y]*((MAP_SIDE + 1)/2.0),
};

const double Z_MOD = (BLOCK_SIZE_ISO[MAX_ZOOM][Y]*3.5)/(double)BLOCK_SIZE_3D[Z];

const GLshort VIEW_SIZE[/*ZOOM*/][2] = {
	MAIN_FRAME_SIZE[X] * pow(2, 2), MAIN_FRAME_SIZE[Y] * pow(2, 2),
	MAIN_FRAME_SIZE[X] * pow(2, 1), MAIN_FRAME_SIZE[Y] * pow(2, 1),
	MAIN_FRAME_SIZE[X] * pow(2, 0), MAIN_FRAME_SIZE[Y] * pow(2, 0),
};

const GLshort MAP_VIEW_SIZE[/*ZOOM*/][2] = {
	VIEW_SIZE[0][X], VIEW_SIZE[0][Y],
	VIEW_SIZE[1][X], VIEW_SIZE[1][Y],
	VIEW_SIZE[2][X], VIEW_SIZE[2][Y],
};

const GLshort CAMERA_BOUND[/*ZOOM*/][2] = {
	MAP_SIZE_ISO[0][X] - BLOCK_SIZE_ISO[0][X] - MAIN_FRAME_SIZE[X],
	MAP_SIZE_ISO[0][Y] - BLOCK_SIZE_ISO[0][Y] - (MAIN_FRAME_SIZE[Y]),
	
	MAP_SIZE_ISO[1][X] - BLOCK_SIZE_ISO[1][X] - MAIN_FRAME_SIZE[X],
	MAP_SIZE_ISO[1][Y] - BLOCK_SIZE_ISO[1][Y] - (MAIN_FRAME_SIZE[Y]),
	
	MAP_SIZE_ISO[2][X] - BLOCK_SIZE_ISO[2][X] - MAIN_FRAME_SIZE[X],
	MAP_SIZE_ISO[2][Y] - BLOCK_SIZE_ISO[2][Y] - (MAIN_FRAME_SIZE[Y]),
};


const GLshort SCREEN_BLOCK[/*ZOOM*/][2] = {
	MAIN_FRAME_SIZE[X]/(BLOCK_SIZE_ISO[0][X]/1.0), 
	(MAIN_FRAME_SIZE[Y])/(BLOCK_SIZE_ISO[0][Y]/2.0),
	
	MAIN_FRAME_SIZE[X]/(BLOCK_SIZE_ISO[1][X]/1.0), 
	(MAIN_FRAME_SIZE[Y])/(BLOCK_SIZE_ISO[1][Y]/2.0),
	
	MAIN_FRAME_SIZE[X]/(BLOCK_SIZE_ISO[2][X]/1.0), 
	(MAIN_FRAME_SIZE[Y])/(BLOCK_SIZE_ISO[2][Y]/2.0),
};


//---- INTERUPTS ----//
enum{INT_ON_NONE, INT_ON_NEW, INT_ON_ANY};


//---- ISO SORTING ----//
enum{MINIMUM, MIDDLE, MAXIMUM};
enum{SORT_DYNAMIC, SORT_STATIC, SORT_ALL};


//---- UI ----//
const GLshort CURSOR_MODES = 1;
enum{MOVE};

#endif
