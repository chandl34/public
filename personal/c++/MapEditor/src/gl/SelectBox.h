#ifndef SELECTBOX_H_
#define SELECTBOX_H_

#include <FL/Gl.H>
#include "../Include.h"

class LevelMap;

class SelectBox{
public:
	SelectBox();
	virtual ~SelectBox(){delete [] coord;}

	static void moveLeft();
	static void moveRight();
	static void moveForward();
	static void moveBackward();
	int getID(){return id;}
	static int get(int c){return coord[c];}
	
private:
	static int* coord;	
	int id;
};

#include "../map/LevelMap.h"

#endif /*SELECTBOX_H_*/
