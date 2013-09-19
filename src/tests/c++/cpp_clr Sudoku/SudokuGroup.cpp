#include "stdafx.h"
#include "SudokuGroup.h"


// Constructors / Destructors
SudokuGroup::SudokuGroup()
{

}

SudokuGroup::~SudokuGroup()
{

}

	
// Class Methods
void SudokuGroup::addBlock(SudokuBlock^ sb)
{
	_block.push_back(sb);
}
	
void SudokuGroup::remove(int val)
{
	for(cliext::list<SudokuBlock^>::iterator iter = _block.begin(); iter != _block.end(); ++iter)
	{
		(*iter)->remove(val);
	}
}