#include "Ground.h"

Ground::Ground(){
	ground = NULL; 
	grass = NULL;
}

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

void Ground::setGround(UnbreakableModel* m){
	if(ground != NULL)
		delete ground;
	ground = m;
}

void Ground::setGrass(UnbreakableModel* m){
	if(grass != NULL)
		delete grass;
	grass = m;
}

void Ground::addDebris(UnbreakableModel* m){
	debris.push_back(m);
}

void Ground::clear(){
	delete grass;
	grass = NULL;
	for(size_t i = 0; i < debris.size(); i++)
		delete debris.at(i);
	debris.clear();
}

void Ground::draw(int x, int z){
	if(ground != NULL)
		ground->draw(x, 0, z);
	if(grass != NULL)
		grass->draw(x, 0, z);
	for(size_t i = 0; i < debris.size(); i++)
		debris.at(i)->draw(x, 0, z);

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
