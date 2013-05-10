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

const GLshort SCREEN_SIZE[] = {480, 320};
const GLshort MENU_SIZE[] = {SCREEN_SIZE[X], 40};

const double EPSILON = 0.00000001;


//----- DRAW -----//
const GLshort DRAW_METHOD = GL_NEAREST;
const GLshort FRAMES_PER_SECOND = 30;

const GLshort SCREEN_TEX_VERT[] = {
	0, 512,
	0, 0,
	512, 512,
	512, 0
};


//----- TOUCH -----//
const GLshort DRAG_THRESHOLD = 16;		// Limit to how much you can move your touch before it's considered a drag


//----- MAP -----//
const GLshort MAP_SIDE = 80;
const GLshort MAP_BLOCK_X = MAP_SIDE + 1;
const GLshort MAP_BLOCK_Y = MAP_SIDE * 2 + 1;
const GLshort MAP_BLOCK[] = {MAP_BLOCK_X, MAP_BLOCK_Y};	// Extra end pieces are cut off


//--- 3D COORDS ---//
const GLshort BLOCK_SIZE_3D[] = {40, 40, 3 * 40};
/*
const GLshort MAP_SIZE_3D[] = {
	BLOCK_SIZE_3D[X] * MAP_SIDE * 2, 
	BLOCK_SIZE_3D[Y] * MAP_SIDE * 2, 
	0
};
const GLshort MAX_DISTANCE = MAP_BLOCK_Y * BLOCK_SIZE_3D[Y];
*/
 
//--- MODEL ---//
enum{CONST_MODEL, ROTATE_MODEL, SIDE_MODEL, DOOR_MODEL};

const GLshort CONST_MODELS = 3;
enum{GROUND, BULLET, THROWN_ITEM};

const GLshort ROTATE_MODELS = 4;
enum{LEGS, TORSO, HEAD, UNIT};

const GLshort SIDE_MODELS = 5;
enum{WALL, 
	FRONT_FRAME, SIDE_FRAME, TOP_FRAME, BOTTOM_FRAME};
enum{LEFT_SIDE, RIGHT_SIDE};

const GLshort DOOR_MODELS = 1;
enum{DOOR};
enum{CLOSED, OPEN};
enum{OUTER, INNER};
enum{LEFT_HINGE, RIGHT_HINGE};


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

const GLshort BLOCK_SIZE_ISO[/*ZOOM*/][2] = {	
	20 * pow(2, 0), 10 * pow(2, 0),
	20 * pow(2, 1), 10 * pow(2, 1),
	20 * pow(2, 2), 10 * pow(2, 2)
};	

