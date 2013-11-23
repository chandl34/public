#include "Block.h"

Block::Block(int x1, int z1){
	x = x1;
	z = z1;
}

Block::~Block(){}

void Block::draw(){
	glBegin(GL_QUADS);
	glColor3f(0, 0.5f, 0.5f);
	glVertex3f(x, 0, z);
	glVertex3f(x + 1, 0, z);
	glVertex3f(x + 1, 0, z + 1);
	glVertex3f(x, 0, z + 1);	
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(x, 0, z);
	glVertex3f(x + 1, 0, z);
	glVertex3f(x + 1, 0, z + 1);
	glVertex3f(x, 0, z + 1);	
	glEnd();
}
