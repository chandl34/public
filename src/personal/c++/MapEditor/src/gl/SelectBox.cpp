#include "SelectBox.h"

int* SelectBox::coord = new int[3];

SelectBox::SelectBox(){
	coord[X] = 75;  coord[Y] = 0;  coord[Z] = 75;	
	id = glGenLists(1);
	glNewList(id, GL_COMPILE);{
		glLoadName(0);
		glColor3f(0, 0, 0);
		glBegin(GL_QUADS);{
			glVertex3f(0, 0.05f, 0);
			glVertex3f(1, 0.05f, 0);
			glVertex3f(1, 0.05f, 1);
			glVertex3f(0, 0.05f, 1);
		}
		glEnd();
	}
	glEndList();
}

void SelectBox::moveLeft(){
	if(coord[X] > 0 && LevelMap::getBlock(coord[X] - 1, coord[Z]) != NULL)
		coord[X]--;
}

void SelectBox::moveRight(){
	if(coord[X] < LevelMap::LEVEL_LENGTH - 1 && LevelMap::getBlock(coord[X] + 1, coord[Z]) != NULL)
		coord[X]++;
}

void SelectBox::moveForward(){
	if(coord[Z] > 0 && LevelMap::getBlock(coord[X], coord[Z] - 1) != NULL)
		coord[Z]--;
}

void SelectBox::moveBackward(){
	if(coord[Z] < LevelMap::LEVEL_LENGTH - 1 && LevelMap::getBlock(coord[X], coord[Z] + 1) != NULL)
		coord[Z]++;
}
