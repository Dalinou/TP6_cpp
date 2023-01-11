#include <iostream>
#include "sudoku.h"

int main() {
	Sudoku s1 = Sudoku({3,3});
	std::cout << s1;
	Sudoku s2 = Sudoku([] {std::vector<int> tmp; for (int _ = 0; _ < 81; _++)tmp.push_back(_); return tmp; }(), {3,3});
	std::cout << s2;
}