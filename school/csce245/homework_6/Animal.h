// Jonathan Chandler
// Animal.h

#ifndef _ANIMAL_H_
#define _ANIMAL_H_

#include "Item.h"
#include "Grassland.h"

class Animal: public Item{
	protected:
		int x, y;
		int born;
		int lastEat;
		Grassland * g;
	public:
		Animal(int x1, int y1, int t1, Grassland * g1);
		virtual ~Animal(){}
		int getX(){return x;}
		int getY(){return y;}
		virtual bool doit(int i) = 0;
		virtual bool isRabbit() = 0;
};
#endif
