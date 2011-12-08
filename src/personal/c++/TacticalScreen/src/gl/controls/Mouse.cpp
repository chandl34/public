#include "Mouse.h"
#include "../Game_Window.h"
#include "../../world/World.h"

int Mouse::prev[2] = {0, 0};
GLuint Mouse::buffer[16];
int Mouse::viewport[4];
bool Mouse::valid = false;

int Mouse::get(int i){return prev[i];}

void Mouse::move(int x, int y){
#ifdef SCROLLING
	if(x < 20)
		Camera::setScroll(X, Camera::SCROLL_LEFT);
	else if(x > Game_Window::width() - 20)
		Camera::setScroll(X, Camera::SCROLL_RIGHT);
	else 
		Camera::setScroll(X, Camera::NO_SCROLL);

	if(y < 20)
		Camera::setScroll(Y, Camera::SCROLL_UP);
	else 
		Camera::setScroll(Y, Camera::NO_SCROLL);

	if(Camera::getScroll(X) != Camera::NO_SCROLL || 
			Camera::getScroll(Y) != Camera::NO_SCROLL)
		return;	
#endif	
	if(Cursor::getMode() == MOVE){
		if(x > prev[X] + 5 || x < prev[X] - 5 ||
				y > prev[Y] + 5 || y < prev[Y] - 5)
			findSelectedCoord(x, y);
	}
	else{
		prev[X] = x;
		prev[Y] = y;
	}
}

void Mouse::findSelectedCoord(int x, int y){
	prev[X] = x;
	prev[Y] = y;
	float xAdj = (20.0f*x)/Game_Window::width();
	float yAdj = (23.0f*y)/Game_Window::height();
	int xCoord = (int)(-yAdj + xAdj + 75.5f) + Camera::getShift(X) - Camera::getShift(Y);
	int yCoord = (int)(yAdj + xAdj + 1.5f) + Camera::getShift(X) + Camera::getShift(Y);
	Cursor::selectCoord(World::getCoord(xCoord, yCoord));
}

Vertex* Mouse::findSelectedVertex(int x, int y){
	float xAdj = (20.0f*x)/Game_Window::width();
	float yAdj = (23.0f*y)/Game_Window::height();
	float xCoord = -yAdj + xAdj + 75.5f + Camera::getShift(X) - Camera::getShift(Y);
	float zCoord = yAdj + xAdj + 1.5f + Camera::getShift(X) + Camera::getShift(Y);
	return new Vertex(xCoord, 0, zCoord);
}

#ifdef SCROLLING
void Mouse::leave(int x, int y){
	Camera::setScroll(X, Camera::NO_SCROLL);
	Camera::setScroll(Y, Camera::NO_SCROLL);
}
#endif	

void Mouse::push(int button, int x, int y){
	int mode = Cursor::getMode();
	if(button == RMB)
		Cursor::toggleMoveShootMode();
	else if(button == LMB){
		if(mode == MOVE)
			move();
		else if(mode == SHOOT)	
			shoot(x, y);		
		else if(mode == USE)
			use(x, y);
		else
			look(x, y);
	}
}

void Mouse::setupSelectBuffer(int x, int y){	
	if(!valid){
		viewport[0] = 0; viewport[1] = 0;
		viewport[2] = Game_Window::width();
		viewport[3] = Game_Window::height();
	}	
	glSelectBuffer(16, buffer);		
	glRenderMode(GL_SELECT);
	glInitNames();					
	glPushName(0);			
	glMatrixMode(GL_PROJECTION);					
	glLoadIdentity();					
	gluPickMatrix((GLdouble) x, (GLdouble) (viewport[3]-y), 1.0f, 1.0f, viewport);
	Game_Window::view();						
}

void Mouse::move(){			
	Coordinate* coord = Cursor::getSelectedCoord();
	if(coord == NULL)
		return;
	Character* character = World::getSelectedMap()->getBlock(coord)->getCharacter();
	if(character == NULL)
		World::getSelectedChar()->setDestination(coord);	
	else if(character->getType() == PLAYER)
		World::selectChar(character);
}

void Mouse::look(int x, int y){		
	findSelectedCoord(x, y);
	Coordinate* coord = Cursor::getSelectedCoord();
	World::getSelectedChar()->lookAt(coord);	
}

void Mouse::shoot(int x, int y){	
	setupSelectBuffer(x, y);	
	Game_Window::drawCharacters();	
	int hits = glRenderMode(GL_RENDER);	
	Vertex* target;
	if(hits == 0)
		target = findSelectedVertex(x, y);
	else{
		int depth = buffer[1];	
		LevelMap* map = World::getSelectedMap();	
		Selection* select = map->getSelection(buffer[3]);

		for(int i = 1; i < hits; i++){	//Finding closest
			if(buffer[i*4+1] < GLuint(depth))
				select = map->getSelection(buffer[i*4+3]);
		}

		Vertex* relCent = select->getCenter();
		Coordinate* coord = select->getCoord();
		target = new Vertex(relCent->get(X) + coord->get(X), 
				relCent->get(Y), relCent->get(Z) + coord->get(Y));
	}
	World::getSelectedChar()->shootAt(target);	
}

void Mouse::use(int x, int y){
	setupSelectBuffer(x, y);	
	Game_Window::drawDoors();	
	int hits = glRenderMode(GL_RENDER);	
	if(hits == 0)
		cout << "picking up item" << endl;
	else{
		int depth = buffer[1];	
		LevelMap* map = World::getSelectedMap();	
		Selection* select = map->getSelection(buffer[3]);

		for(int i = 1; i < hits; i++){	//Finding closest
			if(buffer[i*4+1] < GLuint(depth))
				select = map->getSelection(buffer[i*4+3]);
		}		
		DoorModel* temp = select->getDoor();
		Coordinate* doorLoc = select->getCoord();
		Coordinate* adjDoorLoc;
		if(temp->getMirror() == false)
			adjDoorLoc = World::getCoord(doorLoc->get(X) - 1, doorLoc->get(Y));
		else
			adjDoorLoc = World::getCoord(doorLoc->get(X), doorLoc->get(Y) + 1);	
		Character* character =  World::getSelectedChar();
		Coordinate* charLoc = character->getCoord();

		if(charLoc == doorLoc){	
			character->lookAt(adjDoorLoc);
			character->setDoorToOpen(select->getDoor());
		}
		else if(charLoc == adjDoorLoc){
			character->lookAt(doorLoc);
			character->setDoorToOpen(select->getDoor());
		}
		
	}
}

void Mouse::release(int button, int x, int y){}
void Mouse::drag(int button, int x, int y){}
void Mouse::mouseWheel(int direction, int x, int y){}
