#include "BestFirstSearch.h"
#include <print>
#include <queue>


#include "Map.h"


int Manhatan(const Point& currentPos, const Point& dest) {
	return CalculateEuclidean(currentPos.x, dest.x, currentPos.y, dest.y);
	return std::abs(dest.x - currentPos.x) + std::abs(dest.y - currentPos.y);
}

int Euclidean(const Point& currentPos, const Point& dest) {
	return CalculateEuclidean(currentPos.x, dest.x, currentPos.y, dest.y);
}

float FastEuclidean(const Point& currentPos, const Point& dest) {
	float x = std::pow(dest.x - currentPos.x, 2);
	float y = std::pow(dest.y - currentPos.y, 2);;
	return x+y;
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
				children.emplace_back(node,Manhatan(node.pos,dest));
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

std::vector<Point> BestFS(Map* map, MapPos& start, MapPos& dest) {
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<EvalNode, std::vector<EvalNode>, EvalNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	EvalNode startEvalNode(startNode, Manhatan(startNode.pos, destPoint));
	closed.insert(startNode);
	std::vector<EvalNode> children = startEvalNode.GetChildrenBestFS(closed,destPoint);
	for (auto& it : children) {
		open.push(it);
	}

	while (!open.empty()) {
		EvalNode currentNode = open.top();
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
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
			std::println("Best First Search 1 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<EvalNode> allChildren = currentNode.GetChildrenBestFS(closed, destPoint);
		open.pop();
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}

std::vector<Point> BestFS2(Map* map, MapPos& start, MapPos& dest) {
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<EvalNode, std::vector<EvalNode>, EvalNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	EvalNode startEvalNode(startNode, Euclidean(startNode.pos, destPoint));
	closed.insert(startNode);
	std::vector<EvalNode> children = startEvalNode.GetChildrenBestFS2(closed, destPoint);
	for (auto& it : children) {
		open.push(it);
	}

	while (!open.empty()) {
		EvalNode currentNode = open.top();
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
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
			std::println("Best First Search  2 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<EvalNode> allChildren = currentNode.GetChildrenBestFS2(closed, destPoint);
		open.pop();
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}

std::vector<Point> BestFS3(Map* map, MapPos& start, MapPos& dest) {
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<EvalNode, std::vector<EvalNode>, EvalNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	EvalNode startEvalNode(startNode, FastEuclidean(startNode.pos, destPoint));
	closed.insert(startNode);
	std::vector<EvalNode> children = startEvalNode.GetChildrenBestFS3(closed, destPoint);
	for (auto& it : children) {
		open.push(it);
	}

	while (!open.empty()) {
		EvalNode currentNode = open.top();
		if (currentNode.node.pos.x == dest.absTileRows && currentNode.node.pos.y == dest.absTileColumn) {
			std::vector<Point> path;
			Node lastNode = currentNode.node;
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
			std::println("Best First Search 3 Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<EvalNode> allChildren = currentNode.GetChildrenBestFS3(closed, destPoint);
		open.pop();
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}