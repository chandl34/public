#include "stdafx.h"
#include "SudokuBlock.h"


// Constructors / Destructors
SudokuBlock::SudokuBlock()
{
	_checked = false;

	for(int i = 0; i < 9; ++i)
	{
		_poss.insert(i + 1);
	}
}

SudokuBlock::~SudokuBlock()
{

}



// Class Methods
int SudokuBlock::getValue()
{
	if(isSolved())
		return *_poss.begin();
	return 0;
}

bool SudokuBlock::isSolved()
{
	return _poss.size() == 1;
}
	

void SudokuBlock::setValue(int val)
{
	_poss.clear();
	_poss.insert(val);
}
	
void SudokuBlock::remove(int val)
{
	if(!isSolved())
		_poss.erase(val);
}

bool SudokuBlock::check()
{
	if(!_checked)
	{
		if(isSolved())
		{
			_checked = true;
			return true;
		}
	}

	return false;
}
	
void SudokuBlock::print()
{
	for(cliext::set<int>::iterator iter = _poss.begin(); iter != _poss.end(); ++iter)
	{
		printf("%i", *iter);
	}
	printf("\n");
}