#include "Map_Window.h"

LevelMap* Map_Window::levelMap;

Map_Window::Map_Window(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	Fl::add_timeout(1.0/15.0, Timer_CB, (void*)this);       // 24fps timer
}

Map_Window::~Map_Window(){
	delete camera;
	delete select;
	delete levelMap;
}

void Map_Window::init(){
	glClearColor(0.75f, 0.9f, 1.0f, 0.0f);
	glClearDepth(1.0f);		
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);		
	glBlendFunc(GL_DST_COLOR, GL_ZERO); 
	glShadeModel(GL_SMOOTH);	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	//glLineWidth(2);

	camera = new Camera();   
	select = new SelectBox();    
	levelMap = new LevelMap();
	levelMap->init();
}

LevelMap& Map_Window::getMap(){
	return *levelMap;
}

LevelMap& Map_Window::getNewMap(){
	delete levelMap;
	levelMap = new LevelMap();
	return *levelMap;
}

void Map_Window::Timer_CB(void *userdata){
	Map_Window *glwin = (Map_Window*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0/15.0, Timer_CB, userdata);
}

void Map_Window::draw(){
	if (!valid()) {
		valid(1);
		init();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
#ifdef SCROLLING
	camera->scroll();
#endif //SCROLLING
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	view();

	glMatrixMode(GL_MODELVIEW);

	glBegin(GL_QUADS);
	glVertex3f(75, 75, 0);
	glVertex3f(75, 90, 0);
	glVertex3f(90, 90, 0);
	glVertex3f(90, 75, 0);
	glEnd();

	drawMap();
}

void Map_Window::view(){
	if(!camera->isOrthogonal())
		gluPerspective(50.0f, 1024.0f/768.0f, 1.0, 1000.0);
	else
		//glOrtho(-14.0f, 14.0f, -13.0f, 13.0f, -100.0f, 100.0f);
		//glOrtho(-12.0f, 12.0f, -11.75, 11.75f, -100.0f, 100.0f);
		glOrtho(-12.0f, 12.0f, -10.0, 10.0f, -100.0f, 100.0f);
}
void Map_Window::drawMap(){
	glLoadIdentity();			

	glTranslatef(camera->getPan(X), camera->getPan(Y), camera->getPan(Z));	

	glRotatef(camera->getRotate(X), 1.0f, 0.0f, 0.0f);
	glRotatef(camera->getRotate(Y), 0.0f, 1.0f, 0.0f);
	glRotatef(camera->getRotate(Z), 0.0f, 0.0f, 1.0f);

	glTranslatef(-LevelMap::LEVEL_OFFSET, 0, -LevelMap::LEVEL_OFFSET);

	if(levelMap->needsUpdate())
		levelMap->refreshMap();

	glPushMatrix(); //PUSH 1
	glTranslatef(select->get(X), select->get(Y) * 0.5f, select->get(Z));

	glCallList(select->getID());

	glPopMatrix(); //POP 1		
	glCallList(levelMap->getID());	

}
