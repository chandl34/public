#pragma once

#include "stdafx.h"
#include "SudokuBlock.h"


ref class SudokuGroup
{
public:
	SudokuGroup();
	~SudokuGroup();

	void addBlock(SudokuBlock^);
	void remove(int);

private:
	cliext::list<SudokuBlock^> _block;
};

