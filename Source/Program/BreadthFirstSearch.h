#pragma once

#include <unordered_set>

#include "Addons.h"

class Map;


struct NodeEq;

struct NodeHash;

struct Node {
	Point pos;
	Point parent;

	Node(const Point& pos, const Point& parent) {
		this->pos = pos;
		this->parent = parent;
	}

	bool operator == (const Node& other)const  {
		if (this->pos == other.pos) {
			return true;
		}
		return false;
	}

	std::vector<Node> GetChildrenBFS1(const std::vector<Node>& closed);

	std::vector<Node> GetChildrenBFS2(std::unordered_set<Node,NodeHash,NodeEq>& closed);

	std::vector<Node> GetChildrenBFS3(std::unordered_set<Node, NodeHash, NodeEq>& closed);
};

struct NodeEq {
	bool operator()(const Node& node, const Node& other) const {
		if (node.pos.x == other.pos.x && node.pos.y == other.pos.y) {
			return true;
		}
		return false;
	}
};

struct NodeHash {
	size_t operator()(const Node& node) const noexcept {
		size_t h1 = std::hash<int>()(node.pos.x);
		size_t h2 = std::hash<int>()(node.pos.y);
		return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
	}
};

std::vector<Point> BFS1(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BFS2(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BFS3(Map* map, MapPos& start, MapPos& dest);