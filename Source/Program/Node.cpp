#include "Node.h"

#include "Map.h"

int Manhatan(const Point& currentPos, const Point& dest) {
	//return CalculateEuclidean(currentPos.x, dest.x, currentPos.y, dest.y);
	return std::abs(dest.x - currentPos.x) + std::abs(dest.y - currentPos.y);
}

int Euclidean(const Point& currentPos, const Point& dest) {
	return CalculateEuclidean(currentPos.x, dest.x, currentPos.y, dest.y);
}

float FastEuclidean(const Point& currentPos, const Point& dest) {
	float x = std::pow(dest.x - currentPos.x, 2);
	float y = std::pow(dest.y - currentPos.y, 2);;
	return x + y;
}


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


std::vector<Node> Node::GetChildrenBFS4(std::unordered_set<Node, NodeHash, NodeEq>& closed) {
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


std::vector<EvalNode> EvalNode::GetChildrenBestFS(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<EvalNode> children;
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, Manhatan(node.pos, dest));
			}
			closed.insert(node);
		}
		};
	helper(-1, -1);
	helper(-1, 0);
	helper(-1, 1);

	helper(0, -1);
	helper(0, 1);

	helper(1, -1);
	helper(1, 0);
	helper(1, 1);

	return children;
}

std::vector<EvalNode> EvalNode::GetChildrenBestFS2(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<EvalNode> children;
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, Euclidean(node.pos, dest));
			}
			closed.insert(node);
		}
		};
	//helper(-1, -1);
	helper(-1, 0);
	//helper(-1, 1);

	helper(0, -1);
	helper(0, 1);

	//helper(1, -1);
	helper(1, 0);
	//helper(1, 1);

	return children;
}

std::vector<EvalNode> EvalNode::GetChildrenBestFS3(std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<EvalNode> children;
	children.reserve(4);
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, FastEuclidean(node.pos, dest));
			}
			closed.insert(node);
		}
		};
	//helper(-1, -1);
	helper(-1, 0);
	//helper(-1, 1);

	helper(0, -1);
	helper(0, 1);

	//helper(1, -1);
	helper(1, 0);
	//helper(1, 1);

	return children;
}

std::vector<EvalNode> EvalNode::GetChildrenBestFS4(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<EvalNode> children;
	children.reserve(4);
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			if (!map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile].isPassable) {
				return;
			}
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, FastEuclidean(node.pos, dest));
			}
			closed.insert(node);
		}
		};
	helper(-1, 0);
	helper(0, -1);
	helper(0, 1);
	helper(1, 0);

	return children;
}

std::vector<StarNode> StarNode::GetChildrenAStar(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<StarNode> children;
	children.reserve(4);
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			if (!map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile].isPassable) {
				return;
			}
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, FastEuclidean(node.pos, dest), cost + 1.0f);
			}
			closed.insert(node);
		}
		};
	helper(-1, 0);
	helper(0, -1);
	helper(0, 1);
	helper(1, 0);

	return children;
}


std::vector<StarNode> StarNode::GetChildrenAStar2(Map* map, std::unordered_set<Node, NodeHash, NodeEq>& closed, const Point& dest, const float cost) {
	// Zgdonie z ruchem zegara zaczynaj¹c o 11 
	std::vector<StarNode> children;
	children.reserve(4);
	MapPos mp;

	auto helper = [&](int8_t rd, int8_t cd) {
		mp.absTileRows = node.pos.x + rd;
		mp.absTileColumn = node.pos.y + cd;
		mp.RecalculateFromAbs();
		if (mp.CorrectnessAbsTileS()) {
			if (!map->GetRegions()[mp.rows][mp.column].TileMap[mp.rowsTile][mp.columnTile].isPassable) {
				return;
			}
			Node node(Point{ mp.absTileRows, mp.absTileColumn }, this->node.pos);
			if (!closed.contains(node)) {
				children.emplace_back(node, FastEuclidean(node.pos, dest), cost + 1.0f);
			}
			//closed.insert(node);
		}
		};
	helper(-1, 0);
	helper(0, -1);
	helper(0, 1);
	helper(1, 0);

	return children;
}