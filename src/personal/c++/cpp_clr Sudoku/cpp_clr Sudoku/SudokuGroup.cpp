#include "stdafx.h"
#include "SudokuGroup.h"


// Constructors / Destructors
SudokuGroup::SudokuGroup()
	: _block(9)
{
}

SudokuGroup::~SudokuGroup()
{

}

	
// Class Methods
void SudokuGroup::setBlock(int i, SudokuBlock^ sb)
{
	_block.at(i) = sb;
}