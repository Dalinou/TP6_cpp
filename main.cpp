#include <iostream>
#include "sudoku.h"
#include <iomanip>

int main() {
	Sudoku s1 = Sudoku({3,3});
	std::cout << s1;
	Sudoku s2 = Sudoku([](int d1, int d2) {std::vector<int> tmp; for (int _ = 0; _ < pow(d1*d2,2); _++)tmp.push_back(_%10); return tmp; }(5,5), {5,5});
	std::cout << s2;
	std::vector<int> test_grid = {
		0,8,0,0,0,0,0,2,0,
		3,0,0,8,1,9,0,0,7,
		0,0,9,0,0,0,4,0,0,
		0,0,3,0,5,0,1,0,0,
		0,0,0,0,9,0,2,0,0,
		0,0,0,2,0,4,0,0,0,
		0,0,0,5,0,7,0,0,0,
		0,7,6,0,3,0,9,1,0,
		4,0,0,0,0,0,0,0,2 };
	Sudoku s3 = Sudoku(test_grid, { 3,3 });
	std::cout << s3;
	std::vector<bool> valid_values = s3.getRawValues(0);
	for (int j = 0; j < 9; j++)
		std::cout << j + 1 << ":" << std::setw(4) << (valid_values.at(j) ? "\033[1;32mT\033[0m  " : "\033[1;31mF\033[0m  ");
	std::cout << std::endl;
	valid_values = s3.getColValues(0);
	for (int j = 0; j < 9; j++)
		std::cout << j + 1 << ":" << std::setw(4) << (valid_values.at(j) ? "\033[1;32mT\033[0m  " : "\033[1;31mF\033[0m  ");
	std::cout << std::endl;
	valid_values = s3.getSquareValues(0, 0);
	for (int j = 0; j < 9; j++)
		std::cout << j + 1 << ":" << std::setw(4) << (valid_values.at(j) ? "\033[1;32mT\033[0m  " : "\033[1;31mF\033[0m  ");
	std::cout << std::endl;
	valid_values = s3.getValidValues(0, 0);
	for (int j = 0; j < 9; j++)
		std::cout << j + 1 << ":" << std::setw(4) << (valid_values.at(j) ? "\033[1;32mT\033[0m  " : "\033[1;31mF\033[0m  ");
	std::cout << std::endl << std::endl;
	for (int i = 0; i < 9; i++)
	{
		std::vector<bool> valid_values = s3.getValidValues(0, i);
		for (int j = 0; j < 9; j++)
			std::cout << j + 1 << ":" << std::setw(4) << (valid_values.at(j) ? "\033[1;32mT\033[0m  " : "\033[1;31mF\033[0m  ");
		std::cout << std::endl;
	}
}