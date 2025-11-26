#pragma once

#include <unordered_set>

#include "Addons.h"

class Map;

struct Node;


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

	std::vector<Node> GetChildren(const std::vector<Node>& closed);
};


std::vector<Point> BFS(Map* map, MapPos& start, MapPos& dest);