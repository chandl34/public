#include "Keyboard.h"
#include "../../world/World.h"

int Keyboard::downKey = -1;

void Keyboard::keyDown(int key, int x, int y){
	if(downKey != -1 )
		return;	
	downKey = key;
	switch(key){
#ifdef SCROLLWITHKEYBOARD
	case 'a':
		Camera::scroll(X, Camera::SCROLL_LEFT);
		break;
	case 'd':
		Camera::scroll(X, Camera::SCROLL_RIGHT);
		break;
	case 's':
		Camera::scroll(Y, Camera::SCROLL_DOWN);
		break;
	case 'w':
		Camera::scroll(Y, Camera::SCROLL_UP);
		break;
#endif
	case 'q':
		World::getSelectedMap()->clearVision(INVISIBLE, true);
		cout << "CLEARED VISION" << endl;
		break;
	case 65507: // Left-Ctrl
		Cursor::toggleUseMode();
		break;
	case 65505: //Left-Shift
		Cursor::toggleLookMode();
		break;
	}
}

void Keyboard::keyUp(int key, int x, int y){
	if(key != downKey)
		return;
	downKey = -1;
	switch(key){
	case 65507: // Left-Ctrl
		Cursor::toggleUseMode();
		break;
	case 65505: //Left-Shift
		Cursor::toggleLookMode();
		break;
	}
}
