#pragma once

#pragma once


#include <unordered_set>
#include <array>
#include <queue>

#include "Addons.h"



int Manhatan(const Point& currentPos, const Point& dest);

float Euclidean(const Point& currentPos, const Point& dest);

float Euclidean2(const Point& currentPos, const Point& dest);

float FastEuclidean(const Point& currentPos, const Point& dest);

float HeuristicOctile(const Point& a, const Point& b);

inline float HeuristicOctileFast(const Point& a, const Point& b) {
	// Sta³e wyliczone raz, ¿eby procesor nie liczy³ w kó³ko
	constexpr float D = 1.0f;
	constexpr float D2 = 1.41421356f;

	const float dx = std::abs(static_cast<float>(a.x - b.x));
	const float dy = std::abs(static_cast<float>(a.y - b.y));

	// Wzór: Tyle kroków na skos ile siê da (min), reszta prosto
	return D * (dx + dy) + (D2 - 2 * D) * std::min(dx, dy);
}

class Map;
struct NodeEq;

struct NodeHash;

struct PointHash {
	std::size_t operator()(const Point& p) const {
		std::size_t h1 = std::hash<int>{}(p.x);
		std::size_t h2 = std::hash<int>{}(p.y);
		return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
	}
};

struct PointEq {
	bool operator()(const Point& p, const Point& otherP) const {
		return p == otherP;
	}
};

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



constexpr std::array<unsigned int, 8> OctileTileCost{};

template<int tileSize = 40>
constexpr void CalcTileCosts() {
	constexpr int centerX = 1000;
	constexpr int centerY = 1000;

	// Right
	OctileTileCost[0] = HeuristicOctile({ centerX, centerY }, { centerX + tileSize, centerY });

	// Left
	OctileTileCost[1] = HeuristicOctile({ centerX, centerY }, { centerX - tileSize, centerY });

	// Up
	OctileTileCost[2] = HeuristicOctile({ centerX, centerY }, { centerX, centerY - tileSize });

	// Down
	OctileTileCost[3] = HeuristicOctile({ centerX, centerY }, { centerX, centerY + tileSize });

	// Up-Right
	OctileTileCost[4] = HeuristicOctile({ centerX, centerY }, { centerX + tileSize, centerY - tileSize });

	// Up-Left
	OctileTileCost[5] = HeuristicOctile({ centerX, centerY }, { centerX - tileSize, centerY - tileSize });

	// Down-Right
	OctileTileCost[6] = HeuristicOctile({ centerX, centerY }, { centerX + tileSize, centerY + tileSize });

	// Down-Left
	OctileTileCost[7] = HeuristicOctile({ centerX, centerY }, { centerX - tileSize, centerY + tileSize });
}
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

	std::vector<StarNode> GetChildrenAStarOct(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);

	std::vector<StarNode> GetChildrenAStarSmart(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);

	std::vector<StarNode> GetChildrenAStarSmart2(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);

	std::vector<StarNode> GetChildrenAStarSmart3(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost);

	std::vector<StarNode> GetChildrenAStarLinear(Map* map, const Point& dest, const float cost);
};

struct StarNodeComp {
	bool operator()(const StarNode& node, const StarNode& other) {
		if ((node.h + node.g) > (other.h + other.g)) {
			return true;
		}
		return false;
	}
};

Point GenerateSimpleChildren(Map* map, const Point& node, const Point& dest, bool& stop);

inline static std::unordered_set<Node, NodeHash, NodeEq> AStartStaticClosed{};
inline static std::priority_queue<StarNode, std::vector<StarNode>, StarNodeComp> AStartStaticOpen{};