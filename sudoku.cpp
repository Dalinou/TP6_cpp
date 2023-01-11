#include "sudoku.h"
#include <string>
#include <iomanip>

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
	int width_size = ceil(2 * log10(s._size))+1;
	for (int raw = 0; raw < s._size; raw++)
	{
		for (int col = 0; col < s._size; col++)
		{
			if (col % s._dimension.at(0) == 0) os << "|" << std::setw(width_size);
			int value = s._board.at(raw * s._size + col);
			if (value == 0)os << "_" << std::setw(width_size);
			else os << value << std::setw(width_size);
		}
		os << "|\n";
		if ((raw + 1) % s._dimension.at(1) == 0) os << "\n";
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
	if (_board.size() != pow(_size, 2))
		return false;
	
	return true;
}
bool Sudoku::solve(bool check_unicity)
{
	bool solution_found = false;
	while (check_unicity || !solution_found)
	{
		//TODO
	}
	return true;
}