/*
 *  Math.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef MATH_H_
#define MATH_H_


// Random 
int random(int);
bool roll(double);	// compares percent, with three significant digits

double degreeToRad(double);
double radToDegree(double);

// Comparison methods
int compare(double, double);
bool greaterThan(double, double);
bool greaterThanOrEqualTo(double, double);
bool lessThan(double, double);
bool lessThanOrEqualTo(double, double);

#endif
