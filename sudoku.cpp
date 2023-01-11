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
std::ostream& operator<<(std::ostream& os, Sudoku& s) {
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
std::ostream& Sudoku::getSolved(std::ostream& os) {
	int width_size = ceil(log10(_size)) + 1;
	for (int raw = 0; raw < _size; raw++)
	{
		for (int col = 0; col < _size; col++)
		{
			if (col % _dimension.at(0) == 0) os << "|" << std::setw(width_size);
			int value = _solution.at(raw * _size + col);
			if (value == 0)os << "_" << std::setw(width_size);
			else os << value << std::setw(width_size);
		}
		os << std::setw(width_size + 1) << "|\n";
		if ((raw + 1) % _dimension.at(1) == 0) os << "\n";
	}
	return os;
}
bool Sudoku::generate(bool empty) {
	if (empty)
		for (int i = 0; i < pow(_size,2); i++)
			_board.push_back(0);
	else 
		for (int i = 0; i < pow(_size, 2); i++)
			_board.push_back(0);
	return true;
}
bool Sudoku::isValid() {
	if (_board.size() != pow(_size, 2))
		return false;
	for (auto value : _board)
		if (value < 0 || value > _size) 
			return false;
	if (!solve(true)) 
		return false;
	return true;
}
bool Sudoku::solve(bool check_unicity) {
	bool solution_found = false;
	std::vector<int> board_copy = _board;
	std::vector<int> advencment(pow(_size, 2), 0);
	while (check_unicity || !solution_found)
	{
		board_copy = _board;
		int i = 0;
		while (i >= 0 && i < pow(_size, 2)) {
			std::vector<bool> valid_values = ::getValidValues(i / 9, i % 9, board_copy, _dimension);
			if (nonZeroCount(valid_values) == 0) {
				i--;
				advencment.at(i)++;
				board_copy.at(i) = _board.at(i);
			}
			else if (nonZeroCount(valid_values) == advencment.at(i)) {
				board_copy.at(i) = _board.at(i);
				advencment.at(i) = 0;
				i--;
				advencment.at(i)++;
				board_copy.at(i) = _board.at(i);
			}
			else {
				board_copy.at(i) = getNonZeroValue(valid_values, advencment.at(i));
				i++;
			}
			
		}
		if (i == pow(_size,2)) 
			if (solution_found) 
				return true;
			else {
				_solution = board_copy;
				solution_found = true;
			}
		if (i == 0) {
			return solution_found;
		}
	}
	return true;
}

std::vector<bool> Sudoku::getValidValues(int raw, int col) {
	return ::getValidValues(raw, col, _board, _dimension);
}
std::vector<bool> Sudoku::getRawValues(int raw) {
	return ::getRawValues(raw, _board, _dimension);
}
std::vector<bool> Sudoku::getColValues(int col) {
	return ::getColValues(col, _board, _dimension);
}
std::vector<bool> Sudoku::getSquareValues(int raw, int col) {
	return ::getSquareValues(raw, col, _board, _dimension);
}

std::vector<bool> getValidValues(int raw, int col, std::vector<int>board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	if (board.at(raw * size + col) != 0) {
		std::vector<bool> valid_values(size, false);
		valid_values.at(board.at(raw * size + col) - 1) = true;
		return valid_values;
	}
	std::vector<bool> valid_values;
	std::vector<bool> raw_values = getRawValues(raw, board, dimension);
	std::vector<bool> col_values = getColValues(col, board, dimension);
	std::vector<bool> square_values = getSquareValues(raw, col, board, dimension);
	for (int i = 0; i < size; i++)
		valid_values.push_back(!(raw_values.at(i) || col_values.at(i) || square_values.at(i)));
	return valid_values;
}
std::vector<bool> getRawValues(int raw, std::vector<int>board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	std::vector<bool> raw_values(size, false);
	for (int col = 0; col < size; col++)
		if (board.at(raw * size + col) != 0)
			raw_values.at(board.at(raw * size + col) - 1) = true;
	return raw_values;
}
std::vector<bool> getColValues(int col, std::vector<int>board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	std::vector<bool> col_values(size, false);
	for (int raw = 0; raw < size; raw++)
		if (board.at(raw * size + col) != 0)
			col_values.at(board.at(raw * size + col) - 1) = true;
	return col_values;
}
std::vector<bool> getSquareValues(int raw, int col, std::vector<int>board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	std::vector<bool> square_values(size, false);
	int raw_start = raw - raw % dimension.at(1);
	int col_start = col - col % dimension.at(0);
	for (int raw_ = raw_start; raw_ < raw_start + dimension.at(1); raw_++)
		for (int col_ = col_start; col_ < col_start + dimension.at(0); col_++)
			if (board.at(raw_ * size + col_) != 0)
				square_values.at(board.at(raw_ * size + col_) - 1) = true;
	return square_values;
}

int nonZeroCount(std::vector<bool> values) {
	int count = 0;
	for (auto value : values)
		if (value) count++;
	return count;
}
int getNonZeroValue(std::vector<bool> values, int index) {
	int count = 0;
	for (int i = 0;i<values.size();i++)
		if (values.at(i)) {
			if (count == index)
				return i + 1;
			count++;
		}
	return 0;
}