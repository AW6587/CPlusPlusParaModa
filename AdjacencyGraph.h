#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "edge.h"
using namespace std;

template<class TVertex>
class AdjacencyGraph
{
	private:
		bool isDirected = true;
		bool allowParallelEdges;
		map<TVertex, vector<Edge<TVertex> > *> vertexEdges;
		int edgeCount = 0;
		int edgeCapacity = -1;
	public:
		AdjacencyGraph();
        int getEdgeCount(){return edgeCount;};
        AdjacencyGraph(bool allowParallelEdges);

        AdjacencyGraph(bool allowParallelEdges, int vertexCapacity);

        AdjacencyGraph(bool allowParallelEdges, int vertexCapacity, int edgeCapacity);

		/* to be implemented only if needed, might go around it using c++ */
        // public AdjacencyGraph(bool allowParallelEdges, int vertexCapacity, int edgeCapacity, IEqualityComparer<TVertex> vertexComparer);

        // AdjacencyGraph(
        //     bool allowParallelEdges, 
        //     int capacity, 
        //     int edgeCapacity,
        //     Func<int, VertexEdgeDictionary<TVertex> > vertexEdgesDictionaryFactory);
			
		bool IsDirected;

        bool AllowParallelEdges;

        int EdgeCapacity;

        bool IsVerticesEmpty;
		
        int VertexCount;

        vector<TVertex> Vertices;

        
        bool ContainsVertex(TVertex v);

        bool IsOutEdgesEmpty(TVertex v);

        int OutDegree(TVertex v);

        vector<Edge<TVertex> > OutEdges(TVertex v);

        bool TryGetOutEdges(TVertex v, vector<Edge<TVertex> > &edges);

        Edge<TVertex> *OutEdge(TVertex v, int index);

        /// <summary>
        /// Gets a value indicating whether this instance is edges empty.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is edges empty; otherwise, <c>false</c>.
        /// </value>
        bool IsEdgesEmpty;

        /// <summary>
        /// Gets the edge count.
        /// </summary>
        /// <value>The edge count.</value>
        int EdgeCount;

        // [ContractInvariantMethod]
        // void ObjectInvariant()
        // {
        //     Contract.Invariant(this.edgeCount >= 0);
        // }

        /// <summary>
        /// Gets the edges.
        /// </summary>
        /// <value>The edges.</value>
        // virtual vector<Edge<TVertex>> Edges();

        
        bool ContainsEdge(TVertex source, TVertex target);
        
        bool ContainsEdge(Edge<TVertex> edge);

        bool TryGetEdge(
            TVertex source,
            TVertex target,
            Edge<TVertex> & edge);
        
        bool TryGetEdges(
            TVertex source,
            TVertex target,
        	vector<Edge<TVertex> > & edges);

        bool AddVertex(TVertex v);
		
        int AddVertexRange(vector<TVertex> vertices);

        // public event VertexAction<TVertex> VertexAdded;
		
        // void OnVertexAdded(TVertex args);

        bool RemoveVertex(TVertex v);
		
        // public event VertexAction<TVertex> VertexRemoved;
        
		// void OnVertexRemoved(TVertex args);

        // int RemoveVertexIf(VertexPredicate<TVertex> predicate);

        bool AddVerticesAndEdge(Edge<TVertex> e);

        /// <summary>
        /// Adds a range of edges to the graph
        /// </summary>
        /// <param name="edges"></param>
        /// <returns>the count edges that were added</returns>
        int AddVerticesAndEdgeRange(vector<Edge<TVertex> > edges);

        /// <summary>
        /// Adds the edge to the graph
        /// </summary>
        /// <param name="e">the edge to add</param>
        /// <returns>true if the edge was added; false if it was already part of the graph</returns>
        bool AddEdge(Edge<TVertex> e);

        int AddEdgeRange(vector<Edge<TVertex> > edges);

        // public event EdgeAction<TVertex> EdgeAdded;
        // void OnEdgeAdded(Edge<TVertex> args);

        bool RemoveEdge(Edge<TVertex> e);

        // public event EdgeAction<TVertex> EdgeRemoved;
        // protected virtual void OnEdgeRemoved(Edge<TVertex> args);

        // int RemoveEdgeIf(EdgePredicate<TVertex> predicate);

        void ClearOutEdges(TVertex v);
		
        // int RemoveOutEdgeIf(TVertex v, EdgePredicate<TVertex> predicate);

        void TrimEdgeExcess();

        void Clear();

};

#include "AdjacencyGraph.cpp.h"
