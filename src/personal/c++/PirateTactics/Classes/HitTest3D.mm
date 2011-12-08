/*
 *  HitTest3D.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "HitTest.h"


// Returns time, where (vertFinal = vertOrigin + vectDir*time)  ---  -1 represents no hit
bool rayInTriangle(const Ray& ray, const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& offset, GLfloat& time){
	Vector edge1(v1, v0);	
	Vector edge2(v2, v0);	
	Vector pvec(ray.getDir(), edge2);
	
	GLfloat det = edge1.dot(pvec);
	///*// Culling version
	if(det < EPSILON)
		return false;		
	
	// Globalize this vertex location
	Vertex vert0(v0.getLoc(X) + offset.getLoc(X),
				 v0.getLoc(Y) + offset.getLoc(Y),
				 v0.getLoc(Z) + offset.getLoc(Z));
	
	Vector tvec(ray.getLoc(), vert0);
	
	GLfloat u = tvec.dot(pvec);
	if(u < 0.0f || u > det)
		return false;
	
	Vector qvec(tvec, edge1);
	GLfloat v = ray.getDir().dot(qvec);
	if(v < 0.0f || u + v > det)
		return false;
	//*/
	
	/*// Non-culling version
	if(fabs(det) < EPSILON)
		return false;
	
	// Globalize this vertex location
	Vertex vert0(tri.getLoc(0, X) + offset.getLoc(X),
				 tri.getLoc(0, Y) + offset.getLoc(Y),
				 tri.getLoc(0, Z) + offset.getLoc(Z));
	
	Vector tvec(ray.getLoc(), &vert0);
	
	GLfloat u = tvec.dot(&pvec)/det;
	if(u < 0.0f || u > 1.0f)
		return false;
	
	Vector qvec(&tvec, &edge1);
	GLfloat v = ray.getDir().dot(&qvec)/det;
	if(v < 0.0f || u + v > 1.0f)
		return false;
	
	//*/
	 
	GLfloat t = edge2.dot(qvec)/det;
	if(t > 0){
		if(time < 0 || t < time){
			time = t;
			return true;
		}
	}
	
	return false;			// NOTE:  this is a hit, but I want the soonest hit
}
