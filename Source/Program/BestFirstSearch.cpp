#include "BestFirstSearch.h"
#include <print>
#include <queue>


#include "Map.h"


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

std::vector<Point> BestFSAdv(Map* map, MapPos& start, MapPos& dest, std::vector<Point> &globalClosed) {
	globalClosed.clear();
	std::unordered_set<Node, NodeHash, NodeEq> closed = {};

	std::priority_queue<EvalNode, std::vector<EvalNode>, EvalNodeComp> open = {};
	Node startNode(Point{ start.absTileRows, start.absTileColumn }, Point{ -1,-1 });
	Point destPoint{ dest.absTileRows,dest.absTileColumn };
	EvalNode startEvalNode(startNode, FastEuclidean(startNode.pos, destPoint));
	closed.insert(startNode);
	std::vector<EvalNode> children = startEvalNode.GetChildrenBestFS4(map,closed, destPoint);
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
			for (auto& it : closed) {
				globalClosed.emplace_back(it.pos);
			}
			std::println("Best First Search Adv Succeded");
			std::println("Open: {}", open.size());
			std::println("Closed: {}", closed.size());
			return path;
		}

		std::vector<EvalNode> allChildren = currentNode.GetChildrenBestFS4(map,closed, destPoint);
		open.pop();
		for (auto& it : allChildren) {
			open.push(it);
		}
	}
	return {};
}