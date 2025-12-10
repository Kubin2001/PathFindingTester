#include "AStar.h"

#include <queue>
#include <print>

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