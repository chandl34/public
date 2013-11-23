#include "Game_Window.h"

Camera* Game_Window::camera;
Cursor* Game_Window::cursor;
World* Game_Window::world;
int Game_Window::_width;
int Game_Window::_height;

Game_Window::Game_Window(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	loaded = false;
	Fl::add_timeout(1.0/20.0, Timer_CB, (void*)this);       // 24fps timer
	_width = w;
	_height = h;
}

Game_Window::~Game_Window(){
	delete camera;
	delete cursor;
	delete world;
}

void Game_Window::init(){
	glClearColor(0.75f, 0.9f, 1.0f, 0.0f);
	glClearDepth(1.0f);		
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);		
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	world = new World();
	camera = new Camera();   
	cursor = new Cursor();
	loaded = true;
}

void Game_Window::Timer_CB(void *userdata){
	Game_Window *glwin = (Game_Window*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0/20.0, Timer_CB, userdata);
}

void Game_Window::draw(){
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
	drawMap();	
	if(Camera::getScroll(X) == Camera::NO_SCROLL && 
			Camera::getScroll(Y) == Camera::NO_SCROLL)
		Cursor::draw();	
}

void Game_Window::view(){
	//glOrtho(-12.0f, 12.0f, -10.0, 10.0f, -100.0f, 100.0f);
	glOrtho(-14.15f, 14.15f, -9.4f, 9.4f, -100.0f, 100.0f);
	//glOrtho(-7.075f, 7.075, -4.7f, 4.7f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		

	glTranslatef(camera->getPan(X), camera->getPan(Y), camera->getPan(Z));	

	glRotatef(camera->getRotate(X), 1.0f, 0.0f, 0.0f);
	glRotatef(camera->getRotate(Y), 0.0f, 1.0f, 0.0f);
	glRotatef(camera->getRotate(Z), 0.0f, 0.0f, 1.0f);

	glTranslatef(-LEVEL_OFFSET, 0, -LEVEL_OFFSET);
}

void Game_Window::drawMap(){
	if(World::getSelectedMap()->needsUpdate())
		World::getSelectedMap()->refreshMap();

	World::getSelectedMap()->drawCharacters();
	World::getSelectedMap()->drawProjectiles();
	for(int i = 0; i < 10; i++)
		glCallList(World::getSelectedMap()->getID(i));	
}

void Game_Window::drawDoors(){
	glCallList(World::getSelectedMap()->getID(DOOR));	
}

void Game_Window::drawCharacters(){
	World::getSelectedMap()->drawCharacters();
}

int Game_Window::width(){return _width;}
int Game_Window::height(){return _height;}
