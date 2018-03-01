#include "UndirectedGraph.h"

class QueryGraph : UndirectedGraph<int>
{
public:
	string Identifier;
    bool IsFrequentSubgraph;
	
	QueryGraph(string label);
	
    QueryGraph(string label, bool allowParralelEdges);
    
    bool IsComplete(int subgraphSize = -1);

    bool IsTree(int subgraphSize = -1);

    vector<Mapping> ReadMappingsFromFile(string filename);
    
    string WriteMappingsToFile(vector<Mapping> mappings);
	
    void RemoveNonApplicableMappings(vector<Mapping> mappings, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly = true);
    
};
