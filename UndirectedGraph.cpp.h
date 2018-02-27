#include <map>
#include <iostream>
#include <vector>
#include "edge.h"
#include "UndirectedGraph.h"

using namespace std;

template <class T>
bool contains(vector<T> vect, T a)
{
	for(int i = 0; i < vect.size(); i++)
	{
		if(vect.at(i) == a)
		{
			return true;
		}
	}
	return false;
}

template <class TVertex>
UndirectedGraph<TVertex>::UndirectedGraph()
{
	allowParallelEdges = true;
	edgeCount = 0;
}

template <class TVertex>
UndirectedGraph<TVertex>::UndirectedGraph(bool allowParallelEdges)
{
	allowParallelEdges = true;
	edgeCount = 0;
	allowParallelEdges = allowParallelEdges;
}

template <class TVertex>
int UndirectedGraph<TVertex>::VertexCount()
{
	return edges.size();
}

template <class TVertex>
vector<TVertex> UndirectedGraph<TVertex>::Vertices()
{
	vector<TVertex> keys;
	vector<int>::iterator it;
	it = keys.begin();
	for(auto &kv : edges) 
	{
		it = keys.begin();
    	keys.insert(it, kv.first);
 	} 
	return keys;
}

template <class TVertex>
int UndirectedGraph<TVertex>::EdgeCount()
{
	return edgeCount;
}

template <class TVertex>
vector<Edge<TVertex> > UndirectedGraph<TVertex>::Edges()
{
	vector<Edge<TVertex> > _edges;
	for(auto &vertsSet : edges) 
	{
		if(vertsSet.second != NULL)
		{
			for(int i = 0; i < vertsSet.second->size(); i++)
			{
				Edge<TVertex> edge(vertsSet.first, vertsSet.second->at(i));
				if(!contains(_edges, edge))
				{
					_edges.push_back(edge);
				}
			}
		}
	}
	return _edges;
}

template <class TVertex>
std::vector<TVertex> UndirectedGraph<TVertex>::GetNeighbors(TVertex vertex)
{
	vector<TVertex> retVal;
	typename std::map<TVertex, std::vector<TVertex>*>::const_iterator got = edges.find(vertex);
	if (got != edges.end())
	{
		retVal = *edges[vertex];
	}
	return retVal;
}

template <class TVertex>
std::vector<TVertex> UndirectedGraph<TVertex>::GetNodesSortedByDegree(int count)
{
	map<TVertex, int> tempList;
	vector<TVertex> vertices = Vertices();
	
	for(int i = vertices.size() - 1; i >= 0; i-- )
	{
		tempList[vertices[i]] = GetDegree(vertices[i]);
	}
	
	std::vector<std::pair<TVertex, int>> pairs;
	for (auto itr = tempList.begin(); itr != tempList.end(); ++itr)
	{
	    pairs.push_back(*itr);
	}
	
	sort(pairs.begin(), pairs.end(), [=](std::pair<TVertex, int>& a, std::pair<TVertex, int>& b)
	{
	    return a.second > b.second;
	}
	);
	
	vector<TVertex> listToReturn;
	for(int i = 0; i < count; i++ )
	{
		listToReturn.push_back(pairs[i].first);
	}
	return listToReturn;
}

template <class TVertex>
vector<int> UndirectedGraph<TVertex>::GetReverseDegreeSequence()
{
	vector<TVertex> vertices = Vertices();
	vector<int> tempList;
	for(int i = 0; i < vertices.size(); i++)
	{
		tempList.push_back(GetDegree(vertices[i]));
	}
	sort(tempList.begin(), tempList.end());
	return tempList;
}

template <class TVertex>
UndirectedGraph<TVertex> UndirectedGraph<TVertex>::Clone()
{
	UndirectedGraph<TVertex> clone(allowParallelEdges);
	clone.edgeCount = edgeCount;

	for (auto itr = edges.begin(); itr != edges.end(); ++itr)
	{
		clone.edges[itr->first] = itr->second;
	}

	return clone;
}

template <class TVertex>
string UndirectedGraph<TVertex>::ToString()
{
	if(edgeCount == 0) return "";
	string retVal = "Graph-Edges_";
	for(auto & iter : Edges())
	{
		retVal += "[" + iter.ToString() + "],";
	}
	return retVal;
}

template <class TVertex>
bool UndirectedGraph<TVertex>::RemoveVertex(TVertex v)
{
	ClearAdjacentEdges(v);
	auto it = edges.find(v);
	if(it == edges.end())
	{
		return false;
	}
	edges.erase(it);
	return true;
}


template <class TVertex>
void UndirectedGraph<TVertex>::Clear()
{
	edgeCount = 0;
	edges.clear();
}

