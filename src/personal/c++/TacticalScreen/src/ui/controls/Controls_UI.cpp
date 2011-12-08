#include "../UI_Window.h"
#include "Mouse_UI.h"

int UI_Window::handle(int e){
	if(e == FL_FOCUS)
		return 1;
	else if(e == FL_UNFOCUS)
		return 1;
	if(!loaded)
		return Fl_Gl_Window::handle(e);
	switch(e){
#ifdef SCROLLING
	case FL_LEAVE:
		Mouse_UI::leave(Fl::event_x(), Fl::event_y());
		break;
	case FL_MOVE:
		Mouse_UI::move(Fl::event_x(), Fl::event_y());
		break;	
#endif		
	}

	return Fl_Gl_Window::handle(e);
}
