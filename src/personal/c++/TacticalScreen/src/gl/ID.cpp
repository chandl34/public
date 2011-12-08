#include "ID.h"

int id = 0;

int createID(){
	id++;
	return id;
}

void reset(){
	id = 0;
}
