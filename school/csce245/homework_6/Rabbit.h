// Jonathan Chandler
// Rabbit.h

#ifndef _RABBIT_H_
#define _RABBIT_H_

#include "Animal.h"

class Rabbit: public Animal{
	private:
		bool lazy;
	public:
                Rabbit(int x1, int y1, int t1, Grassland * g1, bool l);
               	virtual ~Rabbit(){}
		virtual bool doit(int i);
                virtual bool isRabbit(){return true;}
		bool isLazy(){return lazy;}
};

#endif
