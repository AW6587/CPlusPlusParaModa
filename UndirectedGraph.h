#ifndef __UNDIRECTEDGRAPH_H
#define __UNDIRECTEDGRAPH_H

#include <map>
#include "edge.h"
template <class TVertex>
class UndirectedGraph
{
public:
	bool allowParallelEdges;
	std::map<TVertex, std::vector<TVertex>* > edges;
	int edgeCount;
	bool AddVerticesAndEdgeStraight(Edge<TVertex> edge);
	void readFile(string fileName);
	UndirectedGraph();
	UndirectedGraph(bool allowParallelEdges);
	int VertexCount();
	std::vector<TVertex> Vertices();
	int EdgeCount();
	std::vector<Edge<TVertex> > Edges();
	std::vector<TVertex> GetNeighbors(TVertex vertex);
	std::vector<TVertex> GetNodesSortedByDegree(int count);
	std::vector<int> GetReverseDegreeSequence();
	UndirectedGraph<TVertex> Clone();
	std::string ToString();
	bool RemoveVertex(TVertex v);
	void Clear();
	void ClearAdjacentEdges(TVertex v);
	bool TryGetEdge(TVertex source, TVertex target, Edge<TVertex> *edge);
	bool ContainsEdge(TVertex source, TVertex target);
	bool AddVerticesAndEdge(TVertex source, TVertex target);
	bool AddVerticesAndEdge(Edge<TVertex> edge);
	int AddVerticesAndEdgeRange(std::vector<Edge<TVertex> > edges);
	int GetDegree(TVertex v);


};

#include "UndirectedGraph.cpp.h"
#endif
