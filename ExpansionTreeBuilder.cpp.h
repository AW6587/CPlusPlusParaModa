#include <iostream>
#include <queue>
#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"
#include "AdjacencyGraph.h"
#include "ThreeNodes.h"
#include "FourNodes.h"
#include "FiveNodes.h"

using namespace std;
template<class TVertex>
ExpansionTreeBuilder<TVertex>::ExpansionTreeBuilder(int numberOfNodes)
{
	_numberOfNodes = numberOfNodes;
	NumberOfQueryGraphs = 1;
	ExpansionTree = new AdjacencyGraph<ExpansionTreeNode>;

	// ExpansionTree.EdgeAdded += e => e.Target.ParentNode = e.Source;
}

template<class TVertex>
void ExpansionTreeBuilder<TVertex>::Build()
{
	ExpansionTreeNode rootNode;
	switch (_numberOfNodes)
	{
		case 3:
			rootNode = ThreeNodes::BuildThreeNodesTree(ExpansionTree);
			NumberOfQueryGraphs = 2;
			break;
		case 4:
			rootNode = FourNodes::BuildFourNodesTree(ExpansionTree);
			NumberOfQueryGraphs = 6;
			break;
		case 5:
			rootNode = FiveNodes::BuildFiveNodesTree(ExpansionTree);
			NumberOfQueryGraphs = 21;
			break;
		default:
			cerr << "Subgraph sizes below 3 and above 5 are not supported, unless you supply a query graph." << endl;
	}
}
