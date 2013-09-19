#ifndef TOOL_CONTAINER_H_
#define TOOL_CONTAINER_H_

#include <set>



class ToolContainer
{
public:
	ToolContainer();
	~ToolContainer();

	static Brush* getBrush(const Color&);
	static Pen* getPen(const Color&, int);

private:
	static list<Brush*> _brush;
	static list<Pen*> _pen;
};

#endif
