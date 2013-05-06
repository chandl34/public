#pragma once

#include "SudokuBlock.h"


ref class SudokuGroup
{
public:
	SudokuGroup();
	~SudokuGroup();

	void setBlock(int, SudokuBlock^);

private:
	cliext::vector<SudokuBlock^> _block;
};

