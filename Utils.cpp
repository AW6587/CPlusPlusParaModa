//
//  Utils.cpp
//  testt
//
//  Created by Xiao Huang on 3/10/18.
//  Copyright © 2018 Xiao Huang. All rights reserved.
//

#include "Utils.h"

MappingTestResult Utils::IsMappingCorrect(map<less<int>, int> function, vector<Edge<int>> queryGraphEdges, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount = 0)
{
    UndirectedGraph<int> subgraph = GetSubgraph(inputGraph, function.);
    
    return IsMappingCorrect2(function, subgraph, queryGraphEdges, checkInducedMappingOnly);
}

MappingTestResult Utils::IsMappingCorrect2(map<less<int>, int> function, UndirectedGraph<int> subgraph, vector<Edge<int>> queryGraphEdges, bool checkInducedMappingOnly)
{
    // Gather the corresponding potential images of the parentQueryGraphEdges in the input graph
    int qgLen = queryGraphEdges.capacity();
    Edge<int>* edgeImages = new Edge<int>[qgLen];
    for (int i = 0; i < qgLen; i++)
    {
        Edge<int> x = queryGraphEdges[i];
        edgeImages[i] = *new Edge<int>(function[x.Source], function[x.Target]);
    }
    MappingTestResult result;
    result.SubgraphEdgeCount = subgraph.EdgeCount();
    
    int compareEdgeCount = result.SubgraphEdgeCount.CompareTo(edgeImagesLength);
    if (compareEdgeCount < 0)
    {
        delete[] edgeImages;
        edgeImages = nullptr;
        return result;
    }
    
    // if mapping is possible (=> if compareEdgeCount >= 0)
    vector<int> subgraphDegrees = subgraph.GetReverseDegreeSequence();
    int subgLen = subgraphDegrees.capacity();
    UndirectedGraph<int> testG;
    testG.AddVerticesAndEdgeRange(edgeImages);
    var testGdeg = testG.GetReverseDegreeSequence();
    if (compareEdgeCount == 0)
    {
        // Same node count, same edge count
        //TODO: All we now need to do is check that the node degrees match
        for (int i = subgLen - 1; i >= 0; i--)
        {
            if (subgraphDegrees[i] != testGdeg[i])
            {
                Array.Clear(subgraphDegrees, 0, subgLen);
                subgraphDegrees = null;
                Array.Clear(edgeImages, 0, qgLen);
                edgeImages = null;
                result.IsCorrectMapping = false;
                return result;
            }
        }
        Array.Clear(subgraphDegrees, 0, subgLen);
        subgraphDegrees = null;
        Array.Clear(edgeImages, 0, qgLen);
        edgeImages = null;
        result.IsCorrectMapping = true;
        return result;
    }
    
    if (compareEdgeCount > 0) //=> result.SubgraphEdgeCount > edgeImages.Count
    {
        if (checkInducedMappingOnly)
        {
            Array.Clear(subgraphDegrees, 0, subgLen);
            subgraphDegrees = null;
            Array.Clear(edgeImages, 0, qgLen);
            edgeImages = null;
            result.IsCorrectMapping = false;
            return result;
        }
        
        for (int i = subgLen - 1; i >= 0; i--)
        {
            if (subgraphDegrees[i] < testGdeg[i]) // base should have at least the same value as test
            {
                Array.Clear(subgraphDegrees, 0, subgLen);
                subgraphDegrees = null;
                Array.Clear(edgeImages, 0, qgLen);
                edgeImages = null;
                result.IsCorrectMapping = false;
                return result;
            }
        }
        Array.Clear(subgraphDegrees, 0, subgLen);
        subgraphDegrees = null;
        Array.Clear(edgeImages, 0, qgLen);
        edgeImages = null;
        result.IsCorrectMapping = true;
        return result;
    }
    
    return result;
}

