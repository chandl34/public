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

const double EPSILON = 0.00000001;


//----- DRAW -----//
const GLshort DRAW_METHOD = GL_LINEAR;
const GLshort FRAMES_PER_SECOND = 30;


//----- TOUCH -----//
const GLshort DRAG_THRESHOLD = 16;		// Limit to how much you can move your touch before it's considered a drag


//----- SCREENS -----//
const GLshort SCREENS = 2;
enum{TITLE_SCREEN, GAME_SCREEN};


//----- PIECES -----//
enum{MINIMUM, MAXIMUM};
enum{LEFT, DOWN, RIGHT, UP};
enum{IN, OUT, EDGE};
const GLshort OFFSET = 20;		// todo: change images so this is consistently true

#endif

