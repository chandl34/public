#ifndef SHIP_C34_H_
#define SHIP_C34_H_

#include "GameObject.h"

#include <list>


class Ship;

typedef std::shared_ptr<Ship> ShipPtr;
typedef std::list<Coord2d<float> > PointList;


class Ship
: public GameObject
{
public:
	Ship();
	
	// Draw
	void input(int);
};

#endif
