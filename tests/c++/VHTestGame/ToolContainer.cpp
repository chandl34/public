#include "ToolContainer.h"


set<Brush*> ToolContainer::_brush;
set<Pen*> ToolContainer::_pen;


ToolContainer::ToolContainer()
{

}


ToolContainer::~ToolContainer()
{
	for(set<Brush*>::iterator iter = _brush.begin(); iter != _brush.end(); ++iter)
		delete *iter;

	for(set<Pen*>::iterator iter = _pen.begin(); iter != _pen.end(); ++iter)
		delete *iter;
}


Brush* ToolContainer::getBrush(const Color& color)
{
	
}

Pen* ToolContainer::getPen(const Color& color, int thickness)
{
	
}

