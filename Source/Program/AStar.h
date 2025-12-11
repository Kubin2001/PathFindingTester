#pragma once

#include <vector>
#include "Node.h"

class Map;

std::vector<Point> AStar(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);

std::vector<Point> AStar2(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);

std::vector<Point> AStarPlus(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);