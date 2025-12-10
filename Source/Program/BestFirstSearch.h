#pragma once

#include <unordered_set>

#include "Node.h"
class Map;

std::vector<Point> BestFS(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFS2(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFS3(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFSAdv(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);