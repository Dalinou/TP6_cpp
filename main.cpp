#include <iostream>
#include "sudoku.h"

int main() {
	Sudoku s1 = Sudoku({3,3});
	std::cout << s1;
	Sudoku s2 = Sudoku([](int d1, int d2) {std::vector<int> tmp; for (int _ = 0; _ < pow(d1*d2,2); _++)tmp.push_back(_); return tmp; }(3,4), {3,4});
	std::cout << s2;
}