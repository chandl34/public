/*
 *  Options.h
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 5/30/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

// Cheat options
const bool AI_ON = true;
const bool ALWAYS_HIT = false;
const bool UNLIMITED_TU = !AI_ON;
const bool GOD_MODE = true;
const bool VIEW_360 = false;	// todo: make this so it actually views 360, not just graphically

// Extra info
const bool SHOW_LOS = true;
const bool SHOW_FPS = false;

// Optimization
const bool USE_BUFFERS = true;

// Other
const bool BLEND_WALLS = false;

// New Hires
const GLshort MAX_NEW_HIRES = 5;
const GLshort MIN_NEW_HIRES = 1;

const GLshort MAX_NEW_HIRE_HP = 50;
const GLshort MIN_NEW_HIRE_HP = 20;

const GLshort MAX_NEW_HIRE_TU = 50;
const GLshort MIN_NEW_HIRE_TU = 20;

#endif
