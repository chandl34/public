#include "Keyboard.h"

void Keyboard::keyDown(int key, int x, int y){
	//cout << "Key: " << key << endl;
	switch(key){
	// VIEW
	case 'e':
		Camera::setOrthogonal(!Camera::isOrthogonal());
		break;
	case 'r':
		Camera::aerialToggle();
		break;

	// SELECTION MOVEMENT
	case 'a':
		SelectBox::moveLeft();
		break;
	case 'w':
		SelectBox::moveForward();
		break;
	case 's':
		SelectBox::moveBackward();
		break;
	case 'd':
		SelectBox::moveRight();
		break;
		
	// ADD MODELS
	case 'i':	
		LevelMap::getSelectedBlock()->addGround();
		break;
	case 'o':
		LevelMap::getSelectedBlock()->addDebris();
		break;
	case 'p':
		LevelMap::getSelectedBlock()->addGrass();
		break;
	case 'k':
		LevelMap::getSelectedBlock()->addWall();
		break;
	case 'l':
		LevelMap::getSelectedBlock()->addObject();
		break;
	case ';':
		LevelMap::getSelectedBlock()->addFence();
		break;
	case ',':
		LevelMap::getSelectedBlock()->addWindow();
		break;
	case '.':
		LevelMap::getSelectedBlock()->addDoor();
		break;
	case '/':
		LevelMap::getSelectedBlock()->addDoor();
		break;
		
	// REMOVE MODELS
	case 'h':
		LevelMap::getSelectedBlock()->clear();
		break;
		
	// CHANGE MODELS
	case 'j':
		Preview_Window::toggleMirror();
		break;
	case 'u':
		Preview_Window::toggleInvert();
		break;
	case 'm':
		Preview_Window::toggleShift();
		break;
		
	}
}
