#include "sudoku.h"
#include <string>
#include <iomanip>
#include <algorithm>

Sudoku::Sudoku(int difficulty, std::array<int, 2> dimension)
	: _dimension(dimension), _size(_dimension.at(0) * _dimension.at(1))
{
	int nb_value;
	if (_dimension.at(0) == 3 && _dimension.at(1) == 3)
		nb_value = 17 + rand() % 3 + (10 - difficulty) * 3;
	else
		nb_value = pow(_size, 4 / 3) + rand() % (int)ceil((_dimension.at(0) + _dimension.at(1)) / 2) + (10 - difficulty) * (_dimension.at(0) + _dimension.at(1)) / 2;
	while (!generate(nb_value, 100));
}
Sudoku::Sudoku(std::vector<int> grid, std::array<int, 2> dimension)
	: _board(grid), _dimension(dimension), _size(_dimension.at(0) * _dimension.at(1))
{
	if (!isValid())
		throw std::string("Invalid grid");
}
std::ostream& operator<<(std::ostream& os, Sudoku& s) {
	return printBoard(os, s._board, s._dimension);
}
std::ostream& Sudoku::getSolved(std::ostream& os) {
	return printBoard(os, _solution, _dimension);
}
bool Sudoku::generate(int nb_value, int max_try) {
	
	
	_board = std::vector<int>(pow(_size, 2), 0);
	if (nb_value == 0) return false;
	
	int nb_try = 0, remove_try = 0;
	do {
		_board = std::vector<int>(pow(_size, 2), 0);
		for (int i = 0; i < 2 * _size; i++) {
			int raw = rand() % _size;
			int col = rand() % _size;
			if (_board.at(raw * _size + col) == 0) {
				std::vector<bool> valid_value = getValidValues(raw, col);
				if (valid_value.at(i%_size)) _board.at(raw * _size + col) = i % _size + 1;
				else 
					i--;
			}
			else
				i--;
		}
		std::cout << *this;
	} while (!solve() && nb_try++ < max_try);
	do {
		_board = _solution;
		nb_try = 0;
		int nb_fill = pow(_size, 2);
		while (nb_fill > nb_value && nb_try < max_try) {
			int pos = rand() % (int)pow(_size, 2);
			if (isRemovable(pos / _size, pos % _size)) {
				_board.at(pos) = 0;
				nb_fill--;
			}
			else nb_try++;
		}
		if (nb_fill != nb_value) for (int pos = 0; pos < pow(_size, 2); pos++) if (isRemovable(pos / _size, pos % _size)) {
			_board.at(pos) = 0;
			nb_fill--;
			if (nb_fill == nb_value) break;
			else pos = 0;
		}
	} while (!solve(true) && remove_try++ < max_try);
	std::vector<int> numbers;
	for (int i = 0; i < _size; i++) numbers.push_back(i + 1);
	std::random_shuffle(numbers.begin(), numbers.end());
	for (auto it : _board) if (it != 0) it = numbers.at(it - 1);
	for (auto it : _solution) if (it != 0) it = numbers.at(it - 1);
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
	std::vector<int> board_copy = _board, main_copy = _board;
	std::vector<int> advencment(pow(_size, 2), 0);
	addForcedValues(main_copy, _dimension);
	std::cout << std::endl;
	std::cout << *this;
	std::vector<int> null_pos;
	for (int pos = 0; pos < pow(_size, 2); pos++) if (main_copy.at(pos) == 0) null_pos.push_back(pos);
	while (check_unicity || !solution_found)
	{
		board_copy = main_copy;
		int i = 0;
		while (i >= 0 && i < null_pos.size()) {
			std::cout << "Progress : " << i << std::setw(2) << "/" << null_pos.size() << "\r";
			std::vector<bool> valid_values = ::getValidValues(null_pos.at(i) / _size, null_pos.at(i) % _size, board_copy, _dimension);
			if (nonZeroCount(valid_values) == 0) {
				i--;
				if (i < 0) break;
				advencment.at(i)++;
				for (int j = i; j < null_pos.size(); j++) board_copy.at(null_pos.at(j)) = main_copy.at(null_pos.at(j));
			}
			else if (nonZeroCount(valid_values) == advencment.at(i)) {
				advencment.at(i) = 0;
				i--;
				if (i < 0) break;
				advencment.at(i)++;
				for (int j = i; j < null_pos.size();j++) board_copy.at(null_pos.at(j)) = main_copy.at(null_pos.at(j));
			}
			else if (board_copy.at(null_pos.at(i)) != 0) i++;
			else {
				board_copy.at(null_pos.at(i)) = getNonZeroValue(valid_values, advencment.at(i));
				i++;
				addForcedValues(board_copy, _dimension);
			}
		}
		std::cout << "Go out looping, i = " << i << std::endl;
		if (i == null_pos.size())
			if (solution_found) {
				std::cout << "Multiple solution found" << std::endl;
				return false;
			}
			else {
				_solution = board_copy;
				advencment.at(null_pos.size()-1)++;
				solution_found = true;
			}
		if (i == -1) {
			if (solution_found) {
				std::cout << "Unique solution found" << std::endl;
				return true;
			}
			else {
				std::cout << "No solution found" << std::endl;
				return false;
			}
			return solution_found;
		}
	}
	std::cout << "Solution found, unicity unchecked" << std::endl;
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
bool Sudoku::isRemovable(int raw, int col) {
	return ::isRemovable(raw, col, _board, _dimension);
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
void addForcedValues(std::vector<int>& board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	for (int pos = 0; pos < pow(size, 2); pos++) {
		if (board.at(pos) != 0) continue;
		std::vector<bool> valid_value = ::getValidValues(pos / size, pos % size, board, dimension);
		if (nonZeroCount(valid_value) == 1) {
			board.at(pos) = getNonZeroValue(valid_value);
			pos = -1;
			continue;
		}
		int nb_allow;
		for (int i = 0; i < size; i++) if (valid_value.at(i)) {
			nb_allow = 0;
			for (int col = 0; col < size; col++) if (col != pos % size && board.at(pos / size * size + col) == 0) {
				std::vector<bool> valid_value_col = ::getValidValues(pos / size, col, board, dimension);
				if (valid_value_col.at(i)) {
					nb_allow++;
					break;
				}
			}
			for (int raw = 0; raw < size; raw++) if (raw != pos / size && board.at(raw * size + pos % size) == 0) {
				std::vector<bool> valid_value_raw = ::getValidValues(raw, pos % size, board, dimension);
				if (valid_value_raw.at(i)) {
					nb_allow++;
					break;
				}
			}
			int raw_start = pos / size - (pos / size) % dimension.at(1);
			int col_start = pos % size - (pos % size) % dimension.at(0);
			for (int raw = raw_start; raw < raw_start + dimension.at(1); raw++)
				for (int col = col_start; col < col_start + dimension.at(0); col++)
					if (raw != pos / size && col != pos % size && board.at(raw * size + col) == 0) {
						std::vector<bool> valid_value_box = ::getValidValues(raw, col, board, dimension);
						if (valid_value_box.at(i)) {
							nb_allow++;
							break;
						}
					}
			if (nb_allow == 0) {
				board.at(pos) = i + 1;
				pos = -1;
				break;
			}
		}
	}
}
bool isRemovable(int raw, int col, std::vector<int>board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1), value;
	if (board.at(raw * size + col) == 0) return false;
	else value = board.at(raw * size + col);
	std::vector<int> board_copy = board;
	board_copy.at(raw * size + col) = 0;
	std::vector<int> pos_allow_value, pos_allow_unique;
	
	//check if allow unique
	if (nonZeroCount(getValidValues(raw, col, board_copy, dimension)) == 1) return true;
	
	//check if unique allowed in raw, col or square
	int nb_value = 0;
	for (int col_ = 0; col_ < size; col_++) 
		if (col_ != col && getValidValues(raw, col_, board_copy, dimension).at(value - 1)) nb_value++;
	if (nb_value == 0) return true;
	
	nb_value = 0;
	for (int raw_ = 0; raw_ < size; raw_++) 
		if (raw_ != raw && getValidValues(raw_, col, board_copy, dimension).at(value - 1)) nb_value++;
	if (nb_value == 0) return true;

	nb_value = 0;
	int raw_start = raw - raw % dimension.at(1);
	int col_start = col - col % dimension.at(0);
	for (int raw_ = raw_start; raw_ < raw_start + dimension.at(1); raw_++)
		for (int col_ = col_start; col_ < col_start + dimension.at(0); col_++) 
			if ((raw_ != raw || col_ != col) && getValidValues(raw_, col_, board_copy, dimension).at(value - 1)) 
				nb_value++;
	if (nb_value == 0) return true;
	
	return false;

}



int nonZeroCount(std::vector<bool> values) {
	int count = 0;
	for (auto value : values)
		if (value) count++;
	return count;
}
int getNonZeroValue(std::vector<bool> values, int index) {
	if (index == -1) index = rand() % nonZeroCount(values);
	int count = 0;
	for (int i = 0;i<values.size();i++)
		if (values.at(i)) {
			if (count == index)
				return i + 1;
			count++;
		}
	return 0;
}
std::ostream& printBoard(std::ostream& os, std::vector<int> board, std::array<int, 2> dimension) {
	int size = dimension.at(0) * dimension.at(1);
	int width_size = ceil(log10(size)) + 1;
	for (int raw = 0; raw < size; raw++)
	{
		for (int col = 0; col < size; col++)
		{
			if (col % dimension.at(0) == 0) os << "|" << std::setw(width_size);
			int value = board.at(raw * size + col);
			if (value == 0)os << "_" << std::setw(width_size);
			else os << value << std::setw(width_size);
		}
		os << std::setw(width_size + 1) << "|\n";
		if ((raw + 1) % dimension.at(1) == 0) os << "\n";
	}
	return os;
}