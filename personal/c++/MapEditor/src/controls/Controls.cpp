#include "../gl/Map_Window.h"
#include "Keyboard.h"
#include "Mouse.h"

int Map_Window::handle(int e) {
	switch(e){
	case FL_KEYDOWN:
		Keyboard::keyDown(Fl::event_key(), Fl::event_x(), Fl::event_y());
		break;
#ifdef SCROLLING
	case FL_ENTER:
		Mouse::enter(Fl::event_x(), Fl::event_y());
		break;	
	case FL_LEAVE:
		Mouse::leave(Fl::event_x(), Fl::event_y());
		break;
#endif //SCROLLING		
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

	Fl_Gl_Window::handle(e);
	return 1;
}
