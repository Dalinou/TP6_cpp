#pragma once
#include <vector>
#include <array>
#include <iostream>

class Sudoku
{
public:
	Sudoku(int difficulty = 3, std::array<int, 2> dimension = { 3,3 });// Génération auto, difficulty from 1 to 10
	Sudoku(std::vector<int> grid, std::array<int, 2> dimension);// Génération manuelle
	friend std::ostream& operator<<(std::ostream& os, Sudoku& s);
	std::ostream& getSolved(std::ostream& os);
	bool generate(int nb_value = 0, int max_try = 1000);
	bool isValid();
	bool solve(bool check_unicity = false);
	std::vector<bool> getValidValues(int raw, int col);
	std::vector<bool> getRawValues(int raw);
	std::vector<bool> getColValues(int col);
	std::vector<bool> getSquareValues(int raw, int col);
	bool isRemovable(int raw, int col);
private:
	std::vector<int> _board;
	std::vector<int> _solution;
	const std::array<int, 2> _dimension;// Dimension d'un "Square"
	const int _size;// Taille du sudoku
};

std::vector<bool> getValidValues(int raw, int col, std::vector<int>board, std::array<int, 2> dimension);
std::vector<bool> getRawValues(int raw, std::vector<int>board, std::array<int, 2> dimension);
std::vector<bool> getColValues(int col, std::vector<int>board, std::array<int, 2> dimension);
std::vector<bool> getSquareValues(int raw, int col, std::vector<int>board, std::array<int, 2> dimension);
void addForcedValues(std::vector<int>& board, std::array<int, 2> dimension);
bool isRemovable(int raw, int col, std::vector<int>board, std::array<int, 2> dimension);
int nonZeroCount(std::vector<bool> values);
int getNonZeroValue(std::vector<bool> values, int index = -1);// -1 for random zero value

std::ostream& printBoard(std::ostream& os, std::vector<int> board, std::array<int, 2> dimension);