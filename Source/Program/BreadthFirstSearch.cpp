#include "BreadthFirstSearch.h"

#include <print>
#include <queue>
#include "Map.h"

std::vector<Point> BFS1(Map* map, MapPos& start, MapPos& dest) {
	std::vector<Node> closed = {};

	std::vector<Node> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{-1,-1});
	closed.emplace_back(startNode);
	std::vector<Node> children = startNode.GetChildrenBFS1(closed);
	for (auto& it : children) {
		open.emplace_back(it);
	}

	while (!open.empty()) {
		for (auto &node : open) {
			if (node.pos.x == dest.absTileRows && node.pos.y == dest.absTileColumn) {
				std::vector<Point> path;
				Node lastNode = node;
				path.emplace_back(lastNode.pos);
				while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
					for (auto& it : closed) {
						if (it.pos == lastNode.parent) {
							lastNode = it;
							break;
						}
					}
					path.emplace_back(lastNode.pos);
				}
				std::println("Breth First Search Succeded");
				std::println("Open: {}",open.size());
				std::println("Closed: {}", closed.size());
				return path;
			}
		}
		std::vector<Node> allChildren;
		for (auto &node : open) {
			closed.emplace_back(node);
			std::vector<Node> children = node.GetChildrenBFS1(closed);
			allChildren.insert(allChildren.end(), children.begin(), children.end());
		}
		open.clear();
		for (auto& it : allChildren) {
			open.emplace_back(it);
		}
	}

	return {};
}

std::vector<Point> BFS2(Map* map, MapPos& start, MapPos& dest) {
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::vector<Node> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	closed.insert(startNode);
	std::vector<Node> children = startNode.GetChildrenBFS2(closed);
	for (auto& it : children) {
		open.emplace_back(it);
	}

	while (!open.empty()) {
		for (auto& node : open) {
			if (node.pos.x == dest.absTileRows && node.pos.y == dest.absTileColumn) {
				std::vector<Point> path;
				Node lastNode = node;
				path.emplace_back(lastNode.pos);
				while (lastNode.parent.x != -1 && lastNode.parent.y != -1) {
					for (auto& it : closed) {
						if (it.pos == lastNode.parent) {
							lastNode = it;
							break;
						}
					}
					path.emplace_back(lastNode.pos);
				}
				std::println("Breth First Search Succeded");
				std::println("Open: {}", open.size());
				std::println("Closed: {}", closed.size());
				return path;
			}
		}
		std::vector<Node> allChildren;
		for (auto& node : open) {
			closed.insert(node);
			std::vector<Node> children = node.GetChildrenBFS2(closed);
			allChildren.insert(allChildren.end(), children.begin(), children.end());
		}
		open.clear();
		for (auto& it : allChildren) {
			open.emplace_back(it);
		}
	}

	return {};
}

std::vector<Point> BFS3(Map* map, MapPos& start, MapPos& dest) {
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::vector<Node> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	closed.insert(startNode);
	std::vector<Node> children = startNode.GetChildrenBFS3(closed);
	for (auto& it : children) {
		open.emplace_back(it);
	}

	while (!open.empty()) {
		for (auto& node : open) {
			if (node.pos.x == dest.absTileRows && node.pos.y == dest.absTileColumn) {
				std::vector<Point> path;
				Node lastNode = node;
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
				std::println("Breth First Search Succeded");
				std::println("Open: {}", open.size());
				std::println("Closed: {}", closed.size());
				return path;
			}
		}
		std::vector<Node> allChildren;
		for (auto& node : open) {
			closed.insert(node);
			std::vector<Node> children = node.GetChildrenBFS3(closed);
			allChildren.insert(allChildren.end(), children.begin(), children.end());
		}
		open.clear();
		for (auto& it : allChildren) {
			open.emplace_back(it);
		}
	}

	return {};
}


std::vector<Point> BFS4(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed) {
	globalClosed.clear();
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::queue<Node> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	closed.insert(startNode);
	std::vector<Node> children = startNode.GetChildrenBFS3(closed);
	for (auto& it : children) {
		open.push(it);
	}

	while (!open.empty()) {
		Node& node = open.front();
		if (node.pos.x == dest.absTileRows && node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = node;
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
			std::println("Best First Search Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<Node> allChildren = node.GetChildrenBFS4(closed);
		for (auto& it : allChildren) {
			open.push(it);
		}
		open.pop();
	}
	return {};
}