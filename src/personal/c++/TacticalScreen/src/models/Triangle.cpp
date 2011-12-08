#include "Triangle.h"

Triangle::Triangle(Vertex* v1, Vertex* v2, Vertex* v3, float* c){
	vert = new Vertex*[3];
	vert[0] = v1; 
	vert[1] = v2; 
	vert[2] = v3; 
	
	Vector vec1(v2, v1);
	Vector vec2(v3, v2);
	normal = vec1.getNormal(&vec2);	
	light = getShade() - dark;
	color = c;
}

void Triangle::draw(float x, float y, float z){	
	glColor3f(color[R] + light, color[G] + light, color[B] + light);
	//glNormal3f(normal->get(X), normal->get(Y), normal->get(Z));
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 3; i++)
		vert[i]->draw(x, y, z);
	glEnd();
	
	//normal->draw(x, y, z, vert[0]);
}

void Triangle::draw(float x, float y, float z, bool darkened){	
	if(darkened)
		glColor3f(color[R] + light - 0.2f, 
				color[G] + light - 0.2f, color[B] + light - 0.2f);
	else		
	glColor3f(color[R] + light, color[G] + light, color[B] + light);
	//glNormal3f(normal->get(X), normal->get(Y), normal->get(Z));
	glBegin(GL_TRIANGLES);
	for(int i = 0; i < 3; i++)
		vert[i]->draw(x, y, z);
	glEnd();
	
	//normal->draw(x, y, z, vert[0]);
}

void Triangle::rotateY(float s, float c){
	normal->rotateY(s, c);
	light = getShade() - dark;
}

void Triangle::mirror(){
	normal->mirror();
	light = getShade() - dark;
}

void Triangle::invert(){
	normal->invert();
	light = getShade() - dark;
}
