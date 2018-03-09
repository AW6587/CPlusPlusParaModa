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
#include <queue>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
#include "AdjacencyGraph.h"
#include "ExpansionTreeNode.h"
#include "ExpansionTreeBuilder.h"
class ModaAlgorithms
{
public:
    //Need to do
    //Implement the Mapping Nodes Comparer
    friend MappingNodesComparer MappingNodesComparer;
    friend vector<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
    ModaAlgorithms();
    
    void BuildTree(int subgraphSize);
    bool UseModifiedGrochow;
    
    //Algorithm1C
    map<QueryGraph, string> Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize, int thresholdValue);
    
    //Algorithm1
    map<QueryGraph, vector<Mapping>> Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize = -1, int thresholdValue = 0)

private:
    
    //Need to implement the ExpansionTreeBuilder
    ExpansionTreeBuilder<int> _builder;
    ExpansionTreeNode GetNextNode(){
        if (_builder.verticesSorted.capacity() > 0)
        {
            return _builder.VerticesSorted.Dequeue();
        }
        return NULL;
    };
    
    //Get edge difference
    Edge<int> GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, HashSet<Edge<int>> parentQueryGraphEdges);
    
    //Get Parent query node
    QueryGraph GetParent(QueryGraph queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree);
    
    //Algorithm 3
    vector<Mapping> Algorithm3(Dictionary<QueryGraph, vector<Mapping>> allMappings, UndirectedGraph<int> inputGraph, QueryGraph queryGraph,
                                               AdjacencyGraph<ExpansionTreeNode> expansionTree,
                               QueryGraph parentQueryGraph, string newFileName, string fileName = NULL);
    
    //Get set
    unordered_set<Mapping> GetSet(Dictionary<int[], vector<Mapping>> theMappings);
    
    //Algorithm2 modified
    vector<Mapping> Algorithm2_Modified(QueryGraph queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly)
    
    //Algorithm2
    vector<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly)
};

#endif /* ModaAlgorithms_h */
