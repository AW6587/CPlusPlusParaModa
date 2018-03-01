#define TEST_UNDIRECTED_GRAPH
#ifdef TEST_UNDIRECTED_GRAPH

#include <iostream>
#include <map>
#include <vector>
#include "edge.h"
#include "UndirectedGraph.h"
using namespace std;
int main()
{
	Edge<int> edgeA(1, 2);
	UndirectedGraph<int> a;
	
	cout << "initial vertex count:" << endl;
	cout << a.VertexCount() << endl;
	a.AddVerticesAndEdge(edgeA);
	
	cout << "vertex count after adding 1,2:" << endl;
	cout << a.VertexCount() << endl;
	Edge<int> edgeB(1, 3);
	a.AddVerticesAndEdge(edgeB);
	
	cout << "added 1,3" << endl;
	
	cout << "vertex count after adding 1,3:" << endl;
	cout << a.VertexCount() << endl;
	a.AddVerticesAndEdge(3,4);
	cout << "vertex count after adding 3,4:" << endl;
	cout << a.VertexCount() << endl;
	
	vector<int> vertices = a.Vertices();
	cout << "list of all vertices:" << endl;
	for(int i= 0; i < vertices.size(); i++)
	{
		cout << vertices[i] << " ";
	}
	cout << endl;
	
	cout << "number of edges:" << endl;
	cout << a.EdgeCount() << endl;
	
	vector<Edge<int> > edges = a.Edges();
	cout << "List of all edges: " << endl;
	for (int i = 0; i < edges.size(); i++)
	{
		cout << edges[i].ToString() << " ";
	}
	cout << endl;
	
	cout << "neighbors of 1" << endl;
	vector<int> neighbors = a.GetNeighbors(1);
	
	for (int i = 0; i < neighbors.size(); i++)
	{
		cout << neighbors[i] << " ";
	}
	cout << endl;
	
	UndirectedGraph<int> b;
	
	b.AddVerticesAndEdge(2, 5);
	b.AddVerticesAndEdge(1, 2);
	b.AddVerticesAndEdge(1, 3);
	b.AddVerticesAndEdge(1, 6);
	
	cout << "nodes sorted by degree: " << endl;
	vector<int> nodes = b.GetNodesSortedByDegree(4);
	for(int i = 0; i < nodes.size(); i++)
	{
		cout << nodes[i] << " ";
	}
	cout << endl;
	
	cout << "degree sequence:" << endl;
	vector<int> degreeSequence = b.GetReverseDegreeSequence();
	for(auto &i : degreeSequence)
	{
		cout << i << " ";
	}
	cout << endl;
	
	cout << "cloning b:" << endl;
	UndirectedGraph<int> c = b.Clone();
	cout << "b:" << endl;
	cout << b.ToString() << endl;
	cout << "c:" << endl;
	cout << c.ToString() << endl;
	
	cout << "deleting the vertex \"1\":" << endl;
	c.RemoveVertex(1);
	cout << c.ToString() << endl;
	
	cout << "clearing c:" << endl;
	c.Clear();
	cout << c.ToString() << endl;
	cout << "done" << endl;
	
	cout << "getting edge 1, 2 from b: " << endl;
	Edge<int> test;
	if(b.TryGetEdge(1, 2, &test))
	{
		cout << test.ToString() << endl;
	}
	
	cout << "getting edge 41, 2 from b: " << endl;
	if(b.TryGetEdge(41, 2, &test))
	{
		cout << test.ToString() << endl;
	}
	else
	{
		cout << "it doesn't exist" << endl;
	}

	cout << "does b contain 1,2?:" << endl;
	b.ContainsEdge(1,2) ? cout << "yes" << endl : cout << "no" << endl;
	cout << "does it contain 41,2?:" << endl;
	b.ContainsEdge(41,2) ? cout << "yes" << endl : cout << "no" << endl;
	
	cout << "B before adding more:" << endl;
	cout << b.ToString() << endl;
	vector<Edge<int> > edgeList;
	edgeList.push_back(Edge<int>(1, 7));
	edgeList.push_back(Edge<int>(61, 1));
	b.AddVerticesAndEdgeRange(edgeList);
	cout << "B after:" << endl;
	cout << b.ToString() << endl;
    cout << "test read file:" << endl;
    UndirectedGraph<int> e;
    e.readFile("/Users/huangxiao/Desktop/483/ParaMODA-master/ParaMODA/SampleInputGraph.txt");
    cout << e.ToString() << endl;
    

    
}
#endif
