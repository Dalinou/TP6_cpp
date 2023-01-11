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
	int width_size = ceil(log10(s._size))+1;
	for (int raw = 0; raw < s._size; raw++)
	{
		for (int col = 0; col < s._size; col++)
		{
			if (col % s._dimension.at(0) == 0) os << "|" << std::setw(width_size);
			int value = s._board.at(raw * s._size + col);
			if (value == 0)os << "_" << std::setw(width_size);
			else os << value << std::setw(width_size);
		}
		os << std::setw(width_size + 1) << "|\n";
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
	for (auto value : _board)
		if (value < 0 || value > _size)
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

std::vector<bool> Sudoku::getValidValues(int raw, int col) {
	if (_board.at(raw * _size + col) != 0) {
		std::vector<bool> valid_values(_size, false);
		valid_values.at(_board.at(raw * _size + col) - 1) = true;
		return valid_values;
	}
	std::vector<bool> valid_values;
	std::vector<bool> raw_values = getRawValues(raw);
	std::vector<bool> col_values = getColValues(col);
	std::vector<bool> square_values = getSquareValues(raw, col);
	for (int i = 0; i < _size; i++)
		valid_values.push_back(!(raw_values.at(i) || col_values.at(i) || square_values.at(i)));
	return valid_values;
}
std::vector<bool> Sudoku::getRawValues(int raw)
{
	std::vector<bool> raw_values(_size, false);
	for (int col = 0; col < _size; col++)
		if (_board.at(raw * _size + col) != 0)
			raw_values.at(_board.at(raw * _size + col) - 1) = true;
	return raw_values;
}
std::vector<bool> Sudoku::getColValues(int col)
{
	std::vector<bool> col_values(_size, false);
	for (int raw = 0; raw < _size; raw++)
		if (_board.at(raw * _size + col) != 0)
			col_values.at(_board.at(raw * _size + col) - 1) = true;
	return col_values;
}
std::vector<bool> Sudoku::getSquareValues(int raw, int col)
{
	std::vector<bool> square_values(_size, false);
	int raw_start = raw - raw % _dimension.at(1);
	int col_start = col - col % _dimension.at(0);
	for (int raw_ = raw_start; raw_ < raw_start + _dimension.at(1); raw_++)
		for (int col_ = col_start; col_ < col_start + _dimension.at(0); col_++)
			if (_board.at(raw_ * _size + col_) != 0)
				square_values.at(_board.at(raw_ * _size + col_) - 1) = true;
	return square_values;
}