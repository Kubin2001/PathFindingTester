#pragma once

#pragma once


#include <unordered_set>

#include "Addons.h"

int Manhatan(const Point& currentPos, const Point& dest);

int Euclidean(const Point& currentPos, const Point& dest);

float FastEuclidean(const Point& currentPos, const Point& dest);

class Map;
struct NodeEq;

struct NodeHash;

struct Node {
	Point pos;
	Point parent;

	Node() = default;

	Node(const Point& pos, const Point& parent) {
		this->pos = pos;
		this->parent = parent;
	}

	bool operator == (const Node& other)const {
		if (this->pos == other.pos) {
			return true;
		}
		return false;
	}

	std::vector<Node> GetChildrenBFS1(const std::vector<Node>& closed);

	std::vector<Node> GetChildrenBFS2(std::unordered_set<Node, NodeHash, NodeEq>& closed);

	std::vector<Node> GetChildrenBFS3(std::unordered_set<Node, NodeHash, NodeEq>& closed);

	std::vector<Node> GetChildrenBFS4(std::unordered_set<Node, NodeHash, NodeEq>& closed);
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

struct EvalNodeComp;

struct StarNode {
	Node node;
	float h = 0;
	float g = 0;

	StarNode() = default;

	StarNode(const Node& node, float heutistic, float gCost) {
		this->node = node;
		this->h = heutistic;
		this->g = gCost;
	}

	std::vector<StarNode> GetChildrenAStar(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);

	std::vector<StarNode> GetChildrenAStar2(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);
};

struct StarNodeComp {
	bool operator()(const StarNode& node, const StarNode& other) {
		if ((node.h + node.g) > (other.h + other.g)) {
			return true;
		}
		return false;
	}
};