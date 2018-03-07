//
//  ModaAlgorithms.h
//  483
//
//  Copyright © 2018 martin. All rights reserved.
//
#ifndef ModaAlgorithms_h
#define ModaAlgorithms_h
#include <iostream>
#include <fstream>
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
class ModaAlgorithms
{
public:
    //Need to do
    //Implement the Mapping Nodes Comparer
    friend MappingNodesComparer MappingNodesComparer;
    friend vector<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
    ModaAlgorithms();
    
    void BuildTree(int subgraphSize);
    bool UseModifiedGrochow();
    //Algorithm1C
    map<QueryGraph, string> Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize, int thresholdValue);
    //Algorithm1
    map<QueryGraph, vector<Mapping>> Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize = -1, int thresholdValue = 0)

private:
    
    //Need to implement the ExpansionTreeBuilder
    ExpansionTreeBuilder<int> _builder;
    ExpansionTreeNode GetNextNode();
    Edge<int> GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, HashSet<Edge<int>> parentQueryGraphEdges);
    QueryGraph GetParent(QueryGraph queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree);
    vector<Mapping> Algorithm3(Dictionary<QueryGraph, vector<Mapping>> allMappings, UndirectedGraph<int> inputGraph, QueryGraph queryGraph,
                                               AdjacencyGraph<ExpansionTreeNode> expansionTree,
                               QueryGraph parentQueryGraph, string newFileName, string fileName = NULL);
    unordered_set<Mapping> GetSet(Dictionary<int[], vector<Mapping>> theMappings);
    vector<Mapping> Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly)
};

#endif /* ModaAlgorithms_h */
