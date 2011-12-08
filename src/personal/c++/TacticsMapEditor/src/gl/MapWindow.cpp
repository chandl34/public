#include "MapWindow.h"

MapWindow::MapWindow(int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	redraw();
}

MapWindow::~MapWindow(){
	delete camera;
}

void MapWindow::init(){
	glClearColor(0.75f, 0.9f, 1.0f, 0.0f);
	glClearDepth(1.0f);		
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);		
	glBlendFunc(GL_DST_COLOR, GL_ZERO);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	camera = new Camera();
	int w, h;
	cout << "Map size (Format:  width height / Size Limit:  10-15) ::  " << endl;
	while(true){
		cin >> w;
		cin >> h;
		if(w >= 10 && h >= 10 && w <= 15 && h <= 15)
			break;
		else
			cout << "Invalid input." << endl;		
	}
	map = new Map(w, h);
	Fl::add_timeout(1.0/10.0, Timer_CB, (void*)this);       // 24fps timer
}

void MapWindow::Timer_CB(void *userdata){
	MapWindow *glwin = (MapWindow*)userdata;
	glwin->redraw();
	Fl::repeat_timeout(1.0/20.0, Timer_CB, userdata);
}

void MapWindow::draw(){
	if (!valid()) {
		valid(1);
		init();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	view();
	map->draw();
}

void MapWindow::view(){
	//glOrtho(-12.0f, 12.0f, -10.0, 10.0f, -100.0f, 100.0f);
	glOrtho(-14.15f, 14.15f, -9.4f, 9.4f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();		

	glTranslatef(camera->getPan(X), camera->getPan(Y), camera->getPan(Z));	

	glRotatef(camera->getRotate(X), 1.0f, 0.0f, 0.0f);
	glRotatef(camera->getRotate(Y), 0.0f, 1.0f, 0.0f);
	glRotatef(camera->getRotate(Z), 0.0f, 0.0f, 1.0f);
	
	glTranslatef(-map->getWidth()*0.5f, 0, -map->getHeight()*0.5f);	
}
