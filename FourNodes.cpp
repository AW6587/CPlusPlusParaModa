#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include "FourNodes.h"

QueryGraph ToQueryGraph4(vector<Edge<int> > edges, string graphLabel)
{
	QueryGraph g(graphLabel);

	g.AddVerticesAndEdgeRange(edges);
	return g;
}

// bool AddVerticesAndEdgeRange(vector<Edge<int> > edges);


namespace FourNodes
{
	ExpansionTreeNode* BuildFourNodesTree(AdjacencyGraph<ExpansionTreeNode*> expansionTree)
	{
		//Level 0 - Root Node
		ExpansionTreeNode* rootNode = new ExpansionTreeNode;
		rootNode->Level = 0;
		rootNode->IsRootNode = true;

		vector<Edge<int> > qGraphL1_1Vect;
		    qGraphL1_1Vect.push_back(Edge<int>(1,2));
		    qGraphL1_1Vect.push_back(Edge<int>(2,3));
		    qGraphL1_1Vect.push_back(Edge<int>(3,4));
		QueryGraph qGraphL1_1 = ToQueryGraph4(qGraphL1_1Vect, "qGraphL1_1");


		vector<Edge<int> > qGraphL1_2Vect;
		    qGraphL1_1Vect.push_back(Edge<int>(1,2));
		    qGraphL1_1Vect.push_back(Edge<int>(2,3));
		    qGraphL1_1Vect.push_back(Edge<int>(2,4));
		QueryGraph qGraphL1_2 = ToQueryGraph4(qGraphL1_2Vect, "qGraphL1_2");

		ExpansionTreeNode* nodeL1_1 = new ExpansionTreeNode;
	    nodeL1_1->Level = 1;
	    nodeL1_1->QueryGraph = qGraphL1_1;
		nodeL1_1->NodeName = "qGraphL1_1";

		ExpansionTreeNode* nodeL1_2 = new ExpansionTreeNode;
		nodeL1_2->Level = 1;
	    nodeL1_2->QueryGraph = qGraphL1_2;
		nodeL1_2->NodeName = "qGraphL1_2";

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(rootNode, nodeL1_1));
		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(rootNode, nodeL1_2));

		vector<Edge<int> > qGraphL2_1vect;
		qGraphL2_1vect.push_back(Edge<int>(1, 2));
		qGraphL2_1vect.push_back(Edge<int>(2, 3));
		qGraphL2_1vect.push_back(Edge<int>(2, 4));
		qGraphL2_1vect.push_back(Edge<int>(3, 4));

		QueryGraph qGraphL2_1 = ToQueryGraph4(qGraphL2_1vect, "qGraphL2_1");

		vector<Edge<int> > qGraphL2_2vect;
		qGraphL2_2vect.push_back(Edge<int>(1, 2));
		qGraphL2_2vect.push_back(Edge<int>(1, 4));
		qGraphL2_2vect.push_back(Edge<int>(2, 3));
		qGraphL2_2vect.push_back(Edge<int>(3, 4));

		QueryGraph qGraphL2_2 = ToQueryGraph4(qGraphL2_2vect, "qGraphL2_2");

		ExpansionTreeNode* nodeL2_1 = new ExpansionTreeNode;
		nodeL2_1->Level = 2;
		nodeL2_1->QueryGraph = qGraphL2_1;
		nodeL2_1->NodeName = "qGraphL2_1";

		ExpansionTreeNode* nodeL2_2 = new ExpansionTreeNode;
		nodeL2_2->Level = 2;
		nodeL2_2->QueryGraph = qGraphL2_2;
		nodeL2_2->NodeName = "qGraphL2_2";

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(nodeL1_1, nodeL2_1));
		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(nodeL1_1, nodeL2_2));

		vector<Edge<int> > qGraphL3_1Vect;
		qGraphL3_1Vect.push_back(Edge<int>(1, 2));
		qGraphL3_1Vect.push_back(Edge<int>(1, 3));
		qGraphL3_1Vect.push_back(Edge<int>(2, 3));
		qGraphL3_1Vect.push_back(Edge<int>(2, 4));
		qGraphL3_1Vect.push_back(Edge<int>(3, 4));

		QueryGraph qGraphL3_1 = ToQueryGraph4(qGraphL3_1Vect, "qGraphL3_1");

		ExpansionTreeNode* nodeL3_1 = new ExpansionTreeNode;
		nodeL3_1->Level = 3;
		nodeL3_1->QueryGraph = qGraphL3_1;
		nodeL3_1->NodeName = "qGraphL3_1";

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(nodeL2_1, nodeL3_1));

		vector<Edge<int > > qGraphL4_1Vect;
		qGraphL4_1Vect.push_back(Edge<int>(1, 2));
		qGraphL4_1Vect.push_back(Edge<int>(1, 3));
		qGraphL4_1Vect.push_back(Edge<int>(1, 4));
		qGraphL4_1Vect.push_back(Edge<int>(2, 3));
		qGraphL4_1Vect.push_back(Edge<int>(2, 4));
		qGraphL4_1Vect.push_back(Edge<int>(3, 4));

		QueryGraph qGraphL4_1 = ToQueryGraph4(qGraphL4_1Vect, "qGraphL4_1");

		ExpansionTreeNode* nodeL4_1 = new ExpansionTreeNode;
		nodeL4_1->Level = 4;
		nodeL4_1->QueryGraph = qGraphL4_1;
		nodeL4_1->NodeName = "qGraphL4_1";

		expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode*>(nodeL3_1, nodeL4_1));

		return rootNode;
	}
}
