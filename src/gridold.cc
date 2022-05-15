#include "textdisplay.h"
#include "grid.h"
#include <iostream>
#include "state.h"

// Constructor implementation. 
Grid::~Grid() { 
	delete td;
	delete ob;
}

// Determines if the grid is full. 
bool Grid::isFull() const {
	int sizee = theGrid.size();
	for (int i = 0; i < sizee; ++i) {
		std::vector <Cell> tmp = theGrid[i];
		int size_tmp = tmp.size();
		for (int j = 0; j < size_tmp; ++j) {
			Info information = tmp[j].getInfo();
			if (information.colour == Colour::NoColour) {
				return false;
			}
		}
	}
	return true;
}

// Determines who has more pieces given that the grid is full. 
Colour Grid::whoWon() const {
	int numBlack = 0;
	int numWhite = 0;
	int sizee = theGrid.size();
	for (int i = 0; i < sizee; ++i) {
		std::vector <Cell> tmp = theGrid[i];
		int size_tmp = tmp.size();
		for (int j = 0; j < size_tmp; ++j) {
			Info information = tmp[j].getInfo();
			if (information.colour == Colour::Black) {
				numBlack += 1;
			} else {
				numWhite += 1;
			}
		}
	}
	if (numBlack > numWhite) return Colour::Black;
	if (numBlack < numWhite) return Colour::White;
	return Colour::NoColour;
}

// Initializes grid and set observers. 
void Grid::init(size_t n) {
	theGrid.clear();
	int mid = n / 2;
	delete td;
	td = new TextDisplay{n};

	for (int i = 0; i < n; ++i) {
		std::vector <Cell> tmp;
		for (int j = 0; j < n; ++j) {
			class Cell cell = Cell{i, j};
			if ((i == mid - 1) && ( j == mid - 1)) {
				cell.setPiece(Colour::Black);
			} else if ((i == mid) && (j == mid)) {
				cell.setPiece(Colour::Black);
			} else if ((i == mid - 1) && (j == mid)) {
				cell.setPiece(Colour::White);
			} else if ((i == mid) && (j == mid - 1)) {
				cell.setPiece(Colour::White);
			} else {
				cell.setPiece(Colour::NoColour);
			}
			tmp.emplace_back(cell);
		}
		theGrid.emplace_back(tmp);
	}

	// attach observers for every cell. 
	for (int i = 0; i < n; ++i) {
		std::vector <Cell> &tmp = theGrid[i];
		for (int j = 0; j < n; ++j) {
			tmp[j].attach(td);
			if ((j - 1 >= 0) && ( i - 1 >= 0) && (j + 1 < n) && (i + 1 < n)) {
				tmp[j].attach(&tmp[j - 1]);
				tmp[j].attach(&tmp[j + 1]);
				tmp[j].attach(&(theGrid[i-1][j]));
				tmp[j].attach(&(theGrid[i+1][j]));
				tmp[j].attach(&(theGrid[i-1][j-1]));
				tmp[j].attach(&(theGrid[i-1][j+1]));
				tmp[j].attach(&(theGrid[i+1][j+1]));
				tmp[j].attach(&(theGrid[i+1][j-1]));
			} else if ((j - 1 < 0) && (i - 1 < 0)) {
				tmp[j].attach(&tmp[j+1]);
				tmp[j].attach(&theGrid[i+1][j]);
				tmp[j].attach(&theGrid[i+1][j+1]);
			} else if ((j + 1 >= n) && (i + 1 >= n)) {
				tmp[j].attach(&tmp[j-1]);
				tmp[j].attach(&theGrid[i-1][j]);
				tmp[j].attach(&theGrid[i-1][j-1]);
			} else if ((j + 1 >=n) && (i - 1 < 0)) {
				tmp[j].attach(&tmp[j-1]);
				tmp[j].attach(&theGrid[i+1][j]);
				tmp[j].attach(&theGrid[i+1][j-1]);
			} else if ((j - 1 < 0) && (i + 1 >=n)){
				tmp[j].attach(&tmp[j+1]);
				tmp[j].attach(&theGrid[i-1][j+1]);
				tmp[j].attach(&theGrid[i-1][j]);
			} else if (i - 1 < 0) {
				tmp[j].attach(&tmp[j+1]);
				tmp[j].attach(&tmp[j-1]);
				tmp[j].attach(&theGrid[i+1][j]);
				tmp[j].attach(&theGrid[i+1][j+1]);
				tmp[j].attach(&theGrid[i+1][j-1]);
			} else if (i + 1 >= n) {
				tmp[j].attach(&tmp[j+1]);
			  tmp[j].attach(&tmp[j-1]);
				tmp[j].attach(&theGrid[i-1][j]);
				tmp[j].attach(&theGrid[i-1][j+1]);
				tmp[j].attach(&theGrid[i-1][j-1]);
			} else if (j + 1 >= n) {
				tmp[j].attach(&tmp[j-1]);
				tmp[j].attach(&theGrid[i-1][j-1]);
			  tmp[j].attach(&theGrid[i+1][j]);
				tmp[j].attach(&theGrid[i-1][j]);
				tmp[j].attach(&theGrid[i+1][j-1]);
			} else {
				tmp[j].attach(&tmp[j+1]);
				tmp[j].attach(&theGrid[i+1][j+1]);
			  tmp[j].attach(&theGrid[i-1][j+1]);
				tmp[j].attach(&theGrid[i-1][j]);
				tmp[j].attach(&theGrid[i+1][j]);
			}
			theGrid[i][j].attach(td);
		}
	}
}

// Sets a piece on the board. 
void Grid::setPiece(size_t r, size_t c, Colour colour) {
	if ((r >= theGrid.size()) || c >= theGrid.size()) throw std::out_of_range("f");
	if (theGrid[r][c].getInfo().colour == Colour::NoColour) {
	  Cell &cell =  theGrid.at(r).at(c);
		cell.setPiece(colour);
		cell.notifyObservers();	
	} else {
		throw InvalidMove{};
	}
}

// Flips a piece on the board. 
void Grid::toggle(size_t r, size_t c) {
	theGrid.at(r).at(c).toggle();
}

// Outputs a board to the screen.
std::ostream &operator<<(std::ostream &out, const Grid &g) {
	std::cout << *(g.td);
	return out;
}	
