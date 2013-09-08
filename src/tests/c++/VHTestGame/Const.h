#ifndef CONST_C34_H_
#define CONST_C34_H_

// General
enum{X, Y};
enum{R, G, B};

const double EPSILON = 0.00000001f;


// Screen
const int SCREEN_SIZE[]			= {800, 600};
const int SCREEN_ERROR[]		= { 16,  38};
const int GAME_SCREEN_SIZE[]	= {600, 600};
const int PAUSE_SCREEN_SIZE[]	= {300, 200};
const int STAT_SCREEN_SIZE[]	= {200, 600};

// Gameplay
const int UPDATE_TIME = 25;

// Input
enum{UP, DOWN, CCW_ROT, CC_ROT, STOP_ROT, SHOOT};


#endif