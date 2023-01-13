#include <iostream>
#include "sudoku.h"
#include <iomanip>
#include <time.h>
#include <algorithm>
#include <chrono>

int main() {
	srand(time(NULL));
	auto func = []() {
		Sudoku s2 = Sudoku(10, { 3,3 });
		std::cout << s2;
		std::cout << "Solved:\n";
		s2.getSolved(std::cout);
	};
	for (int i = 0; i < 100; i++) {
		std::cout << "Sudoku " << i << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		func();
		auto end = std::chrono::high_resolution_clock::now();
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	}
		
}