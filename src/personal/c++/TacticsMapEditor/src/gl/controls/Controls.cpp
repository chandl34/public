#include "../MapWindow.h"
#include "Mouse.h"
#include "Keyboard.h"

int MapWindow::handle(int e){
	switch(e){
	case FL_KEYDOWN:
		Keyboard::keyDown(Fl::event_key(), Fl::event_x(), Fl::event_y());
		break;
	case FL_KEYUP:
		Keyboard::keyUp(Fl::event_key(), Fl::event_x(), Fl::event_y());
		break;
	case FL_MOVE:
		Mouse::move(Fl::event_x(), Fl::event_y());
		break;		
	case FL_PUSH:
		Mouse::push(Fl::event_button(), Fl::event_x(), Fl::event_y());
		break;
	case FL_RELEASE:
		Mouse::release(Fl::event_button(), Fl::event_x(), Fl::event_y());
		break;
	case FL_DRAG:
		Mouse::drag(Fl::event_button(), Fl::event_x(), Fl::event_y());
		break;
	case FL_MOUSEWHEEL:
		Mouse::mouseWheel(Fl::event_dy(), Fl::event_x(), Fl::event_y());
		break;
	}

	return Fl_Gl_Window::handle(e);
}
