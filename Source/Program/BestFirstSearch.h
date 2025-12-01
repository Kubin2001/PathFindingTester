#pragma once

#include <unordered_set>

#include "Node.h"
class Map;

struct EvalNodeComp;

struct EvalNode {
	Node node;
	int manhatanDistance = 0;

	EvalNode() = default;

	EvalNode(const Node& node, int heutistic) {
		this->node = node;
		this->manhatanDistance = heutistic;
	}

	std::vector<EvalNode> GetChildrenBestFS(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest);
};

struct EvalNodeComp {
	bool operator()(const EvalNode& node, const EvalNode& other) {
		if (node.manhatanDistance > other.manhatanDistance) {
			return true;
		}
		return false;
	}
};


int Manhatan(const Point &currentPos, const Point &dest);

std::vector<Point> BestFS(Map* map, MapPos& start, MapPos& dest);