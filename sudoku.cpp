#include "sudoku.h"
#include <string>

Sudoku::Sudoku(std::array<int, 2> dimension)
	: _dimension(dimension), _size(_dimension.at(0) * _dimension.at(1))
{
	while (!generate());
}
Sudoku::Sudoku(std::vector<int> grid, std::array<int, 2> dimension)
	: _board(grid), _dimension(dimension), _size(_dimension.at(0) * _dimension.at(1))
{
	if (!isValid())
		throw std::string("Invalid grid");
}
std::ostream& operator<<(std::ostream& os, Sudoku& s)
{
	for (int i = 0; i < s._size; i++)
	{
		for (int j = 0; j < s._size; j++)
		{
			if (j % s._dimension.at(0) == 0) os << "|	";
			int value = s._board.at(i * s._size + j);
			if (value == 0)os << "_	";
			else os << value << "	";
		}
		os << "|	\n";
		if ((i + 1) % s._dimension.at(1) == 0) os << "	\n";
	}
	return os;
}
bool Sudoku::generate(bool empty)
{
	if (empty)
		for (int i = 0; i < pow(_size,2); i++)
			_board.push_back(0);
	else 
		for (int i = 0; i < pow(_size, 2); i++)
			_board.push_back(0);
	return true;
}
bool Sudoku::isValid()
{
	// TODO
	return true;
}