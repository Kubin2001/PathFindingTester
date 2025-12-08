#pragma once

#include <unordered_set>

#include "Node.h"

class Map;

std::vector<Point> BFS1(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BFS2(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BFS3(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BFS4(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);