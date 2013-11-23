/*
 *  HitTest
 *  Tactics
 *
 *  Created by Jonathan Chandler on 2/3/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "HitTest.h"

#include "GridBlock.h"
#include "Hit.h"
#include "Ray.h"

#include "LevelMap.h"


// Do a trial run to find the bullet's lifespan
void testFlight(Ray tRay, Hit& hit, double gravity, bool ignore)
{
	LevelMap* levelMap = LevelMap::getInstance();
	GLshort t;
	GridBlock* gb;
	GridBlock* ogb = levelMap->getBlockBy3D(tRay.getLoc(X), tRay.getLoc(Y));
	for(t = 0; hit.getTimeLeft() < 0.0 || hit.getTimeLeft() > 1.0; ++t){		
		tRay.setDir(tRay.getDir(X),
						tRay.getDir(Y),
						tRay.getDir(Z) + 2 * gravity);
		
		// NOTE: This would ignore Hits on polygons that have normals pointing towards its GridBlock.
		//       I don't build my Models this way, so this probably won't be a problem.
		gb = levelMap->getBlockBy3D(tRay.getLoc(X) + tRay.getDir(X), 
											 tRay.getLoc(Y) + tRay.getDir(Y));
		
		if(gb == NULL)
			break;
		else if(tRay.getLoc(Z) < 0.0){
			printf("ERROR:  went through ground!\n");
			break;
		}
		
		gb->detectHit(tRay, hit, ignore, ogb == gb);
		
		tRay.step();		
	}
	
	if(hit.getTimeLeft() < 0.0)
		hit.setTimeLeft(0.0);	
	hit.setTimeLeft(hit.getTimeLeft() + t);
}