UndirectedGraph<int> Utils::GetSubgraph(UndirectedGraph<int> inputGraph, IList<int> g_nodes)
{
    // Remember, f(h) = g, so Function.Values is for g's
    
    // Try to get all the edges in the induced subgraph made up of these g_nodes
    var inducedSubGraphEdges = new List<Edge<int>>();
    int subgraphSize = g_nodes.Count;
    for (int i = 0; i < subgraphSize - 1; i++)
    {
        for (int j = (i + 1); j < subgraphSize; j++)
        {
            Edge<int> edge_g;
            if (inputGraph.TryGetEdge(g_nodes[i], g_nodes[j], out edge_g))
            {
                inducedSubGraphEdges.Add(edge_g);
            }
        }
    }
    var subgraph = new UndirectedGraph<int>();
    subgraph.AddVerticesAndEdgeRange(inducedSubGraphEdges);
    inducedSubGraphEdges.Clear();
    inducedSubGraphEdges = null;
    return subgraph;
}

Dictionary<int[], List<Mapping>> Utils::IsomorphicExtension(Dictionary<int, int> partialMap, QueryGraph queryGraph, Edge<int>[] queryGraphEdges, UndirectedGraph<int> inputGraph, bool getInducedMappingsOnly)
{
    if (partialMap.Count == queryGraph.VertexCount)
    {
#region Return base case
        var function = new SortedList<int, int>(partialMap);
        
        var result = IsMappingCorrect(function, queryGraphEdges, inputGraph, getInducedMappingsOnly);
        if (result.IsCorrectMapping)
        {
            return new Dictionary<int[], List<Mapping>>(1) { { function.Values.ToArray(), new List<Mapping>(1) { new Mapping(function, result.SubgraphEdgeCount) } } };
        }
        function.Clear();
        function = null;
        return null;
#endregion
        
    }
    
    //Remember: f(h) = g, so h is Domain and g is Range.
    //  In other words, Key is h and Value is g in the dictionary
    
    // get m, most constrained neighbor
    int m = GetMostConstrainedNeighbour(partialMap.Keys, queryGraph);
    if (m < 0) return null;
    
    var listOfIsomorphisms = new Dictionary<int[], List<Mapping>>(ModaAlgorithms.MappingNodesComparer);
    
    var neighbourRange = ChooseNeighboursOfRange(partialMap.Values, inputGraph);
    
    var neighborsOfM = queryGraph.GetNeighbors(m, false);
    var newPartialMapCount = partialMap.Count + 1;
    //foreach neighbour n of f(D)
    for (int i = 0; i < neighbourRange.Count; i++)
    {
        //int n = neighbourRange[i];
        if (false == IsNeighbourIncompatible(inputGraph, neighbourRange[i], partialMap, queryGraph, neighborsOfM))
        {
            //It's not; so, let f' = f on D, and f'(m) = n.
            
            //Find all isomorphic extensions of f'.
            //newPartialMap[m] = neighbourRange[i];
            var newPartialMap = new Dictionary<int, int>(newPartialMapCount);
            foreach (var item in partialMap)
            {
                newPartialMap.Add(item.Key, item.Value);
            }
            newPartialMap[m] = neighbourRange[i];
            var subList = IsomorphicExtension(newPartialMap, queryGraph, queryGraphEdges, inputGraph, getInducedMappingsOnly);
            newPartialMap.Clear();
            newPartialMap = null;
            if (subList != null && subList.Count > 0)
            {
                foreach (var item in subList)
                {
                    if (item.Value.Count > 1)
                    {
                        queryGraph.RemoveNonApplicableMappings(item.Value, inputGraph, getInducedMappingsOnly);
                    }
                    List<Mapping> maps;
                    if (listOfIsomorphisms.TryGetValue(item.Key, out maps))
                    {
                        maps.AddRange(item.Value);
                    }
                    else
                    {
                        listOfIsomorphisms[item.Key] = item.Value;
                    }
                }
                subList.Clear();
            }
            subList = null;
        }
    }
    
    neighborsOfM = null; // DO NOT Clear this variable
    neighbourRange.Clear();
    neighbourRange = null;
    return listOfIsomorphisms;
}

