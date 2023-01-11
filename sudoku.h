#pragma once
#include <vector>
#include <array>
#include <iostream>

class Sudoku
{
public:
	Sudoku(std::array<int, 2> dimension = { 3,3 });// G�n�ration auto
	Sudoku(std::vector<int> grid, std::array<int, 2> dimension);// G�n�ration manuelle
	friend std::ostream& operator<<(std::ostream& os, Sudoku& s);
	bool generate(bool empty=true);
	bool isValid();
private:
	std::vector<int> _board;
	std::vector<int> _solution;
	const std::array<int, 2> _dimension;// Dimension d'un "case"
	const int _size;// Taille du sudoku
};

