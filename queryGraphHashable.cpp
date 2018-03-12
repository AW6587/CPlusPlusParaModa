#include <unordered_set>
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"


using namespace std;
int main()
{
	QueryGraph qGraph("name");
	unordered_set<QueryGraph, QueryGraphHasher, QueryGraphComparator> treatedNodes;

}
