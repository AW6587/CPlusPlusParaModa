#pragma once
#include <iostream>
#include "AdjacencyGraph.h"

template <class TVertex>
AdjacencyGraph<TVertex>::AdjacencyGraph()
{
	AdjacencyGraph(true);
}

template <class TVertex>
AdjacencyGraph<TVertex>::AdjacencyGraph(bool _allowParallelEdges)
{
	AdjacencyGraph(_allowParallelEdges,-1);
}

template <class TVertex>
AdjacencyGraph<TVertex>::AdjacencyGraph(bool _allowParallelEdges, int _vertexCapacity)
{
	AdjacencyGraph(_allowParallelEdges, _vertexCapacity, -1);
}

template <class TVertex>
AdjacencyGraph<TVertex>::AdjacencyGraph(bool _allowParallelEdges, int _vertexCapacity, int _edgeCapacity)
{
    allowParallelEdges = _allowParallelEdges;
    // if (vertexCapacity > -1)
	// {
	// 	vertexEdges = new VertexEdgeDictionary<TVertex>(vertexCapacity, vertexComparer);
	// }
    // 	
    // else
	// {
	// 	vertexEdges = new VertexEdgeDictionary<TVertex>(vertexComparer);
	// }
        
    edgeCapacity = _edgeCapacity;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::ContainsVertex(TVertex v)
{
	if(vertexEdges.count(v))
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::IsOutEdgesEmpty(TVertex v)
{
	if(vertexEdges[v] != NULL)
	{
		return vertexEdges[v]->size() == 0;
	}
	else 
	{
		return true;
	}
}

template <class TVertex>
int AdjacencyGraph<TVertex>::OutDegree(TVertex v)
{
	if(vertexEdges[v] != NULL)
	{
		return vertexEdges[v]->size();
	}
	else
	{
		return 0;
	}
}

template <class TVertex>
vector<Edge<TVertex> > AdjacencyGraph<TVertex>::OutEdges(TVertex v)
{
	if(vertexEdges[v] == NULL)
	{
		vertexEdges[v] = new vector<Edge<TVertex> >;
	}
	return *vertexEdges[v];
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::TryGetOutEdges(TVertex v, vector<Edge<TVertex> > & edges)
{
	if(vertexEdges[v] != NULL)
	{
		edges = *vertexEdges[v];
		return true;
	}
	return false;
}

template <class TVertex>
Edge<TVertex> * AdjacencyGraph<TVertex>::OutEdge(TVertex v, int index)
{
	if(vertexEdges[v] != NULL)
	{
		if(vertexEdges[v]->size() > index)
		{
			return &vertexEdges[v]->at(index);
		}
	}
	return nullptr;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::ContainsEdge(TVertex source, TVertex target)
{
	if(vertexEdges[source] == NULL) 
	{
		return false;
	}
	for(auto & outEdge : *vertexEdges[source])
	{
		if(outEdge.Target == target)
		{
			return true;
		}
	}
	return false;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::ContainsEdge(Edge<TVertex> edge)
{
	if(vertexEdges[edge.Source] == NULL) 
	{
		return false;
	}
	for(auto & outEdge : *vertexEdges[edge.Source])
	{
		if(outEdge.Equals(edge))
		{
			return true;
		}
	}
	return false;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::TryGetEdge(
	TVertex source,
	TVertex target,
	Edge<TVertex> & edge)
{
	if(vertexEdges[source] != NULL)
	{
		if(vertexEdges[source]->size() > 0)
		{
			for(auto & e : *vertexEdges[source])
			{
				if(e.Target == target)
				{
					edge = e;
					return true;
				}
			}
		}
	}
	return false;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::TryGetEdges(
	TVertex source,
	TVertex target,
	vector<Edge<TVertex> > & edges)
{
	if(vertexEdges[source] != NULL)
	{
		for(auto & edge : *vertexEdges[source])
		{
			if(edge.Target == target)
			{
				edges.push_back(edge);
			}
		}
		return true;
	}
	return false;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::AddVertex(TVertex v)
{
	if (ContainsVertex(v))
	{
		return false;
	}
	if(edgeCount < edgeCapacity || edgeCapacity < 0)
	{
        cout << "executed" << endl;
		edgeCount++;
		if(vertexEdges[v] == NULL)
		{
			vertexEdges[v] = new vector<Edge<TVertex> >;
		}
	}
	
	return true;
}

template <class TVertex>
int AdjacencyGraph<TVertex>::AddVertexRange(vector<TVertex> vertices)
{
	int count = 0;
	for (auto & v : vertices)
	{
		if (AddVertex(v))
		{
			count++;
		}
	}
	return count;
}

//TODO: this may need more work
template <class TVertex>
bool AdjacencyGraph<TVertex>::RemoveVertex(TVertex v)
{
	if (!ContainsVertex(v))
	{
		return false;
	}
    // remove outedges
    // {
    //     vector<Edge<TVertex> > edges = vertexEdges[v];
    //     if (this.EdgeRemoved != null) // lazily notify
    //     {
    //         foreach (var edge in edges)
    //             this.OnEdgeRemoved(edge);
    //     }
    //     this.edgeCount -= edges.Count;
    //     edges.Clear();
    // }
	
	vector<Edge<TVertex> > edgeToRemove;
	for(auto & kv : vertexEdges)
	{
		// this may be assuming above commented block is being used
		// if(kv.first == v) continue;
		
		if(kv.second != NULL)
		{
			for(auto & edge : *kv.second)
			{
				cout << "here" << endl;
				if (edge.Target == v)
				{
					edgeToRemove.push_back(edge);
				}
			}
		}
		for (auto & edge : edgeToRemove)
		{
			int indexOfEdge;
			for(int i = 0; i < kv.second->size(); i++)
			{
				if(kv.second->at(i) == edge)
				{
					indexOfEdge = i;
				}
			}
			kv.second->erase(kv.second->begin() + indexOfEdge);
			// this.OnEdgeRemoved(edge);
		}
		edgeCount -= edgeToRemove.size();
	}
	vertexEdges.erase(v);
	return true;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::AddVerticesAndEdge(Edge<TVertex> e)
{
	AddVertex(e.Source);
	AddVertex(e.Target);
	return AddEdge(e);
}

template <class TVertex>
int AdjacencyGraph<TVertex>::AddVerticesAndEdgeRange(vector<Edge<TVertex> > edges)
{
	int count = 0;
	for(auto & edge : edges)
	if (AddVerticesAndEdge(edge))
	{
		count++;
	}
	return count;
}

template <class TVertex>
bool AdjacencyGraph<TVertex>::AddEdge(Edge<TVertex> e)
{
	if (!AllowParallelEdges)
    {
        if (ContainsEdge(e.Source, e.Target))
		{
			return false;
		}
	}
	if(vertexEdges[e.Source] == NULL)
	{
		vertexEdges[e.Source] = new vector<Edge<TVertex> >;
	}
	vertexEdges[e.Source]->push_back(e);
	edgeCount++;

	// this.OnEdgeAdded(e);

return true;
}
