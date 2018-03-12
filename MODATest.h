#include <iostream>
#include <vector>
#include "UndirectedGraph.h"
#include "QueryGraph.h"

using namespace std;

namespace MODATest
{
	void Run(vector<string> args);
	void Process(string options,
				 UndirectedGraph<int> inputGraph,
				 QueryGraph * queryGraph = nullptr,
				 int subGraphSize = -1,
				 bool saveTempMappingsToDisk = false);
}
