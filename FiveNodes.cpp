#include "AdjacencyGraph.h"
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"
#include "UndirectedGraph.h"
#include "QueryGraph.h"
#include "FiveNodes.h"

QueryGraph ToQueryGraph5(vector<Edge<int> > edges, string graphLabel)
{
	QueryGraph g(graphLabel);

	g.AddVerticesAndEdgeRange(edges);
	return g;
}

namespace FiveNodes
{
	ExpansionTreeNode BuildFiveNodesTree(AdjacencyGraph<ExpansionTreeNode> &expansionTree)
	{
		//Level 0 - Root Node
            ExpansionTreeNode rootNode;
			rootNode.Level = 0;
			rootNode.IsRootNode = true;

			vector<Edge<int> > qGraphL1_1Vect;
            qGraphL1_1Vect.push_back(Edge<int>(1, 2));
			qGraphL1_1Vect.push_back(Edge<int>(2, 3));
			qGraphL1_1Vect.push_back(Edge<int>(3, 4));
			qGraphL1_1Vect.push_back(Edge<int>(4, 5));

            QueryGraph qGraphL1_1 = ToQueryGraph5(qGraphL1_1Vect, "qGraphL1_1");

            vector<Edge<int> > qGraphL1_2Vect;
			qGraphL1_2Vect.push_back(Edge<int>(1, 2));
			qGraphL1_2Vect.push_back(Edge<int>(2, 3));
			qGraphL1_2Vect.push_back(Edge<int>(2, 4));
			qGraphL1_2Vect.push_back(Edge<int>(2, 5));

            QueryGraph qGraphL1_2 = ToQueryGraph5(qGraphL1_2Vect, "qGraphL1_2");

			vector<Edge<int> > qGraphL1_3Vect;
			qGraphL1_3Vect.push_back(Edge<int>(1, 2));
			qGraphL1_3Vect.push_back(Edge<int>(2, 3));
			qGraphL1_3Vect.push_back(Edge<int>(3, 4));
			qGraphL1_3Vect.push_back(Edge<int>(3, 5));

            QueryGraph qGraphL1_3 = ToQueryGraph5(qGraphL1_3Vect, "qGraphL1_3");

            ExpansionTreeNode nodeL1_1;
            nodeL1_1.Level = 1;
            nodeL1_1.QueryGraph = qGraphL1_1;
			nodeL1_1.NodeName = "qGraphL1_1";

			ExpansionTreeNode nodeL1_2;
            nodeL1_2.Level = 1;
            nodeL1_2.QueryGraph = qGraphL1_2;
			nodeL1_2.NodeName = "qGraphL1_2";

			ExpansionTreeNode nodeL1_3;
            nodeL1_3.Level = 1;
            nodeL1_3.QueryGraph = qGraphL1_3;
			nodeL1_3.NodeName = "qGraphL1_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(rootNode, nodeL1_1));
            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(rootNode, nodeL1_2));
            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(rootNode, nodeL1_3));

            vector<Edge<int> > qGraphL2_3Vect;
			qGraphL2_3Vect.push_back(Edge<int>(1, 2));
			qGraphL2_3Vect.push_back(Edge<int>(2, 3));
			qGraphL2_3Vect.push_back(Edge<int>(3, 4));
			qGraphL2_3Vect.push_back(Edge<int>(3, 5));
			qGraphL2_3Vect.push_back(Edge<int>(4, 5));

		    QueryGraph qGraphL2_3 = ToQueryGraph5(qGraphL2_3Vect, "qGraphL2_3");
            ExpansionTreeNode nodeL2_3;
            nodeL2_3.Level = 2;
            nodeL2_3.QueryGraph = qGraphL2_3;
			nodeL2_3.NodeName = "qGraphL2_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL1_3, nodeL2_3));

            //From L1_2
			vector<Edge<int> > qGraphL2_2Vect;
			qGraphL2_2Vect.push_back(Edge<int>(1, 2));
			qGraphL2_2Vect.push_back(Edge<int>(1, 5));
			qGraphL2_2Vect.push_back(Edge<int>(2, 3));
			qGraphL2_2Vect.push_back(Edge<int>(2, 4));
			qGraphL2_2Vect.push_back(Edge<int>(2, 5));

		    QueryGraph qGraphL2_2 = ToQueryGraph5(qGraphL2_2Vect, "qGraphL2_2");

            ExpansionTreeNode nodeL2_2;
            nodeL2_2.Level = 2;
            nodeL2_2.QueryGraph = qGraphL2_2;
			nodeL2_2.NodeName = "qGraphL2_2";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL1_2, nodeL2_2));

            //From L1_1
            vector<Edge<int> > qGraphL2_1aVect;
			qGraphL2_1aVect.push_back(Edge<int>(1,2));
			qGraphL2_1aVect.push_back(Edge<int>(2,3));
			qGraphL2_1aVect.push_back(Edge<int>(3,4));
			qGraphL2_1aVect.push_back(Edge<int>(4,5));
			qGraphL2_1aVect.push_back(Edge<int>(5,1));

			QueryGraph qGraphL2_1a = ToQueryGraph5(qGraphL2_1aVect, "qGraphL2_1a");

	        ExpansionTreeNode nodeL2_1a;
            nodeL2_1a.Level = 2;
            nodeL2_1a.QueryGraph = qGraphL2_1a;
			nodeL2_1a.NodeName = "qGraphL2_1a";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL1_1, nodeL2_1a));

			vector<Edge<int> > qGraphL2_1bVect;
			qGraphL2_1bVect.push_back(Edge<int>(1,2));
			qGraphL2_1bVect.push_back(Edge<int>(2,3));
			qGraphL2_1bVect.push_back(Edge<int>(2,4));
			qGraphL2_1bVect.push_back(Edge<int>(3,4));
			qGraphL2_1bVect.push_back(Edge<int>(4,5));

			QueryGraph qGraphL2_1b = ToQueryGraph5(qGraphL2_1bVect, "qGraphL2_1b");

			ExpansionTreeNode nodeL2_1b;
			nodeL2_1b.Level = 2;
			nodeL2_1b.QueryGraph = qGraphL2_1b;
			nodeL2_1b.NodeName = "qGraphL2_1b";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL1_1, nodeL2_1b));


			vector<Edge<int> > qGraphL2_1cVect;
			qGraphL2_1cVect.push_back(Edge<int>(1,2));
			qGraphL2_1cVect.push_back(Edge<int>(2,3));
			qGraphL2_1cVect.push_back(Edge<int>(2,5));
			qGraphL2_1cVect.push_back(Edge<int>(3,4));
			qGraphL2_1cVect.push_back(Edge<int>(4,5));

            QueryGraph qGraphL2_1c = ToQueryGraph5(qGraphL2_1cVect, "qGraphL2_1c");

            ExpansionTreeNode nodeL2_1c;
            nodeL2_1c.Level = 2;
            nodeL2_1c.QueryGraph = qGraphL2_1c;
			nodeL2_1c.NodeName = "qGraphL2_1c";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL1_1, nodeL2_1c));

            //From L2_1a
			vector<Edge<int> > qGraphL3_1Vect;
			qGraphL3_1Vect.push_back(Edge<int>(1,2));
			qGraphL3_1Vect.push_back(Edge<int>(2,3));
			qGraphL3_1Vect.push_back(Edge<int>(3,4));
			qGraphL3_1Vect.push_back(Edge<int>(4,5));
			qGraphL3_1Vect.push_back(Edge<int>(5,1));
			qGraphL3_1Vect.push_back(Edge<int>(5,2));

            QueryGraph qGraphL3_1 = ToQueryGraph5(qGraphL3_1Vect, "qGraphL3_1");
            ExpansionTreeNode nodeL3_1;
            nodeL3_1.Level = 3;
            nodeL3_1.QueryGraph = qGraphL3_1;
			nodeL3_1.NodeName = "qGraphL3_1";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL2_1a, nodeL3_1));

            //From L2_2
			vector<Edge<int> > qGraphL3_2Vect;
			qGraphL3_2Vect.push_back(Edge<int>(1,2));
			qGraphL3_2Vect.push_back(Edge<int>(1,5));
			qGraphL3_2Vect.push_back(Edge<int>(2,3));
			qGraphL3_2Vect.push_back(Edge<int>(2,4));
			qGraphL3_2Vect.push_back(Edge<int>(2,5));
			qGraphL3_2Vect.push_back(Edge<int>(3,4));

            QueryGraph qGraphL3_2 = ToQueryGraph5(qGraphL3_2Vect, "qGraphL3_2");

            ExpansionTreeNode nodeL3_2;
            nodeL3_2.Level = 3;
            nodeL3_2.QueryGraph = qGraphL3_2;
			nodeL3_2.NodeName = "qGraphL3_2";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL2_2, nodeL3_2));

            //From L2_3
			vector<Edge<int> > qGraphL3_3Vect;
			qGraphL3_3Vect.push_back(Edge<int>(1,2));
			qGraphL3_3Vect.push_back(Edge<int>(2,3));
			qGraphL3_3Vect.push_back(Edge<int>(2,4));
			qGraphL3_3Vect.push_back(Edge<int>(3,4));
			qGraphL3_3Vect.push_back(Edge<int>(3,5));
			qGraphL3_3Vect.push_back(Edge<int>(4,5));

			QueryGraph qGraphL3_3 = ToQueryGraph5(qGraphL3_3Vect, "qGraphL3_3");

            ExpansionTreeNode nodeL3_3;
            nodeL3_3.Level = 3;
            nodeL3_3.QueryGraph = qGraphL3_3;
			nodeL3_3.NodeName = "qGraphL3_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL2_3, nodeL3_3));

            //From L3_1
			vector<Edge<int> > qGraphL4_1Vect;
			qGraphL4_1Vect.push_back(Edge<int>(1, 2));
			qGraphL4_1Vect.push_back(Edge<int>(2, 3));
			qGraphL4_1Vect.push_back(Edge<int>(2, 4));
			qGraphL4_1Vect.push_back(Edge<int>(3, 4));
			qGraphL4_1Vect.push_back(Edge<int>(4, 5));
			qGraphL4_1Vect.push_back(Edge<int>(5, 1));
			qGraphL4_1Vect.push_back(Edge<int>(5, 2));

			QueryGraph qGraphL4_1 = ToQueryGraph5(qGraphL4_1Vect, "qGraphL4_1");

            ExpansionTreeNode nodeL4_1;
            nodeL4_1.Level = 4,
            nodeL4_1.QueryGraph = qGraphL4_1,
			nodeL4_1.NodeName = "qGraphL4_1";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL3_1, nodeL4_1));

            //From L3_2
			vector<Edge<int> > qGraphL4_2Vect;
			qGraphL4_2Vect.push_back(Edge<int>(1, 2));
			qGraphL4_2Vect.push_back(Edge<int>(1, 5));
			qGraphL4_2Vect.push_back(Edge<int>(2, 3));
			qGraphL4_2Vect.push_back(Edge<int>(2, 4));
			qGraphL4_2Vect.push_back(Edge<int>(2, 5));
			qGraphL4_2Vect.push_back(Edge<int>(3, 4));
			qGraphL4_2Vect.push_back(Edge<int>(4, 5));

			QueryGraph qGraphL4_2 = ToQueryGraph5(qGraphL4_2Vect, "qGraphL4_2");

			ExpansionTreeNode nodeL4_2;
            nodeL4_2.Level = 4;
            nodeL4_2.QueryGraph = qGraphL4_2;
			nodeL4_2.NodeName = "qGraphL4_2";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL3_2, nodeL4_2));

            //From L3_3
			vector<Edge<int> > qGraphL4_3Vect;
			qGraphL4_3Vect.push_back(Edge<int>(1, 2));
			qGraphL4_3Vect.push_back(Edge<int>(1, 5));
			qGraphL4_3Vect.push_back(Edge<int>(2, 3));
			qGraphL4_3Vect.push_back(Edge<int>(2, 4));
			qGraphL4_3Vect.push_back(Edge<int>(3, 4));
			qGraphL4_3Vect.push_back(Edge<int>(3, 5));
			qGraphL4_3Vect.push_back(Edge<int>(4, 5));

			QueryGraph qGraphL4_3 = ToQueryGraph5(qGraphL4_3Vect, "qGraphL4_3");

			ExpansionTreeNode nodeL4_3;
            nodeL4_3.Level = 4;
            nodeL4_3.QueryGraph = qGraphL4_3;
			nodeL4_3.NodeName = "qGraphL4_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL3_3, nodeL4_3));

            //From L4_1
			vector<Edge<int> > qGraphL5_1Vect;
			qGraphL5_1Vect.push_back(Edge<int>(1, 2));
			qGraphL5_1Vect.push_back(Edge<int>(2, 3));
			qGraphL5_1Vect.push_back(Edge<int>(2, 4));
			qGraphL5_1Vect.push_back(Edge<int>(3, 4));
			qGraphL5_1Vect.push_back(Edge<int>(3, 5));
			qGraphL5_1Vect.push_back(Edge<int>(4, 5));
			qGraphL5_1Vect.push_back(Edge<int>(5, 1));
			qGraphL5_1Vect.push_back(Edge<int>(5, 2));

			QueryGraph qGraphL5_1 = ToQueryGraph5(qGraphL5_1Vect, "qGraphL5_1");

            ExpansionTreeNode nodeL5_1;
            nodeL5_1.Level = 5;
            nodeL5_1.QueryGraph = qGraphL5_1;
			nodeL5_1.NodeName = "qGraphL5_1";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL4_1, nodeL5_1));

            //From L4_2
			vector<Edge<int> > qGraphL5_2Vect;
			qGraphL5_2Vect.push_back(Edge<int>(1, 2));
			qGraphL5_2Vect.push_back(Edge<int>(1, 3));
			qGraphL5_2Vect.push_back(Edge<int>(1, 5));
			qGraphL5_2Vect.push_back(Edge<int>(2, 3));
			qGraphL5_2Vect.push_back(Edge<int>(2, 4));
			qGraphL5_2Vect.push_back(Edge<int>(2, 5));
			qGraphL5_2Vect.push_back(Edge<int>(3, 4));
			qGraphL5_2Vect.push_back(Edge<int>(4, 5));

			QueryGraph qGraphL5_2 = ToQueryGraph5(qGraphL5_2Vect, "qGraphL5_2");

			ExpansionTreeNode nodeL5_2;
            nodeL5_2.Level = 5;
            nodeL5_2.QueryGraph = qGraphL5_2;
			nodeL5_2.NodeName = "qGraphL5_2";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL4_2, nodeL5_2));

            //From L4_3
			vector<Edge<int> > qGraphL5_3Vect;
			qGraphL5_3Vect.push_back(Edge<int>(1, 2));
			qGraphL5_3Vect.push_back(Edge<int>(1, 5));
			qGraphL5_3Vect.push_back(Edge<int>(2, 3));
			qGraphL5_3Vect.push_back(Edge<int>(2, 4));
			qGraphL5_3Vect.push_back(Edge<int>(2, 5));
			qGraphL5_3Vect.push_back(Edge<int>(3, 4));
			qGraphL5_3Vect.push_back(Edge<int>(3, 5));
			qGraphL5_3Vect.push_back(Edge<int>(4, 5));

			QueryGraph qGraphL5_3 = ToQueryGraph5(qGraphL5_3Vect, "qGraphL5_3");

			ExpansionTreeNode nodeL5_3;
            nodeL5_3.Level = 5;
            nodeL5_3.QueryGraph = qGraphL5_3;
			nodeL5_3.NodeName = "qGraphL5_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL4_3, nodeL5_3));

            //From L5_1
			vector<Edge<int> > qGraphL6_1Vect;
			qGraphL6_1Vect.push_back(Edge<int>(1,2));
			qGraphL6_1Vect.push_back(Edge<int>(1,3));
			qGraphL6_1Vect.push_back(Edge<int>(2,3));
			qGraphL6_1Vect.push_back(Edge<int>(2,4));
			qGraphL6_1Vect.push_back(Edge<int>(3,4));
			qGraphL6_1Vect.push_back(Edge<int>(3,5));
			qGraphL6_1Vect.push_back(Edge<int>(4,5));
			qGraphL6_1Vect.push_back(Edge<int>(5,1));
			qGraphL6_1Vect.push_back(Edge<int>(5,2));

            QueryGraph qGraphL6_1 = ToQueryGraph5(qGraphL6_1Vect, "qGraphL6_1");
            ExpansionTreeNode nodeL6_1;
            nodeL6_1.Level = 6;
            nodeL6_1.QueryGraph = qGraphL6_1;
			nodeL6_1.NodeName = "qGraphL6_1";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL5_1, nodeL6_1));

            //From L5_2
			vector<Edge<int> > qGraphL6_2Vect;
			qGraphL6_2Vect.push_back(Edge<int>(1,2));
			qGraphL6_2Vect.push_back(Edge<int>(1,3));
			qGraphL6_2Vect.push_back(Edge<int>(1,4));
			qGraphL6_2Vect.push_back(Edge<int>(1,5));
			qGraphL6_2Vect.push_back(Edge<int>(2,3));
			qGraphL6_2Vect.push_back(Edge<int>(2,4));
			qGraphL6_2Vect.push_back(Edge<int>(2,5));
			qGraphL6_2Vect.push_back(Edge<int>(3,4));
			qGraphL6_2Vect.push_back(Edge<int>(4,5));

			QueryGraph qGraphL6_2 = ToQueryGraph5(qGraphL6_2Vect, "qGraphL6_2");

			ExpansionTreeNode nodeL6_2;
            nodeL6_2.Level = 6;
            nodeL6_2.QueryGraph = qGraphL6_2;
			nodeL6_2.NodeName = "qGraphL6_2";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL5_2, nodeL6_2));

            //From L5_3
			vector<Edge<int> > qGraphL6_3Vect;
			qGraphL6_3Vect.push_back(Edge<int>(1,2));
			qGraphL6_3Vect.push_back(Edge<int>(1,4));
			qGraphL6_3Vect.push_back(Edge<int>(1,5));
			qGraphL6_3Vect.push_back(Edge<int>(2,3));
			qGraphL6_3Vect.push_back(Edge<int>(2,4));
			qGraphL6_3Vect.push_back(Edge<int>(2,5));
			qGraphL6_3Vect.push_back(Edge<int>(3,4));
			qGraphL6_3Vect.push_back(Edge<int>(3,5));
			qGraphL6_3Vect.push_back(Edge<int>(4,5));

			QueryGraph qGraphL6_3 = ToQueryGraph5(qGraphL6_3Vect, "qGraphL6_3");

            ExpansionTreeNode nodeL6_3;
            nodeL6_3.Level = 6;
            nodeL6_3.QueryGraph = qGraphL6_3;
			nodeL6_3.NodeName = "qGraphL6_3";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL5_3, nodeL6_3));

            //From L6_2
			vector<Edge<int> > qGraphL7_1Vect;
			qGraphL7_1Vect.push_back(Edge<int>(1,2));
			qGraphL7_1Vect.push_back(Edge<int>(1,3));
			qGraphL7_1Vect.push_back(Edge<int>(1,4));
			qGraphL7_1Vect.push_back(Edge<int>(1,5));
			qGraphL7_1Vect.push_back(Edge<int>(2,3));
			qGraphL7_1Vect.push_back(Edge<int>(2,4));
			qGraphL7_1Vect.push_back(Edge<int>(2,5));
			qGraphL7_1Vect.push_back(Edge<int>(3,4));
			qGraphL7_1Vect.push_back(Edge<int>(3,5));
			qGraphL7_1Vect.push_back(Edge<int>(4,5));

            QueryGraph qGraphL7_1 = ToQueryGraph5(qGraphL7_1Vect, "qGraphL7_1");
            ExpansionTreeNode nodeL7_1;
            nodeL7_1.Level = 7;
            nodeL7_1.QueryGraph = qGraphL7_1;
			nodeL7_1.NodeName = "qGraphL7_1";

            expansionTree.AddVerticesAndEdge(Edge<ExpansionTreeNode>(nodeL6_2, nodeL7_1));

            return rootNode;

	}
}
