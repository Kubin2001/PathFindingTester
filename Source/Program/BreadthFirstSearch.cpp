#include "BreadthFirstSearch.h"

#include <print>
#include "Map.h"

bool VecContains(const std::vector<Node>& vec, Node& node) {
	for (const auto& it : vec) {
		if (it.pos == node.pos) {
			return true;
		}
	}
	return false;
}

std::vector<Node> Node::GetChildrenBFS1(const std::vector<Node>& closed) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<Node> children;
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = pos.x + rd;
		mp.absTileColumn = pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->pos);
			if (!VecContains(closed, node)) {
				children.emplace_back(node);
			}
		}
	};
	helper(-1, -1);
	helper(-1, 0);
	helper(-1, 1);

	helper(0, -1);
	helper(0, 0);
	helper(0, 1);

	helper(1, -1);
	helper(1, 0);
	helper(1, 1);

	return children;
}

std::vector<Node> Node::GetChildrenBFS2(std::unordered_set<Node, NodeHash, NodeEq>& closed) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<Node> children;
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = pos.x + rd;
		mp.absTileColumn = pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->pos);
			if (!closed.contains(node)) {
				children.emplace_back(node);
			}
		}
	};
	helper(-1, -1);
	helper(-1, 0);
	helper(-1, 1);

	helper(0, -1);
	helper(0, 0);
	helper(0, 1);

	helper(1, -1);
	helper(1, 0);
	helper(1, 1);

	return children;
}

std::vector<Node> Node::GetChildrenBFS3(std::unordered_set<Node, NodeHash, NodeEq>& closed) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<Node> children;
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = pos.x + rd;
		mp.absTileColumn = pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->pos);
			if (!closed.contains(node)) {
				children.emplace_back(node);
			}
			closed.insert(node);
		}
		};
	helper(-1, -1);
	helper(-1, 0);
	helper(-1, 1);

	helper(0, -1);
	helper(0, 0);
	helper(0, 1);

	helper(1, -1);
	helper(1, 0);
	helper(1, 1);

	return children;
}

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