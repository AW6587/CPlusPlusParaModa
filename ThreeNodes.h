#pragma once
#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

namespace ThreeNodes
{
	ExpansionTreeNode BuildThreeNodesTree(AdjacencyGraph<ExpansionTreeNode> &expansionTree);
}
