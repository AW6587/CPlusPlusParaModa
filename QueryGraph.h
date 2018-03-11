#pragma once
#include "UndirectedGraph.h"
#include "Mapping.h"

class QueryGraph : public UndirectedGraph<int>
{
public:
	string Identifier;
    bool IsFrequentSubgraph;
	
	QueryGraph(string label);
	
    QueryGraph(string label, bool allowParralelEdges);
    
    bool IsComplete(int subgraphSize = -1);

    const bool& IsTree(int subgraphSize = -1);

    vector<Mapping> ReadMappingsFromFile(string filename);
    
    string WriteMappingsToFile(vector<Mapping> mappings);
	
    void RemoveNonApplicableMappings(vector<Mapping> mappings, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly = true);
    
	bool AddVerticesAndEdgeRange(vector<Edge<int> > edges);
	
	int edgeCount();
};
