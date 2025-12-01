#include "Node.h"


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