#ifndef VERTEX_H_
#define VERTEX_H_

#include "../Include.h"

class Vertex{
public:
	Vertex(float* f){coord = f;}
	Vertex(float, float, float);
	virtual ~Vertex(){delete [] coord;}
	
	float get(int c){return coord[c];}
	void set(int c, float v){coord[c] = v;}
	void set(float x, float y, float z){coord[X] = x; coord[Y] = y; coord[Z] = z;}

	void draw(float x, float y, float z){glVertex3f(coord[X] + x, coord[Y] + y, coord[Z] + z);}

	void rotateY(float, float, float, float);
	void mirror();
	void invert(){coord[Z] = 1 - coord[Z];}
	void shift(){coord[X] += 0.1;}
		
private:
	float* coord;
};

#endif /*VERTEX_H_*/
