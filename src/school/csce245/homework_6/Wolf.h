// Jonathan Chandler
// Wolf.h

#ifndef _WOLF_H_
#define _WOLF_H_

#include "Animal.h"

class Wolf: public Animal{
	public:
	        Wolf(int x1, int y1, int t1, Grassland * g1);
               	virtual ~Wolf(){}
		virtual bool doit(int i);
                virtual bool isRabbit(){return false;}
};

#endif
