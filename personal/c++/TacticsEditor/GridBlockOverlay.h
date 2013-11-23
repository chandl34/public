/*
 *  GridBlockOverlay.h
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */


#ifndef GRID_BLOCK_OVERLAY_H_
#define GRID_BLOCK_OVERLAY_H_

#include "Icon.h"

class GridBlock;
class Image;


class GridBlockOverlay : public Icon{
public:
	GridBlockOverlay(Image*, const GridBlock*);
	
	void setGridBlock(const GridBlock*);		
};

#endif