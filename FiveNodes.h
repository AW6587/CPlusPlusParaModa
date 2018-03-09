#pragma once
#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

namespace FiveNodes
{
	ExpansionTreeNode BuildFiveNodesTree(AdjacencyGraph<ExpansionTreeNode> &expansionTree);
}
