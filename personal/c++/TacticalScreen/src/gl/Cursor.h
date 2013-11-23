#ifndef CURSOR_H_
#define CURSOR_H_

#include "../Include.h"
#include "../io/Reader.h"
#include "../world/map/Coordinate.h"

class Cursor{
public:
	Cursor();
	virtual ~Cursor();

	static void selectCoord(Coordinate*);
	static Coordinate* getSelectedCoord();
	
	static int getCursor();
	static void toggleMoveShootMode();
	static void toggleUseMode();
	static void toggleLookMode();
	static void revertMode();
	static int getMode();
	
	static void draw();
	
	
private:
	static Model* cursor;
	static Model* cursor2;
	static int mode;
	static int prevMode;
	static int* id;	
	static Coordinate* sCoord;
};

#endif /*CURSOR_H_*/
