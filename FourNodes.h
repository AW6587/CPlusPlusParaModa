#pragma once
#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

namespace FourNodes
{
	ExpansionTreeNode BuildFourNodesTree(AdjacencyGraph<ExpansionTreeNode> &expansionTree);
}
