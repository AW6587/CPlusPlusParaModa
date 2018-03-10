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
#include <unordered_set>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
#include "AdjacencyGraph.h"
#include "ExpansionTreeNode.h"
#include "ExpansionTreeBuilder.h"
#include "MappingNodesComparer.h"

class ModaAlgorithms
{
public:
    ModaAlgorithms();
    
    void BuildTree(int subgraphSize);
    bool UseModifiedGrochow;
    
    //Algorithm1C
    map<QueryGraph, string> Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph* qGraph, int subgraphSize, int thresholdValue);
    
    //Algorithm1
    map<QueryGraph, vector<Mapping>> Algorithm1(UndirectedGraph<int> inputGraph, QueryGraph* qGraph, int subgraphSize, int thresholdValue);
    
    //Algorithm2
    vector<Mapping> Algorithm2(QueryGraph* queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly);

private:
    
    ExpansionTreeBuilder<int> _builder;
    ExpansionTreeNode* GetNextNode();
    
    //Get edge difference
    Edge<int> GetEdgeDifference(QueryGraph currentQueryGraph, QueryGraph parentQueryGraph, unordered_set<Edge<int>> parentQueryGraphEdges);
    
    //Get Parent query node
    QueryGraph GetParent(QueryGraph* queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree);
    
    //Algorithm 3
    vector<Mapping> Algorithm3(map<QueryGraph, vector<Mapping>> allMappings, UndirectedGraph<int> inputGraph, QueryGraph* queryGraph, AdjacencyGraph<ExpansionTreeNode> expansionTree, QueryGraph parentQueryGraph, string newFileName, string = "" );
    
    //Get set
    vector<Mapping> GetSet(map<int[], vector<Mapping>> theMappings);
    
    //Algorithm2 modified
    vector<Mapping> Algorithm2_Modified(QueryGraph* queryGraph, UndirectedGraph<int> inputGraph, int numberOfSamples, bool getInducedMappingsOnly);
};

#endif /* ModaAlgorithms_h */
