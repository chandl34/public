#include "../Game_Window.h"

int Game_Window::handle(int e){
	if(e == FL_FOCUS)
		return 1;
	else if(e == FL_UNFOCUS)
		return 1;
	if(!loaded)
		return Fl_Gl_Window::handle(e);
	switch(e){
	case FL_KEYDOWN:
		Keyboard::keyDown(Fl::event_key(), Fl::event_x(), Fl::event_y());
		break;
	case FL_KEYUP:
		Keyboard::keyUp(Fl::event_key(), Fl::event_x(), Fl::event_y());
		break;
#ifdef SCROLLING
	case FL_LEAVE:
		Mouse::leave(Fl::event_x(), Fl::event_y());
		break;
#endif	
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
