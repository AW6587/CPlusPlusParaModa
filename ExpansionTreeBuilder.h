#pragma once
#include <iostream>
#include <queue>
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

using namespace std;

template<class TVertex>
class ExpansionTreeBuilder
{
	private:
		int _numberOfNodes;
		vector<ExpansionTreeNode> sortWithBFS(AdjacencyGraph<ExpansionTreeNode> tree, ExpansionTreeNode root);
	public:
		int NumberOfQueryGraphs;
        queue<ExpansionTreeNode> VerticesSorted;
        AdjacencyGraph<ExpansionTreeNode> ExpansionTree;

		ExpansionTreeBuilder(int numberOfNodes);
		void Build();
};

#include "ExpansionTreeBuilder.cpp.h"
