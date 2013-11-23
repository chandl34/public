#ifndef MOUSE_H_
#define MOUSE_H_

class Mouse{
public:
	Mouse(){}
	virtual ~Mouse(){}

	static void move(int, int);
	static void push(int, int, int);
	static void release(int, int, int);
	static void drag(int, int, int);
	static void mouseWheel(int, int, int);	
	
};

#endif /*MOUSE_H_*/
