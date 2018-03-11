#include <iostream>
#include <fstream>
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"

int main()
{
	map<int, int> b;
    b[1] = 2;
    b[2] = 3;
    Mapping a(b, 2);
    Mapping c(b, 2);

    vector<Mapping> d;
    d.push_back(a);
    d.push_back(c);

    QueryGraph e("name");
    string fileName = e.WriteMappingsToFile(d);
	
	vector<Mapping> mappingVector = e.ReadMappingsFromFile(fileName);
	
	UndirectedGraph<int> inputGraph;
	inputGraph.AddVerticesAndEdge(1, 2);
	inputGraph.AddVerticesAndEdge(2, 3);
	
	e.RemoveNonApplicableMappings(mappingVector, inputGraph);
}
