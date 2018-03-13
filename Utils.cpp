//
//  Utils.cpp
//  testt
//
//  Created by Xiao Huang on 3/10/18.
//  Copyright © 2018 Xiao Huang. All rights reserved.
//
#include "Utils.h"

void clearVector(vector<int> vect, int start, int end)
{
	for(int i = 0; i < end && i < vect.size(); i++)
	{
		vect[i] = 0;
	}
}

void clearVector(vector<Edge<int> > vect, int start, int end)
{
	for(int i = 0; i < end && i < vect.size(); i++)
	{
		vect[i].Source = 0;
		vect[i].Target = 0;
	}
}

MappingTestResult Utils::IsMappingCorrect(map<int, int> function, vector<Edge<int> > queryGraphEdges, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount)
{
	vector<int> functionValues;
	for(auto & kv : function)
	{
		functionValues.push_back(kv.second);
	}
    UndirectedGraph<int>* subgraph = GetSubgraph(inputGraph, functionValues);

    return IsMappingCorrect2(function, subgraph, queryGraphEdges, checkInducedMappingOnly);
}

MappingTestResult Utils::IsMappingCorrect2(map<int, int> function, UndirectedGraph<int> subgraph, vector<Edge<int>> queryGraphEdges, bool checkInducedMappingOnly)
{
    // Gather the corresponding potential images of the parentQueryGraphEdges in the input graph
    int qgLen = queryGraphEdges.size();
    vector<Edge<int> > edgeImages;
    for (auto const & edge : queryGraphEdges)
    {
        //Edge<int> x = queryGraphEdges[i];
        //edgeImages.push_back(Edge<int>(function[x.Source], function[x.Target]));
        
        try
        {
            edgeImages.push_back(Edge<int>(function[edge.Source], function[edge.Target]));
        }
        catch (out_of_range)
        {
        }
    }
    MappingTestResult result;
    result.SubgraphEdgeCount = subgraph.EdgeCount();
    
    int compareEdgeCount = result.SubgraphEdgeCount - edgeImages.size();

    if (compareEdgeCount < 0)
    {
        return result;
    }

    // if mapping is possible (=> if compareEdgeCount >= 0)
    vector<int> subgraphDegrees = subgraph.GetReverseDegreeSequence();
    int subgLen = subgraphDegrees.size();
    UndirectedGraph<int> testG;
    testG.AddVerticesAndEdgeRange(edgeImages);
    vector<int> testGdeg = testG.GetReverseDegreeSequence();
    if (compareEdgeCount == 0)
    {
        // Same node count, same edge count
        //TODO: All we now need to do is check that the node degrees match
        for (int i = subgLen - 1; i >= 0; i--)
        {
            if (subgraphDegrees[i] != testGdeg[i])
            {
                result.IsCorrectMapping = false;
                return result;
            }
        }
        
        result.IsCorrectMapping = true;
        return result;
    }

    if (compareEdgeCount > 0) //=> result.SubgraphEdgeCount > edgeImages.Count
    {
        if (checkInducedMappingOnly)
        {
            result.IsCorrectMapping = false;
            return result;
        }

        for (int i = subgLen - 1; i >= 0; i--)
        {
            if (subgraphDegrees[i] < testGdeg[i]) // base should have at least the same value as test
            {
                result.IsCorrectMapping = false;
                return result;
            }
        }
        result.IsCorrectMapping = true;
        return result;
    }

    return result;
}

UndirectedGraph<int>* Utils::GetSubgraph(UndirectedGraph<int> inputGraph, vector<int> g_nodes)
{
    // Remember, f(h) = g, so Function.Values is for g's

    // Try to get all the edges in the induced subgraph made up of these g_nodes
    vector<Edge<int>> inducedSubGraphEdges;
    UndirectedGraph<int>* subgraph = new UndirectedGraph<int>();
    int subgraphSize = g_nodes.size();
    for (int i = 0; i < subgraphSize - 1; i++)
    {
        for (int j = (i + 1); j < subgraphSize; j++)
        {
            Edge<int> edge_g;
            if (inputGraph.TryGetEdge(g_nodes[i], g_nodes[j], edge_g))
            {
                inducedSubGraphEdges.push_back(edge_g);
            }
        }
    }
    subgraph->AddVerticesAndEdgeRange(inducedSubGraphEdges);
    return subgraph;
}

