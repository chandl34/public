#ifndef MOUSE_H_
#define MOUSE_H_

#include "../Camera.h"
#include "../Cursor.h"

class Mouse{
public:
	Mouse(){}
	virtual ~Mouse(){}

	static int get(int);
	static void findSelectedCoord(int, int);
	static Vertex* findSelectedVertex(int, int);
	
#ifdef SCROLLING
	static void leave(int, int);
#endif //SCROLLING
	
	static void move(int, int);
	static void push(int, int, int);
	static void release(int, int, int);
	static void drag(int, int, int);
	static void mouseWheel(int, int, int);
	
private:
	static void setupSelectBuffer(int, int);
	static void move();
	static void look(int, int);
	static void shoot(int, int);
	static void use(int, int);
	
	enum{LMB = 1, MMB, RMB};
	static int prev[];
	
	static GLuint buffer[];
	static int viewport[];
	static bool valid;
	
};

#endif /*MOUSE_H_*/
