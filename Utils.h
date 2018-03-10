#include <vector>
#include "QueryGraph.h"
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"
#include "AdjacencyGraph.h"
#include "ExpansionTreeNode.h"
#include "ExpansionTreeBuilder.h"

class MappingTestResult{
public:
    bool IsCorrectMapping;
    int SubgraphEdgeCount;
};

class Utils
{
public:
    const int DefaultEdgeNodeVal = -999;
    static UndirectedGraph<int> GetSubgraph(UndirectedGraph<int> inputGraph, vector<int> g_nodes);
    static map<int[], vector<Mapping>> IsomorphicExtension(map<int, int> partialMap, QueryGraph queryGraph, Edge<int>* queryGraphEdges, UndirectedGraph<int> inputGraph, bool getInducedMappingsOnly);
    static bool CanSupport(QueryGraph queryGraph, int node_H, UndirectedGraph<int> inputGraph, int node_G);
private:
    //Is mapping correct
    static MappingTestResult IsMappingCorrect(map<less<int>, int> function, Edge<int>* queryGraphEdges, UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly, int subGraphEdgeCount = 0);
    //Is mapping correct 2
    static MappingTestResult IsMappingCorrect2(map<less<int>, int> function, UndirectedGraph<int> subgraph, vector<Edge<int>> queryGraphEdges, bool checkInducedMappingOnly);
    static bool IsNeighbourIncompatible(UndirectedGraph<int> inputGraph, int n, map<int, int> partialMap, QueryGraph queryGraph, vector<int> neighborsOfM);
    static vector<int> ChooseNeighboursOfRange(vector<int> usedRange, UndirectedGraph<int> inputGraph);
    static int GetMostConstrainedNeighbour(vector<int> domain, UndirectedGraph<int> queryGraph);
};