map<vector<int>, vector<Mapping> > Utils::IsomorphicExtension(map<int, int> partialMap, QueryGraph queryGraph, vector<Edge<int> > queryGraphEdges, UndirectedGraph<int> inputGraph, bool getInducedMappingsOnly)
{
    map<vector<int>,vector<Mapping>> output;
    vector<int> pValues;
    vector<int> pKeys;
    for (auto const& set : partialMap)
    {
        pKeys.push_back(set.first);
        pValues.push_back(set.second);
    }
    if (partialMap.size() == queryGraph.VertexCount())
    {
        map<int, int> function = partialMap;

        MappingTestResult result = IsMappingCorrect(function, queryGraphEdges, inputGraph, getInducedMappingsOnly);
        if (result.IsCorrectMapping)
        {
            Mapping singleValue(function,result.SubgraphEdgeCount);
            vector<Mapping> values;
            values.push_back(singleValue);
            output[pValues] = values;


			return output;
        }
        map<vector<int>, vector<Mapping> > null;
        return null;

    }

    //Remember: f(h) = g, so h is Domain and g is Range.
    //  In other words, Key is h and Value is g in the dictionary

    // get m, most constrained neighbors
    int m = GetMostConstrainedNeighbour(pKeys, queryGraph);
    if (m < 0){
        map<vector<int>, vector<Mapping>> null;
        return null;
    };

	map<vector<int>, vector<Mapping> > listOfIsomorphisms;

    vector<int> neighbourRange = ChooseNeighboursOfRange(pValues, inputGraph);
    vector<int> neighborsOfM = queryGraph.GetNeighbors(m);
    int newPartialMapCount = partialMap.size() + 1;
    
    //foreach neighbour n of f(D)
    for (int i = 0; i < neighbourRange.size(); i++)
    {
        if (false == IsNeighbourIncompatible(inputGraph, neighbourRange[i], partialMap, queryGraph, neighborsOfM))
        {
            map<int, int> newPartialMap;
            
            for (auto & item : partialMap)
            {
                newPartialMap[item.first] = item.second;
            }
            
            newPartialMap[m] = neighbourRange[i];
            map<vector<int>, vector<Mapping>> subList = IsomorphicExtension(newPartialMap, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);

            if (subList.size() > 0)
            {
                for (auto & item : subList)
                {
                    if (item.second.size() > 1)
                    {
                        queryGraph.RemoveNonApplicableMappings(item.second, inputGraph, getInducedMappingsOnly);
                    }
                    vector<Mapping> maps;
					if(listOfIsomorphisms.count(item.first))
					{
						maps = listOfIsomorphisms[item.first];
                        for(auto & i : item.second)
                        {
                            maps.push_back(i);
                        }
					}
                    else
                    {
                        listOfIsomorphisms[item.first] = item.second;
                    }
                }
            }
        }
    }

    return listOfIsomorphisms;
}

template <class T>
bool ContainsValue(map<T, T> map, T value)
{
	for(auto & kv : map)
	{
		if(kv.second == value)
		{
			return true;
		}
	}
	return false;
}

template <class T>
bool Contains(vector<T> vect, T val)
{
	for(auto & item : vect)
	{
		if(item == val)
		{
			return true;
		}
	}
	return false;
}

template <class T>
bool tryGetValue(map<T, T> map, T value, T & target)
{
	for(auto & kv : map)
	{
		if(kv.second == value)
		{
			target = kv.second;
			return true;
		}
	}
	return false;
}

bool Utils::IsNeighbourIncompatible(UndirectedGraph<int> inputGraph, int n, map<int, int> partialMap, QueryGraph queryGraph, vector<int> neighborsOfM)
{
    //  RECALL: m is for Domain, the Key => the query graph
    if (ContainsValue(partialMap, n))
    {
        return true; // cos it's already done
    }

    //If there is a neighbor d ∈ D of m such that n is NOT neighbors with f(d),
    auto neighboursOfN = inputGraph.GetNeighbors(n);

    bool doNext = false;
    int val; // f(d)
    for (auto & d : neighborsOfM)
    {
		if(partialMap.count(d))
		{
			val = partialMap[d];
		}
		else
		{
			doNext = true;
			break;
		}
        if (!Contains(neighboursOfN, val))
        {
            return true;
        }
    }

    // or if there is a NON - neighbor d ∈ D of m such that n IS neighbors with f(d)
    if (doNext && queryGraph.VertexCount() > 4)
    {
        vector<int> queryExcept;
        
        for (auto & item : queryGraph.Vertices()){
            if(find(neighborsOfM.begin(), neighborsOfM.end(), item) != neighborsOfM.end()) {
                /* v contains x */
                
            } else {
                /* v does not contain x */
                queryExcept.push_back(item);
            }
        }
            
        
        
        for (auto & d : queryExcept){
            if (partialMap.count(d))
            {
                val = partialMap[d];
            }else{
                neighborsOfM.clear();
                return false;
            }
            
            if (Contains(neighboursOfN, val))
            {
                neighborsOfM.clear();
                return true;
            }

        }
        
    }
    neighborsOfM.clear();
    return false;
}


vector<int> Utils:: ChooseNeighboursOfRange(vector<int> usedRange, UndirectedGraph<int> inputGraph)
{
    vector<int> toReturn;
    //var usedRangeSet = new HashSet<int>(usedRange);
    for (auto & range : usedRange) //usedRangeSet)
    {
        auto local = inputGraph.GetNeighbors(range);
        if (local.size() > 0)
        {
            for (auto & loc : local)
            {
                //if (!usedRangeSet.Contains(loc))
                if (!Contains(usedRange, loc))
                {
                    toReturn.push_back(loc);
                }
            }
        }
        else
        {
            break;
        }
    }
    //usedRangeSet = null;
    return toReturn;
}

int Utils::GetMostConstrainedNeighbour(vector<int> domain, QueryGraph queryGraph)
{
    /*
     * As is standard in backtracking searches, the algorithm uses the most constrained neighbor
     * to eliminate maps that cannot be isomorphisms: that is, the neighbor of the already-mapped
     * nodes which is likely to have the fewest possible nodes it can be mapped to. First we select
     * the nodes with the most already-mapped neighbors, and amongst those we select the nodes with
     * the highest degree and largest neighbor degree sequence.
     * */
    //var domainDict = new HashSet<int>(domain);
    for(auto dom : domain) //domainDict)
    {
        auto local = queryGraph.GetNeighbors(dom);
        if (local.size() > 0)
        {
            for (auto & loc : local)
            {
                //if (!domainDict.Contains(loc))
                if (!Contains(domain, loc))
                {
                    return loc;
                }
            }
        }
    }
    return -1;
}

bool Utils::CanSupport(QueryGraph queryGraph, int node_H, UndirectedGraph<int> inputGraph, int node_G)
{

    return inputGraph.GetDegree(node_G) >= queryGraph.GetDegree(node_H);
}