template <class TVertex>
void UndirectedGraph<TVertex>::ClearAdjacentEdges(TVertex v)
{
	vector<TVertex> ends = *edges[v];
	edgeCount -= ends.size();
	for(auto & end : ends)
	{
		if(edges[end] != NULL)
		{
			int i = 0;
			for(auto & iter : *edges[end])
			{
				if(iter == v)
				{
					edges[end]->erase(edges[end]->begin() + i);
				}
				i++;
			}
		}
	}
}

template <class TVertex>
bool UndirectedGraph<TVertex>::TryGetEdge(TVertex source, TVertex target, Edge<TVertex> *edge)
{
	if(edges[source] != NULL)
	{
		if(contains(*edges[source], target))
		{
			edge->Source = source;
			edge->Target = target;
			return true;
		}
	}
	return false;
}

template <class TVertex>
bool UndirectedGraph<TVertex>::ContainsEdge(TVertex source, TVertex target)
{
	if(edges[source] != NULL)
	{
		if(contains(*edges[source], target))
		{
			return true;
		}
	}
	return false;
}

template <class TVertex>
bool UndirectedGraph<TVertex>::AddVerticesAndEdge(TVertex source, TVertex target)
{
	typename std::map<TVertex, std::vector<TVertex>*>::const_iterator gotSource = edges.find(source);
	typename std::map<TVertex, std::vector<TVertex>*>::const_iterator gotTarget = edges.find(target);
	
	if(gotSource != edges.end())
	{

		if(edges[source] != NULL)
		{
			if(contains(*edges[source], target))
			{
				return false;
			}
		}
		edges[source]->push_back(target);
			
		if(gotTarget != edges.end())
		{
			if(edges[target] != NULL)
			{
				if(!contains(*edges[target], source))
				{
					edges[target]->push_back(source);
				}
			}
		}
		else
		{
			edges[target] = new vector<TVertex>;
			edges[target]->push_back(source);
		}
	}
	else if(gotTarget != edges.end())
	{
		if(edges[target] != NULL)
		{
			if(contains(*edges[target], source))
			{
				return false;
			}
		}
		
		edges[target]->push_back(source);
		if (gotSource != edges.end())
        {
            if (edges[source] != NULL)
            {
                if(!contains(*edges[source], target))
				{
					edges[source]->push_back(target);
				}
            }
        }
		else
		{
			edges[source] = new vector<TVertex>;
			edges[source]->push_back(target);
		}
	}
	else // neither exists. So, add them
    {
        edges[source] = new vector<TVertex>;
		edges[source]->push_back(target);
        edges[target] = new vector<TVertex>;
		edges[target]->push_back(source);
    }

    edgeCount++;
    return true;
}

template <class TVertex>
bool UndirectedGraph<TVertex>::AddVerticesAndEdge(Edge<TVertex> edge)
{
	return AddVerticesAndEdge(edge.Source, edge.Target);
}

template <class TVertex>
int UndirectedGraph<TVertex>::AddVerticesAndEdgeRange(std::vector<Edge<TVertex> > _edges)
{
	int count = 0;
	for(auto & edge : _edges)
	{
		if (AddVerticesAndEdge(edge.Source, edge.Target))
		{
			count++;
		}
	}
	return count;
}

template <class TVertex>
int UndirectedGraph<TVertex>::GetDegree(TVertex v)
{
	if(edges[v] != NULL)
	{
		return edges[v]->size();
	}
	else 
	{
		return 0;
	}
}

template <class TVertex>
bool UndirectedGraph<TVertex>::AddVerticesAndEdgeStraight(Edge<TVertex> edge)
{
	TVertex source = edge.Source;
	TVertex target = edge.Target;
	
	typename std::map<TVertex, std::vector<TVertex>*>::const_iterator gotSource = edges.find(source);
	typename std::map<TVertex, std::vector<TVertex>*>::const_iterator gotTarget = edges.find(target);
	
	if(gotSource != edges.end())
	{
		if(edges[source] != NULL)
		{
			if(contains(edges[source], target))
			{
				return false;
			}
		}
		
		edges[source]->push_back(target);
		
		if(gotTarget != edges.end())
		{
			edges[target]->push_back(source);
		}
		else
		{
			edges[target] = new vector<TVertex>;
			edges[target]->push_back(source);
		}
	}
	else if(gotTarget != edges.end())
	{
		if(edges[target] != NULL)
		{
			if(contains(edges[target], source))
			{
				return false;
			}
		}
		
		edges[target]->push_back(source);
		
		if(gotSource != edges.end())
		{
			edges[source]->push_back(target);
		}
		else
		{
			edges[source] = new vector<TVertex>;
			edges[source]->push_back(target);
		}
	}
	
	edgeCount++;
	return true;
}
