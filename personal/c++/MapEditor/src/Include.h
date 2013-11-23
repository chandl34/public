#ifndef INCLUDE_H_
#define INCLUDE_H_

//#define SCROLLING
//#define ROTATING
//#define ZOOMING
#define PANNING
//#define OUTLINED

#include <math.h>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <iostream>
using namespace std;

const int WIDTH = 800, HEIGHT = 600;
enum{X, Y, Z};
enum{LEFT, RIGHT};
enum{FORWARD, BACKWARD};
enum{GROUND, DEBRIS, GRASS, DOOR, WALL,	
	OBJECT, FENCE, DOORFRAME, WINDOWFRAME, WINDOW};
enum{CLOSED, HALFOPEN, OPEN};
enum{UNBROKEN, BROKEN};

#endif /*INCLUDE_H_*/
