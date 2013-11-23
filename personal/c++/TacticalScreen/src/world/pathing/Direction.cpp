#include "Direction.h"

Direction::Direction(int i, int x, int y, float c, float s){
	index = i;
	dir = new int[2];
	dir[X] = x; dir[Y] = y;
	sine = s; cosine = c;
}

Direction::~Direction(){
	delete [] dir;
}

int Direction::get(int c){
	return dir[c];
}

int Direction::getIndex(){
	return index;
}

float Direction::getSin(){
	return sine;
}

float Direction::getCos(){
	return cosine;
}
