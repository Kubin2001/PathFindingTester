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

	std::vector<EvalNode> GetChildrenBestFS(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest); // Managatan

	//Eucklides i tylko ruch lewy prawy góra dó³
	std::vector<EvalNode> GetChildrenBestFS2(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest); 

	std::vector<EvalNode> GetChildrenBestFS3(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest);

	std::vector<EvalNode> GetChildrenBestFS4(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest);
};

struct EvalNodeComp {
	bool operator()(const EvalNode& node, const EvalNode& other) {
		if (node.manhatanDistance > other.manhatanDistance) {
			return true;
		}
		return false;
	}
};


std::vector<Point> BestFS(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFS2(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFS3(Map* map, MapPos& start, MapPos& dest);

std::vector<Point> BestFSAdv(Map* map, MapPos& start, MapPos& dest, std::vector<Point>& globalClosed);