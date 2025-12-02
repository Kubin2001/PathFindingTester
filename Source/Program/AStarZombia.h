#pragma once

#include <algorithm>
#include "Addons.h"

class Map;

typedef std::pair<double, std::pair<int, int> > pPair;

// A structure to hold the necessary parameters
struct cell {
	// Row and Column index of its parent
	// Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	int parent_i, parent_j;
	// f = g + h
	double f, g, h;
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col);

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int row, int col);

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, std::pair<int, int> dest);

// A Utility Function to calculate the 'h' heuristics.


// A Utility Function to trace the path from the source
// to destination
std::vector<Point> tracePath(std::vector<std::vector<cell>> cellDetails, std::pair<int, int> dest);

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
std::vector <Point> ZombiaAStar(Map *map, std::pair<int, int> src, std::pair<int, int> dest);
