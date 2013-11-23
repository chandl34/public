/*
 *  Math.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 10/19/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "Math.h"

#include "Include.h"


// Random 
int random(int max)
{
	return rand() % max;
}

bool roll(double comp)
{
	return compare(random(100001) / 1000.0, comp) != 1;
}


double degreeToRad(double deg)
{
	return deg * M_PI / 180.0;
}

double radToDegree(double rad)
{
	return rad / M_PI * 180.0;
}

// Comparison methods
int compare(double a, double b)
{
	if(a + EPSILON < b)
		return -1;
	if(a - EPSILON > b)
		return 1;
	return 0;
}

bool greaterThan(double a, double b)
{
	return a > b;
}

bool greaterThanOrEqualTo(double a, double b)
{
	return a >= b;
}

bool lessThan(double a, double b)
{
	return a < b;
}

bool lessThanOrEqualTo(double a, double b)
{
	return a <= b;
}