// Jonathan Chandler
// Grassland.h

#ifndef _GRASSLAND_H_
#define _GRASSLAND_H_

#include "Item.h"
#include "PQ.h"

class Grassland: public Item{
	private:
		int wolf, aRabbit, lRabbit;
		Item *** animal;
		int ** grass;
		PQ * queue;
		
	public:
		Grassland(int w, int ar, int lr);
		virtual ~Grassland();
		virtual bool doit(int t);
		bool available(int x, int y){return animal[x][y] == NULL;}
		Item * getAnimal(int x, int y){return animal[x][y];}
		void setAnimal(int x, int y, Item * a){animal[x][y] = a;}
		bool hasGrass(int t, int x, int y){
			if(t - grass[x][y] >= 10) 
				return true;
			return false;
		}	
		void killWolf(Item * dead, int x, int y);
		void killARabbit(Item * dead, int x, int y);
		void killLRabbit(Item * dead, int x, int y);
		void killGrass(int t, int x, int y){grass[x][y] = t;}
};

#endif
