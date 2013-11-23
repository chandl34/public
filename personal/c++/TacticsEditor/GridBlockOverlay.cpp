/*
 *  GridBlockOverlay.mm
 *  Tactics
 *
 *  Created by Jonathan Chandler on 4/6/12.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "GridBlockOverlay.h"

#include "GridBlock.h"
#include "Image.h"


GridBlockOverlay::GridBlockOverlay(Image* img, const GridBlock* gb) : Icon(img){
	setGridBlock(gb);
}

void GridBlockOverlay::setGridBlock(const GridBlock* gb){
	if(gb == NULL)
		setOffset(-500, -500);
	else
		setOffset(gb->getOffset(X), gb->getOffset(Y));
}