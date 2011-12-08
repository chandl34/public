#ifndef HITDETECTION_H_
#define HITDETECTION_H_

#include "../models/Ray.h"
#include "Hit.h"

class HitDetection{
public:
	HitDetection();
	virtual ~HitDetection();
	
	static Hit* hitDetect(Ray*, float, bool);
	
private:
	enum{FALSE, TRUE, CLOSEST};
	
	static void intersectBreakable(Ray*, Coordinate*, Hit*, float);
	static void intersectDoor(Ray*, int, Coordinate*, Hit*, float);
	static void intersectCharacter(Ray*, Coordinate*, Hit*, float);
	static int intersectModel(Ray*, Model*, Coordinate*, Hit*, float);
	static int intersectTriangle(Ray*, Triangle*, Coordinate*, Hit*, float);
};

#endif /*HITDETECTION_H_*/
