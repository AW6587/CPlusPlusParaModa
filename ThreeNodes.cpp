#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"
#include "UndirectedGraph.h"
#include "QueryGraph.h"

#include "ThreeNodes.h"

QueryGraph ToQueryGraph3(vector<Edge<int> > edges, string graphLabel)
{
	QueryGraph g(graphLabel);

	g.AddVerticesAndEdgeRange(edges);
	return g;
}

namespace ThreeNodes
{
	ExpansionTreeNode BuildThreeNodesTree(AdjacencyGraph<ExpansionTreeNode> &expansionTree)
	{

		//Level 0 - Root Node
		ExpansionTreeNode* rootNode = new ExpansionTreeNode;
		rootNode->Level = 0;
		rootNode->IsRootNode = true;

		//Level 1
		vector<Edge<int> > qGraphL1_1Vect;
		qGraphL1_1Vect.push_back(Edge<int>(1,2));
		qGraphL1_1Vect.push_back(Edge<int>(2,3));
		QueryGraph qGraphL1_1 = ToQueryGraph3(qGraphL1_1Vect, "qGraphL1_1");
		ExpansionTreeNode* nodeL1_1 = new ExpansionTreeNode;
		nodeL1_1->Level = 1;
		nodeL1_1->QueryGraph = qGraphL1_1;
		nodeL1_1->NodeName = "qGraphL1_1";
        nodeL1_1->ParentNode = rootNode;
        nodeL1_1->IsRootNode = false;
        

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(*rootNode, *nodeL1_1));

		//Level 2
		vector<Edge<int> > qGraphL2_1Vect;
		qGraphL2_1Vect.push_back(Edge<int>(1,2));
		qGraphL2_1Vect.push_back(Edge<int>(2,3));
		qGraphL2_1Vect.push_back(Edge<int>(1,3));

		QueryGraph qGraphL2_1 = ToQueryGraph3(qGraphL2_1Vect, "qGraphL2_1");

		ExpansionTreeNode* nodeL2_1 = new ExpansionTreeNode;
		nodeL2_1->Level = 2;
		nodeL2_1->QueryGraph = qGraphL2_1;
		nodeL2_1->NodeName = "qGraphL2_1";
		nodeL2_1->ParentNode = nodeL1_1;
        nodeL2_1->IsRootNode = false;

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(*nodeL1_1, *nodeL2_1));

		return *rootNode;
	}
}
