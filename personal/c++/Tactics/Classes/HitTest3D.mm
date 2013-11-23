/*
 *  HitTest3D.mm
 *  Pirate Tactics
 *
 *  Created by Jonathan Chandler on 6/20/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "HitTest.h"

#include "Hit.h"
#include "Ray.h"
#include "Triangle.h"


// Returns best time, where (vertFinal = vertOrigin + vectDir*time)  ---  -1 represents no hit
bool rayInTri(const Ray& ray, const Tri& tri, const Vertex& offset, Hit& hit)
{
	Vector edge1(tri.getVert(1), tri.getVert(0));	
	Vector edge2(tri.getVert(2), tri.getVert(0));	
	Vector pvec(ray.getDir(), edge2);
	
	double det = edge1.dot(pvec);
	
	if(det < EPSILON)
		return false;		
	
	// Globalize this vertex location
	Vertex vert0(tri.getVert(0).getLoc(X) + offset.getLoc(X),
				 tri.getVert(0).getLoc(Y) + offset.getLoc(Y),
				 tri.getVert(0).getLoc(Z) + offset.getLoc(Z));
	
	Vector tvec(ray.getLoc(), vert0);
	
	double u = tvec.dot(pvec);
	//if(u < EPSILON || u > det - EPSILON)
	if(u < 0.0 || u > det)
		return false;
	
	Vector qvec(tvec, edge1);
	double v = ray.getDir().dot(qvec);
	//if(v < EPSILON || u + v > det - EPSILON)
	if(v < 0.0 || u + v > det)
		return false;
	
	double t = edge2.dot(qvec)/det;
	if(t > 0){
		if(hit.getTimeLeft() < 0 || t < hit.getTimeLeft()){
			hit.setTimeLeft(t);
			return true;
		}
	}
	
	return false;	// NOTE:  this is a hit, but I want the soonest hit
}
