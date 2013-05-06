#include "stdafx.h"
#include "SudokuBlock.h"


// Constructors / Destructors
SudokuBlock::SudokuBlock()
{
	_val = 0;

	for(int i = 0; i < 9; ++i)
	{
		_poss.insert(i);
	}
}

SudokuBlock::~SudokuBlock()
{

}



// Class Methods
void SudokuBlock::setValue(int x)
{
	_val = x;
}

bool SudokuBlock::solved()
{
	return _val != 0;
}
	