const GLshort MAP_SIZE_ISO[/*ZOOM*/][2] = {
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[0][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[0][Y],
	
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[1][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[1][Y],
	
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[2][X],
	MAP_BLOCK[X] * BLOCK_SIZE_ISO[2][Y],
};

const double MAP_OFFSET[2] = {
	BLOCK_SIZE_ISO[MAX_ZOOM][X] * (MAP_SIDE / 2.0), 
	-BLOCK_SIZE_ISO[MAX_ZOOM][Y] * ((MAP_SIDE + 1) / 2.0),
};

const double Z_MOD = (BLOCK_SIZE_ISO[MAX_ZOOM][Y] * 3.5) / (double)BLOCK_SIZE_3D[Z];

const GLshort VIEW_SIZE[/*ZOOM*/][2] = {
	SCREEN_SIZE[X] * pow(2, 2), SCREEN_SIZE[Y] * pow(2, 2),
	SCREEN_SIZE[X] * pow(2, 1), SCREEN_SIZE[Y] * pow(2, 1),
	SCREEN_SIZE[X] * pow(2, 0), SCREEN_SIZE[Y] * pow(2, 0),
};

const GLshort MAP_VIEW_SIZE[/*ZOOM*/][2] = {
	VIEW_SIZE[0][X], VIEW_SIZE[0][Y] - MENU_SIZE[Y] * pow(2, 2),
	VIEW_SIZE[1][X], VIEW_SIZE[1][Y] - MENU_SIZE[Y] * pow(2, 1),
	VIEW_SIZE[2][X], VIEW_SIZE[2][Y] - MENU_SIZE[Y] * pow(2, 0),
};

const GLshort CAMERA_BOUND[/*ZOOM*/][2] = {
	MAP_SIZE_ISO[0][X] - BLOCK_SIZE_ISO[0][X] - SCREEN_SIZE[X],
	MAP_SIZE_ISO[0][Y] - BLOCK_SIZE_ISO[0][Y] - (SCREEN_SIZE[Y] - MENU_SIZE[Y]),
	
	MAP_SIZE_ISO[1][X] - BLOCK_SIZE_ISO[1][X] - SCREEN_SIZE[X],
	MAP_SIZE_ISO[1][Y] - BLOCK_SIZE_ISO[1][Y] - (SCREEN_SIZE[Y] - MENU_SIZE[Y]),
	
	MAP_SIZE_ISO[2][X] - BLOCK_SIZE_ISO[2][X] - SCREEN_SIZE[X],
	MAP_SIZE_ISO[2][Y] - BLOCK_SIZE_ISO[2][Y] - (SCREEN_SIZE[Y] - MENU_SIZE[Y]),
};


const GLshort SCREEN_BLOCK[/*ZOOM*/][2] = {
	SCREEN_SIZE[X] / (BLOCK_SIZE_ISO[0][X] / 1.0), 
	(SCREEN_SIZE[Y] - MENU_SIZE[Y]) / (BLOCK_SIZE_ISO[0][Y] / 2.0),
	
	SCREEN_SIZE[X] / (BLOCK_SIZE_ISO[1][X] / 1.0), 
	(SCREEN_SIZE[Y] - MENU_SIZE[Y]) / (BLOCK_SIZE_ISO[1][Y] / 2.0),
	
	SCREEN_SIZE[X] / (BLOCK_SIZE_ISO[2][X] / 1.0), 
	(SCREEN_SIZE[Y] - MENU_SIZE[Y]) / (BLOCK_SIZE_ISO[2][Y] / 2.0),
};


//---- MINIMAP ----//
const double MINIMAP_MOD = 15.0;
const GLshort MINIMAP_VIEW_SIZE[] = {
	SCREEN_SIZE[X] * MINIMAP_MOD, 
	SCREEN_SIZE[Y] * MINIMAP_MOD
};

const GLshort MINIMAP_SIZE[] = {
	MAP_SIZE_ISO[MAX_ZOOM][X] / MINIMAP_MOD,
	MAP_SIZE_ISO[MAX_ZOOM][Y] / MINIMAP_MOD
};

const GLshort MINIMAP_OFFSET[] = {
	(MINIMAP_VIEW_SIZE[X] - MAP_SIZE_ISO[MAX_ZOOM][X] + BLOCK_SIZE_ISO[MAX_ZOOM][X]) / 2.0f,
	(MINIMAP_VIEW_SIZE[Y] - MAP_SIZE_ISO[MAX_ZOOM][Y] + BLOCK_SIZE_ISO[MAX_ZOOM][Y]) / 2.0f
};


//---- INTERUPTS ----//
enum{INT_ON_NONE, INT_ON_NEW, INT_ON_ANY};


//---- ISO SORTING ----//
enum{MINIMUM, MIDDLE, MAXIMUM};
enum{SORT_DYNAMIC, SORT_STATIC, SORT_ALL};


//----- TEAMS -----//
const GLshort TEAMS_PER_FIGHT = 2;
const GLshort TEAMS_PER_LEVEL = 3;
enum{OWNER, INTRUDER, FREE};


//----- UNIT -----//
enum{PLAYER, ENEMY};

enum{NO_CHANGE, DIED, STOPPED};
enum{CHANGED = 2};

const GLshort UNIT_MODES = 5;
enum{MOVE, USE, THROW, LOOK, TOGGLE, KNEEL, RELOAD, IDLE};

const GLshort MOVE_COST[] = {2, 3};
const GLshort USE_COST = 10;
const GLshort THROW_COST = 8;
const GLshort LOOK_COST = 1;
const GLshort TOGGLE_COST = 3;
const GLshort KNEEL_COST = 2;
const GLshort RELOAD_COST = 5;
const GLshort PICK_UP_COST = 2;

const GLshort STANCES = 2;
enum{STANDING, ON_KNEE};

const GLshort BODY_PARTS = 3;
//enum{LEGS, TORSO, HEAD};
const GLshort HEIGHT[][3] = {
	32, 60, 69,
	22, 37, 48
};


//---- PATHING ----//
const GLshort PATH_DIRS = 8;
enum{DIAG, ORTH};
enum {DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, ALL_DIR};

const GLshort DIR[/* currentY % 2 */][PATH_DIRS][2] = {
	{
		-1, -1,	// DOWN_LEFT
		-1, 0,	// LEFT	
		-1, 1,	// UP_LEFT
		0, 2,		// UP	
		0, 1,		// UP_RIGHT	
		1, 0,		// RIGHT	
		0, -1,	// DOWN_RIGHT	
		0, -2,	// DOWN
	},	
	
	{
		0, -1,	// DOWN_LEFT
		-1, 0,	// LEFT	
		0, 1,		// UP_LEFT
		0, 2,		// UP	
		1, 1,		// UP_RIGHT		
		1, 0,		// RIGHT	
		1, -1,	// DOWN_RIGHT	
		0, -2,	// DOWN
	},		
};


//---- SIGHT ----//
const double UNIT_VECTOR[/*dir*/][3] = {	
	-1, 0, 0,
	-sqrt(2)/2.0, sqrt(2)/2.0, 0, 
	0, 1, 0,					
	sqrt(2)/2.0, sqrt(2)/2.0, 0,
	1, 0, 0,
	sqrt(2)/2.0, -sqrt(2)/2.0, 0,
	0, -1, 0,
	-sqrt(2)/2.0, -sqrt(2)/2.0, 0,		
};

const double DIR_ANGLE[/*dir*/] = {
	M_PI,
	3 * M_PI_4,
	M_PI_2,
	M_PI_4,
	0,
	-M_PI_4,
	-M_PI_2,
	-3 * M_PI_4
};

const GLshort WINDOW_FRAME_HEIGHT = 38;

const GLshort LOS_LEVELS = 4;
enum{FULL_LOS, MID_LOS, LOW_LOS, NO_LOS};

const GLshort VIEWS = 3;
enum{VIEWED, VIEWABLE, DOOR_VIEW};

// This means a unit will move 2 steps to get behind a window from full sight
// Or two steps to get from behind a window being completely unseen
const GLshort DANGER_LEVELS = 3;
const GLshort DANGER_LEVEL[DANGER_LEVELS] = {8, 6, 4};

const GLshort LOS_OFFSET = 6;
const GLshort LOS_MIN_HEIGHT[LOS_LEVELS] = {
	0 - LOS_OFFSET,
	HEIGHT[ON_KNEE][LEGS] - LOS_OFFSET,
	HEIGHT[STANDING][LEGS] - LOS_OFFSET,	
	HEIGHT[STANDING][HEAD] - LOS_OFFSET,
};


//---- UI ----//
const GLshort CHARACTERS = 96;
const GLshort CHAR_OFFSET = 32;
const GLshort CHAR_NUM_OFFSET = 48;

const GLshort UI_IMAGES = 1;
enum{UNIT_ICON};

const GLshort UNIT_ICON_SIZE[] = {90, 30};


#endif

