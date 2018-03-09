#pragma once
#include <iostream>
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

using namespace std;

template<class TVertex>
class ExpansionTreeBuilder
{
	private:
		int _numberOfNodes;
	public:
		int NumberOfQueryGraphs;
        queue<ExpansionTreeNode> VerticesSorted;
        AdjacencyGraph<ExpansionTreeNode> ExpansionTree;
		
		ExpansionTreeBuilder(int numberOfNodes);
		void Build();
};

#include "ExpansionTreeBuilder.cpp.h"
