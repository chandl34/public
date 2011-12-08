#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <stack>
#include <list>
#include <set>
#include <FL/Fl.H>
#include <FL/Gl.H>
#include <FL/Glu.H>
#include <FL/Fl_Gl_Window.H>
#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
using namespace std;


#define SCROLLING			// Screen scrolls when you touch the edges
//#define SCROLLWITHKEYBOARD	//ASDW 
#define OUTLINED			// Ground is outlined in a grid
#define CHARMOVED  			// Recalculate path if other character moved

#define EPSILON 0.000001

const int LEVEL_LENGTH = 150, LEVEL_OFFSET = 75;

enum{VISIBLE, KNOWN, INVISIBLE};

enum{X, Y, Z};
enum{LEFT, RIGHT};
enum{DIR_LEFT, DIR_FRONT_LEFT, DIR_FRONT, DIR_FRONT_RIGHT,
	DIR_RIGHT, DIR_BACK_RIGHT, DIR_BACK, DIR_BACK_LEFT};

enum{MOVE, SHOOT, USE, LOOK};
	
enum{PLAYER, ENEMY, NPC};
enum{MALE, FEMALE};
enum{HEAD, RIGHTLEG, LEFTLEG, TORSO, 
	RIGHTARM, LEFTARM, GUN, GUNPOS};
enum{HIT_WINDOWFRAME = 4, HIT_OBJECT, HIT_GROUND, HIT_BOUNDS};
enum{RIFLE, SMG, PISTOL};
enum{BULLET, GRENADE, SIGHT};

enum{GROUND, DEBRIS, GRASS, DOOR, WALL,	
	OBJECT, FENCE, DOORFRAME, WINDOWFRAME, WINDOW};
enum{CLOSED, HALFOPEN, OPEN};
enum{UNBROKEN, BROKEN};

#endif /*INCLUDE_H_*/
