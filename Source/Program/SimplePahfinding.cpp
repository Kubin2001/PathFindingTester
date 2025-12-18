#include "SimplePahfinding.h"

#include <print>
#include "Map.h"


std::vector<Point> SimplePathfinding(Map* map, MapPos& start, MapPos& dest) {;
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec
	// In real map  tilesTwo also need to be checked in these case no noeed to check dest since it will break on nearest unpassable
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}

	bool stop = false;
	std::vector<Point> path;
	Point bestNode{ start.absTileRows,start.absTileColumn };
	path.emplace_back(bestNode);
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	int iter = 0;
	while (true && iter < 1000) { // it should never crooss iter it is only for safety
		bestNode = GenerateSimpleChildren(map, bestNode, destPoint,stop);
		if (stop) {
			//std::println("Simple Pathfinding Succeded stopped at unpassable");
			return path;
		}
		else {
			if (bestNode == destPoint) {
				//std::println("Simple Pathfinding Succeded found best");
				path.emplace_back(bestNode);
				return path;
			}
			else {
				path.emplace_back(bestNode);
			}
		}
		iter++;
	}
	//std::println("Simple  Pathfinding failed");
	return path;
}