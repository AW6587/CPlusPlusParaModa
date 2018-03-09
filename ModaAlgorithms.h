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
    // friend MappingNodesComparer MappingNodesComparer;
    ModaAlgorithms();
    
    void BuildTree(int subgraphSize);
    bool UseModifiedGrochow();
    //Algorithm1C
    map<QueryGraph, string> Algorithm1_C(UndirectedGraph<int> inputGraph, QueryGraph qGraph, int subgraphSize, int thresholdValue);
    
    vector<Mapping> Algorithm2(QueryGraph queryGraph, UndirectedGraph<int> inputGraphClone, int numberOfSamples, bool getInducedMappingsOnly);
private:
    
    //Need to implement the ExpansionTreeBuilder
    ExpansionTreeBuilder<int> _builder;
    ExpansionTreeNode GetNextNode();
    
    
};

#endif /* ModaAlgorithms_h */
