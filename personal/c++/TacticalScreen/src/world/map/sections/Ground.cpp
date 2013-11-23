#include "Ground.h"

Ground::Ground(){}

Ground::~Ground(){
	delete ground;
	delete grass;
	for(size_t i = 0; i < debris.size(); i++)
		delete debris.at(i);	
}

void Ground::load(){
	if(ground != NULL)
		ground->load();
	if(grass != NULL)
		grass->load();
	for(size_t i = 0; i < debris.size(); i++)
		debris.at(i)->load();	
}

void Ground::draw(int t, int x, int y, int z){
	if(t == GROUND){
		if(ground != NULL)
			ground->draw(x, y, z);
#ifdef OUTLINED
		// Outline
		glColor3f(0, 0, 0);
		glBegin(GL_LINE_LOOP);
		glVertex3f(x, 0, z);
		glVertex3f(x + 1, 0, z);
		glVertex3f(x + 1, 0, z + 1);
		glVertex3f(x, 0, z + 1);
		glEnd();
#endif //OUTLINED
	}
	else if(t == GRASS){
		if(grass != NULL)
			grass->draw(x, y, z);
	}
	else{
		for(size_t i = 0; i < debris.size(); i++)
			debris.at(i)->draw(x, y, z);
	}
}
