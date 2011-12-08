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

const GLshort SCREEN_PIXEL[] = {480, 320};
const GLshort MENU_SIZE[] = {SCREEN_PIXEL[X], 20};

const GLfloat EPSILON = 0.000001f;


//----- DRAW -----//
const GLshort DRAW_METHOD = GL_NEAREST;
const GLfloat STEP_DELAY = 3.0f/60.0f;  // 20 a second
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
const GLshort MAP_BLOCK_Y = MAP_SIDE*2 + 1;
const GLshort MAP_BLOCK[] = {MAP_BLOCK_X, MAP_BLOCK_Y};	// Extra end pieces are cut off

const GLshort BLOCK_SIZE_ISO[][2] = {						// Zoom based
20*pow(2, 0), 10*pow(2, 0),
20*pow(2, 1), 10*pow(2, 1),
20*pow(2, 2), 10*pow(2, 2),
};	


//--- 3D COORDS ---//
const GLshort BLOCK_SIZE_3D[] = {40, 40, 120};	// In inches
const GLshort MAP_SIZE_3D[] = {BLOCK_SIZE_3D[X]*MAP_SIDE*2, 
BLOCK_SIZE_3D[Y]*MAP_SIDE*2, 
0};

//--- MODEL ---//
enum{CONST_MODEL, ROTATE_MODEL, SIDE_MODEL, DOOR_MODEL};

const GLshort CONST_MODELS = 2;
enum{GROUND};

const GLshort ROTATE_MODELS = 2;
enum{UNIT, BULLET};

const GLshort SIDE_MODELS = 5;
enum{WALL, 
TOP_FRAME, BOTTOM_FRAME, FRONT_FRAME, SIDE_FRAME};
enum{LEFT_SIDE, RIGHT_SIDE};

const GLshort DOOR_MODELS = 1;
enum{DOOR};
enum{CLOSED, OPEN};
enum{OUTER, INNER};
enum{LEFT_HINGE, RIGHT_HINGE};


//----- CAMERA -----//
const GLshort MAX_ZOOM = 2;
const GLshort ZOOMS = 3;

const GLfloat MAP_OFFSET[2] = {
BLOCK_SIZE_ISO[MAX_ZOOM][X]*(MAP_SIDE/2.0f), 
-BLOCK_SIZE_ISO[MAX_ZOOM][Y]*((MAP_SIDE + 1)/2.0f),
};

const GLfloat Z_MOD = (BLOCK_SIZE_ISO[MAX_ZOOM][Y]*3.5f)/(GLfloat)BLOCK_SIZE_3D[Z];

const GLshort VIEW_SIZE[][2] = {
SCREEN_PIXEL[X]*pow(2, 2), SCREEN_PIXEL[Y]*pow(2, 2),
SCREEN_PIXEL[X]*pow(2, 1), SCREEN_PIXEL[Y]*pow(2, 1),
SCREEN_PIXEL[X]*pow(2, 0), SCREEN_PIXEL[Y]*pow(2, 0),
};

const GLshort CAMERA_BOUND[][2] = {
BLOCK_SIZE_ISO[0][X]*MAP_BLOCK[X] - SCREEN_PIXEL[X] - BLOCK_SIZE_ISO[0][X],		// cutting out the extra x-block in-between
BLOCK_SIZE_ISO[0][Y]*MAP_BLOCK[Y]/2 - SCREEN_PIXEL[Y] + 1.5f*BLOCK_SIZE_ISO[0][Y],

BLOCK_SIZE_ISO[1][X]*MAP_BLOCK[X] - SCREEN_PIXEL[X] - BLOCK_SIZE_ISO[1][X],		// cutting out the extra x-block in-between
BLOCK_SIZE_ISO[1][Y]*MAP_BLOCK[Y]/2 - SCREEN_PIXEL[Y] + 0.5f*BLOCK_SIZE_ISO[1][Y],

BLOCK_SIZE_ISO[2][X]*MAP_BLOCK[X] - SCREEN_PIXEL[X] - BLOCK_SIZE_ISO[2][X],		// cutting out the extra x-block in-between
BLOCK_SIZE_ISO[2][Y]*MAP_BLOCK[Y]/2 - SCREEN_PIXEL[Y],
};


const GLshort SCREEN_BLOCK[][2] = {
SCREEN_PIXEL[X]/(BLOCK_SIZE_ISO[0][X]/1.0f), 
(SCREEN_PIXEL[Y]-MENU_SIZE[Y])/(BLOCK_SIZE_ISO[0][Y]/2.0f),

SCREEN_PIXEL[X]/(BLOCK_SIZE_ISO[1][X]/1.0f), 
(SCREEN_PIXEL[Y]-MENU_SIZE[Y])/(BLOCK_SIZE_ISO[1][Y]/2.0f),

SCREEN_PIXEL[X]/(BLOCK_SIZE_ISO[2][X]/1.0f), 
(SCREEN_PIXEL[Y]-MENU_SIZE[Y])/(BLOCK_SIZE_ISO[2][Y]/2.0f),
};


//---- MOVABLE OBJECT ----//
enum{DEAD, NO_CHANGE, UPDATE_SIGHT};


//---- ISO SORTING ----//
enum{MIN_C, MID_C, MAX_C};

//---- STATS ----//
enum{GOOD, NEUTRAL, BAD};


//---- PATHING ----//
const GLshort PATH_DIRS = 8;
enum{DIAG, ORTH};
enum {DOWN_LEFT, LEFT, UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, ALL_DIR};

const GLshort DIR[/* currentY % 2 */][PATH_DIRS][2] = {
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

const GLfloat MOVE_COST[] = {1.0f, sqrt(2)};				// approximately x*sqRoot(2), x
const GLfloat MOVE_SPEED = 60.0f;							// 0 to 100 allowed
const GLshort MOVE_STEPS[] = {MOVE_COST[X]*(100.0f - MOVE_SPEED), 
MOVE_COST[Y]*(100.0f - MOVE_SPEED)};

const GLfloat MOVE_STEP_3D[PATH_DIRS][2] = {
-BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[DIAG], 
0,											// DOWN_LEFT

-BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[ORTH], 
BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[ORTH],// LEFT	

0, 
BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[DIAG],	// UP_LEFT	

BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[ORTH], 
BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[ORTH],	// UP	

BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[DIAG], 
0,											// UP_RIGHT	

BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[ORTH], 
-BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[ORTH],// RIGHT	

0, 
-BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[DIAG],// DOWN_RIGHT	

-BLOCK_SIZE_3D[X]/(GLfloat)MOVE_STEPS[ORTH], 
-BLOCK_SIZE_3D[Y]/(GLfloat)MOVE_STEPS[ORTH],// DOWN	
};


//---- SIGHT ----//
const GLfloat UNIT_VECTOR[/*dir*/][3] = {	
-1, 0, 0,
-sqrt(2)/2.0f, sqrt(2)/2.0f, 0, 
0, 1, 0,					
sqrt(2)/2.0f, sqrt(2)/2.0f, 0,
1, 0, 0,
sqrt(2)/2.0f, -sqrt(2)/2.0f, 0,
0, -1, 0,
-sqrt(2)/2.0f, -sqrt(2)/2.0f, 0,		
};


//----- UNIT -----//
enum{IDLE, MOVE, USE, SHOOT, LOOK};

#endif

