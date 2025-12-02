#include "AStarZombia.h"

#include <stack>
#include <set>
#include <print>

#include "Map.h"

//ASTAR

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(int row, int col) {
	// Returns true if row number and column number
	// is in range
	MapPos mp;
	mp.absTileRows = row;
	mp.absTileColumn = col;
	return mp.CorrectnessAbsTileS();
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(int row, int col) {
	return true;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(int row, int col, std::pair<int, int> dest) {
	if (row == dest.first && col == dest.second) { return true; }
	else { return false; }
}


// A Utility Function to trace the path from the source
// to destination
std::vector<Point> tracePath(std::vector<std::vector<cell>> cellDetails, std::pair<int, int> dest) {
	int row = dest.first;
	int col = dest.second;

	std::stack<std::pair<int, int>> Path;

	while (!(cellDetails[row][col].parent_i == row && cellDetails[row][col].parent_j == col)) {
		Path.push(std::make_pair(row, col));
		int temp_row = cellDetails[row][col].parent_i;
		int temp_col = cellDetails[row][col].parent_j;
		row = temp_row;
		col = temp_col;
	}

	std::vector<Point> vec;
	Path.push(std::make_pair(row, col));
	while (!Path.empty()) {
		std::pair<int, int> p = Path.top();
		Path.pop();
		vec.emplace_back(p.first, p.second);
	}
	std::println("Zombia A Star Executed");
	return vec;
}

// A Function to find the shortest path between
// a given source cell to a destination cell according
// to A* Search Algorithm
std::vector<Point> ZombiaAStar(Map *map, std::pair<int, int> src, std::pair<int, int> dest) {
	// If the source is out of range
	std::vector<Point> vec;

	// Create a closed list and initialise it to false which
	// means that no cell has been included yet This closed
	// list is implemented as a boolean 2D array
	int column = MapPos::tilesPerRegion * MapPos::regionsCountWidth;
	int rows = MapPos::tilesPerRegion * MapPos::regionsCountHeight;
	std::vector<std::vector<bool>> closedList(rows, std::vector<bool>(column, false));

	// Declare a 2D array of structure to hold the details
	// of that cell
	std::vector<std::vector<cell>> cellDetails(rows, std::vector<cell>(column));

	int i, j;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < column; j++) {
			cellDetails[i][j].f = FLT_MAX;
			cellDetails[i][j].g = FLT_MAX;
			cellDetails[i][j].h = FLT_MAX;
			cellDetails[i][j].parent_i = -1;
			cellDetails[i][j].parent_j = -1;
		}
	}

	// Initialising the parameters of the starting node
	i = src.first, j = src.second;
	cellDetails[i][j].f = 0.0;
	cellDetails[i][j].g = 0.0;
	cellDetails[i][j].h = 0.0;
	cellDetails[i][j].parent_i = i;
	cellDetails[i][j].parent_j = j;

	/*
	 Create an open list having information as-
	 <f, <i, j>>
	 where f = g + h,
	 and i, j are the row and column index of that cell
	 Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
	 This open list is implemented as a set of pair of
	 pair.*/
	std::set<pPair> openList;

	// Put the starting cell on the open list and set its
	// 'f' as 0
	openList.insert(std::make_pair(0.0, std::make_pair(i, j)));

	// We set this boolean value as false as initially
	// the destination is not reached.

	while (!openList.empty()) {
		pPair p = *openList.begin();

		// Remove this vertex from the open list
		openList.erase(openList.begin());

		// Add this vertex to the closed list
		i = p.second.first;
		j = p.second.second;
		closedList[i][j] = true;

		double gNew, hNew, fNew;

		//----------- 1st Successor (North) ------------

		// Only process this cell if this is a valid one
		if (isValid(i - 1, j) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i - 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i - 1][j].parent_i = i;
				cellDetails[i - 1][j].parent_j = j;
				printf("The destination cell is found 1\n");
				return tracePath(cellDetails, dest);
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i - 1][j] == false && isUnBlocked(i - 1, j) == true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = CalculateEuclidean(i - 1, j, dest.first, dest.second);
				fNew = gNew + hNew;
				if (cellDetails[i - 1][j].f == FLT_MAX
					|| cellDetails[i - 1][j].f > fNew) {
					openList.insert(std::make_pair(
						fNew, std::make_pair(i - 1, j)));

					// Update the details of this cell
					cellDetails[i - 1][j].f = fNew;
					cellDetails[i - 1][j].g = gNew;
					cellDetails[i - 1][j].h = hNew;
					cellDetails[i - 1][j].parent_i = i;
					cellDetails[i - 1][j].parent_j = j;
				}
			}
		}

		//----------- 2nd Successor (South) ------------

		// Only process this cell if this is a valid one
		if (isValid(i + 1, j) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i + 1, j, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i + 1][j].parent_i = i;
				cellDetails[i + 1][j].parent_j = j;
				printf("The destination cell is found 2\n");
				return tracePath(cellDetails, dest);
			}
			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i + 1][j] == false
				&& isUnBlocked(i + 1, j)
				== true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = CalculateEuclidean(i + 1, j, dest.first, dest.second);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//                OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (cellDetails[i + 1][j].f == FLT_MAX
					|| cellDetails[i + 1][j].f > fNew) {
					openList.insert(std::make_pair(
						fNew, std::make_pair(i + 1, j)));
					// Update the details of this cell
					cellDetails[i + 1][j].f = fNew;
					cellDetails[i + 1][j].g = gNew;
					cellDetails[i + 1][j].h = hNew;
					cellDetails[i + 1][j].parent_i = i;
					cellDetails[i + 1][j].parent_j = j;
				}
			}
		}

		//----------- 3rd Successor (East) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j + 1) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j + 1, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i][j + 1].parent_i = i;
				cellDetails[i][j + 1].parent_j = j;
				printf("The destination cell is found 3\n");
				return tracePath(cellDetails, dest);
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j + 1] == false && isUnBlocked(i, j + 1) == true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = CalculateEuclidean(i, j + 1, dest.first, dest.second);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//                OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (cellDetails[i][j + 1].f == FLT_MAX
					|| cellDetails[i][j + 1].f > fNew) {
					openList.insert(std::make_pair(
						fNew, std::make_pair(i, j + 1)));

					// Update the details of this cell
					cellDetails[i][j + 1].f = fNew;
					cellDetails[i][j + 1].g = gNew;
					cellDetails[i][j + 1].h = hNew;
					cellDetails[i][j + 1].parent_i = i;
					cellDetails[i][j + 1].parent_j = j;
				}
			}
		}

		//----------- 4th Successor (West) ------------

		// Only process this cell if this is a valid one
		if (isValid(i, j - 1) == true) {
			// If the destination cell is the same as the
			// current successor
			if (isDestination(i, j - 1, dest) == true) {
				// Set the Parent of the destination cell
				cellDetails[i][j - 1].parent_i = i;
				cellDetails[i][j - 1].parent_j = j;
				printf("The destination cell is found 4\n");
				return tracePath(cellDetails, dest);
			}

			// If the successor is already on the closed
			// list or if it is blocked, then ignore it.
			// Else do the following
			else if (closedList[i][j - 1] == false && isUnBlocked(i, j - 1) == true) {
				gNew = cellDetails[i][j].g + 1.0;
				hNew = CalculateEuclidean(i, j - 1, dest.first, dest.second);
				fNew = gNew + hNew;

				// If it isn’t on the open list, add it to
				// the open list. Make the current square
				// the parent of this square. Record the
				// f, g, and h costs of the square cell
				//                OR
				// If it is on the open list already, check
				// to see if this path to that square is
				// better, using 'f' cost as the measure.
				if (cellDetails[i][j - 1].f == FLT_MAX
					|| cellDetails[i][j - 1].f > fNew) {
					openList.insert(std::make_pair(
						fNew, std::make_pair(i, j - 1)));

					// Update the details of this cell
					cellDetails[i][j - 1].f = fNew;
					cellDetails[i][j - 1].g = gNew;
					cellDetails[i][j - 1].h = hNew;
					cellDetails[i][j - 1].parent_i = i;
					cellDetails[i][j - 1].parent_j = j;
				}
			}
		}
	}

	// When the destination cell is not found and the open
	// list is empty, then we conclude that we failed to
	// reach the destination cell. This may happen when the
	// there is no way to destination cell (due to
	// blockages)
	std::cout << "Failed to find the Destination Cell\n";

	//pawn->path = tracePath(cellDetails, dest); // to wywala nie rtobiæ tak
	//pawn->creatingPath = false;

	vec = {};
	return vec;
}