bool Utils::IsNeighbourIncompatible(UndirectedGraph<int> inputGraph,
                             int n, Dictionary<int, int> partialMap, QueryGraph queryGraph, IList<int> neighborsOfM)
{
    //  RECALL: m is for Domain, the Key => the query graph
    if (partialMap.ContainsValue(n))
    {
        return true; // cos it's already done
    }
    
    //If there is a neighbor d ∈ D of m such that n is NOT neighbors with f(d),
    var neighboursOfN = inputGraph.GetNeighbors(n, true); // new HashSet<int>(inputGraph.GetNeighbors(n, true));
    
    bool doNext = false;
    int val; // f(d)
    foreach (var d in neighborsOfM)
    {
        if (!partialMap.TryGetValue(d, out val))
        {
            doNext = true;
            break;
        }
        if (!neighboursOfN.Contains(val))
        {
            //neighboursOfN.Clear();
            neighboursOfN = null;
            return true;
        }
    }
    
    // or if there is a NON - neighbor d ∈ D of m such that n IS neighbors with f(d)
    if (doNext && queryGraph.VertexCount > 4)
    {
        foreach (var d in queryGraph.Vertices.Except(neighborsOfM))
        {
            if (!partialMap.TryGetValue(d, out val))
            {
                //neighboursOfN.Clear();
                neighboursOfN = null;
                return false;
            }
            if (neighboursOfN.Contains(val))
            {
                //neighboursOfN.Clear();
                neighboursOfN = null;
                return true;
            }
        }
    }
    //neighboursOfN.Clear();
    neighboursOfN = null;
    return false;
}

vector<int> Utils::ChooseNeighboursOfRange(IEnumerable<int> usedRange, UndirectedGraph<int> inputGraph)
{
    List<int> toReturn = new List<int>();
    //var usedRangeSet = new HashSet<int>(usedRange);
    foreach (var range in usedRange) //usedRangeSet)
    {
        var local = inputGraph.GetNeighbors(range, true);
        if (local.Count > 0)
        {
            foreach (var loc in local)
            {
                //if (!usedRangeSet.Contains(loc))
                if (!usedRange.Contains(loc))
                {
                    toReturn.Add(loc);
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

int Utils::GetMostConstrainedNeighbour(IEnumerable<int> domain, UndirectedGraph<int> queryGraph)
{
    /*
     * As is standard in backtracking searches, the algorithm uses the most constrained neighbor
     * to eliminate maps that cannot be isomorphisms: that is, the neighbor of the already-mapped
     * nodes which is likely to have the fewest possible nodes it can be mapped to. First we select
     * the nodes with the most already-mapped neighbors, and amongst those we select the nodes with
     * the highest degree and largest neighbor degree sequence.
     * */
    //var domainDict = new HashSet<int>(domain);
    foreach (var dom in domain) //domainDict)
    {
        var local = queryGraph.GetNeighbors(dom, false);
        if (local.Count > 0)
        {
            foreach (var loc in local)
            {
                //if (!domainDict.Contains(loc))
                if (!domain.Contains(loc))
                {
                    return loc;
                }
            }
        }
        local = null; // DO NOT clear
    }
    //domainDict.Clear();
    //domainDict = null;
    return -1;
}

bool Utils::CanSupport(QueryGraph queryGraph, int node_H, UndirectedGraph<int> inputGraph, int node_G)
{
    //// 1. Based on their degrees
    //if (inputGraph.AdjacentDegree(node_G) >= queryGraph.AdjacentDegree(node_H))
    //{
    //    // => we can map the querygraph unto the input graph, based on the nodes given.
    //    // That means we are not ruling out isomorphism. So...
    //    return true;
    //}
    
    //return false;
    return inputGraph.GetDegree(node_G) >= queryGraph.GetDegree(node_H);
}
