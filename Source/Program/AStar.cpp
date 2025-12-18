#include "AStar.h"

#include <queue>
#include <print>

#include "Map.h"

std::vector<Point> AStar(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, FastEuclidean(startNode.pos, destPoint), 0.0f);
	closed.insert(startNode);
	std::vector<StarNode> children = startStarNode.GetChildrenAStar(map, closed, destPoint,0.0f);
	for (auto& it : children) {
		open.push(it);
	}

	while (!open.empty()) {
		StarNode currentNode = open.top();
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A Star Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStar(map, closed, destPoint,currentNode.g);
		open.pop();
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}

std::vector<Point> AStar2(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, FastEuclidean(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A Star2 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStar2(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}

std::vector<Point> AStarPlus(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec

	// In real map  tilesTwo also need to be checked
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}
	if (!map->GetRegions()[dest.rows][dest.column].TileMap[dest.rowsTile][dest.columnTile].isPassable) {
		return{};
	}

	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, FastEuclidean(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A StarPlus Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			std::reverse(path.begin(), path.end());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStar2(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	std::println("A StarPlus failed");
	std::println("Open: {}", open.size());
	std::println("Closed: {}", closed.size());
	return {};
}

std::vector<Point> AStarOct(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec

	// In real map  tilesTwo also need to be checked
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}
	if (!map->GetRegions()[dest.rows][dest.column].TileMap[dest.rowsTile][dest.columnTile].isPassable) {
		return{};
	}

	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, FastEuclidean(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A StarOct Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			std::reverse(path.begin(), path.end());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStarOct(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	std::println("A StarOct failed");
	std::println("Open: {}", open.size());
	std::println("Closed: {}", closed.size());
	return {};
}

std::vector<Point> AStarSmart(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec

	// In real map  tilesTwo also need to be checked
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}
	if (!map->GetRegions()[dest.rows][dest.column].TileMap[dest.rowsTile][dest.columnTile].isPassable) {
		return{};
	}

	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, Euclidean(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A StarSmart Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			std::reverse(path.begin(), path.end());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStarSmart(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	std::println("A StarSmart failed");
	std::println("Open: {}", open.size());
	std::println("Closed: {}", closed.size());
	return {};
}

std::vector<Point> AStarSmart2(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec

	// In real map  tilesTwo also need to be checked
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}
	if (!map->GetRegions()[dest.rows][dest.column].TileMap[dest.rowsTile][dest.columnTile].isPassable) {
		return{};
	}

	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, HeuristicOctile(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A StarSmart2 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			std::reverse(path.begin(), path.end());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStarSmart2(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	std::println("A StarSmart2 failed");
	std::println("Open: {}", open.size());
	std::println("Closed: {}", closed.size());
	return {};
}

std::vector<Point> AStarSmart3(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	if (start.absTileRows == dest.absTileRows && start.absTileColumn == dest.absTileColumn) {
		return{};
	}
	// No need to check if start or dest is correct since it will be casted away in children anyway and return empty vec

	// In real map  tilesTwo also need to be checked
	if (!map->GetRegions()[start.rows][start.column].TileMap[start.rowsTile][start.columnTile].isPassable) {
		return{};
	}
	if (!map->GetRegions()[dest.rows][dest.column].TileMap[dest.rowsTile][dest.columnTile].isPassable) {
		return{};
	}

	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	StarNode startStarNode(startNode, HeuristicOctile(startNode.pos, destPoint), 0.0f);

	open.push(startStarNode);

	while (!open.empty()) {
		StarNode currentNode = open.top();
		open.pop();
		if (closed.contains(currentNode.node)) {
			continue;
		}
		closed.insert(currentNode.node);
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
			path.emplace_back(lastNode.pos);
			while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
				Node search(lastNode.parent, lastNode.parent);
				search.pos = lastNode.parent;
				auto testNode = closed.find(search);
				if (testNode != closed.end()) {
					lastNode = *testNode;
				}
				else {
					return path;
				}
				path.emplace_back(lastNode.pos);
			}
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("A StarSmart3 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			std::reverse(path.begin(), path.end());
			return path;
		}

		std::vector<StarNode> allChildren = currentNode.GetChildrenAStarSmart3(map, closed, destPoint, currentNode.g);
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	std::println("A StarSmart3 failed");
	std::println("Open: {}", open.size());
	std::println("Closed: {}", closed.size());
	return {};
}