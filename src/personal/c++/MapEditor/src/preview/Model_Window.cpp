#include "Model_Window.h"

Model_Window::Model_Window(int t, int x, int y, int w, int h) : Fl_Gl_Window(x, y, w, h){
	type = t;
	model = -1;
	Fl::add_timeout(2.0, Timer_CB, (void*)this);
}

void Model_Window::Timer_CB(void* userdata){
	Model_Window *glwin = (Model_Window*)userdata;
	glwin->loadModel();
	glwin->redraw();
}

void Model_Window::init(){	
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClearDepth(1.0f);		
	glEnable(GL_DEPTH_TEST); 
	glDepthFunc(GL_LEQUAL);		
	glBlendFunc(GL_DST_COLOR, GL_ZERO); 
	glLineWidth(2);

	box = glGenLists(1);
	glNewList(box, GL_COMPILE);
	glBegin(GL_LINE_LOOP);
	glColor3f(0, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	glVertex3f(1, 0, 1);
	glVertex3f(0, 0, 1);
	glEnd();
	glEndList();	
}

void Model_Window::draw(){
	if (!valid()) {
		valid(1);
		init();
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.5f, 1.5f, -1.5f, 1.5f, -100.0f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();			
	glTranslatef(-0.75f, -0.75f, -0.75f);	
	glRotatef(Camera::getRotate(X), 1.0f, 0.0f, 0.0f);
	glRotatef(Camera::getRotate(Y), 0.0f, 1.0f, 0.0f);
	glRotatef(Camera::getRotate(Z), 0.0f, 0.0f, 1.0f);

	glCallList(box);	
	glCallList(model);
}

int Model_Window::handle(int e){
	if(e == FL_RELEASE){
		if(Fl::event_button() == 1) // Left Mouse
			MapModelContainer::increment(type);
		else if(Fl::event_button() == 3) // Right Mouse
			MapModelContainer::decrement(type);
		loadModel();
		redraw();
	}
	return Fl_Gl_Window::handle(e);
}


void Model_Window::loadModel(){
	glDeleteLists(model, 1);
	model = glGenLists(1);
	glNewList(model, GL_COMPILE);
	if(type != GROUND)
		MapModelContainer::get(GROUND)->draw(0, 0, 0);
	Model* temp = MapModelContainer::get(type);
	if(temp != NULL){
		temp->draw(0, 0, 0);
		if(type == WINDOWFRAME && MapModelContainer::getCondition(WINDOWFRAME) != BROKEN){
			glEnable(GL_BLEND);
			MapModelContainer::get(WINDOW)->draw(0, 0, 0);
			glDisable(GL_BLEND);
		}
	}
	glEndList();
}
