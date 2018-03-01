#define TEST_QUERY_GRAPH
#ifdef TEST_QUERY_GRAPH
#include <iostream>
#include <fstream>
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"

int main()
{
	// map<int, int> b;
    // b[1] = 2;
    // b[2] = 3;
    // Mapping a(b, 2);
    // Mapping c(b, 2);
	// 
    // vector<Mapping> d;
    // d.push_back(a);
    // d.push_back(c);
	// 
    // QueryGraph e("name");
    // string fileName = e.WriteMappingsToFile(d);
	// 
	// vector<Mapping> mappingVector = e.ReadMappingsFromFile(fileName);
	// 
	// UndirectedGraph<int> inputGraph;
	// inputGraph.AddVerticesAndEdge(1, 2);
	// inputGraph.AddVerticesAndEdge(2, 3);
	// 
	// e.RemoveNonApplicableMappings(mappingVector, inputGraph);
	
	map<int,int> intMapA, intMapB, intMapC, intMapD;
	intMapA[1] = 2;
	intMapA[2] = 3;
	
	intMapB[2] = 15;
	intMapB[3] = 27;
	intMapB[4] = 42;
	
	intMapC[2] = 24;
	intMapC[3] = 42;
	
	intMapD[55] = 24;
	intMapD[245] = 4;
	intMapD[16] = 10;
	intMapD[124] = 421;
	
	vector<Mapping> mappings;
	Mapping a(intMapA, 4);
	Mapping b(intMapB, 4);
	Mapping c(intMapC, 4);
	Mapping d(intMapD, 4);
	
	
	// 2 As
	// 3 Bs
	// 2 Cs
	// 1 D
	mappings.push_back(a);
	mappings.push_back(b);
	mappings.push_back(c);
	mappings.push_back(b);
	mappings.push_back(b);
	mappings.push_back(c);
	mappings.push_back(d);
	mappings.push_back(a);
	
	for(auto & mapping : mappings)
	{
		for(auto & kv : mapping.Function)
		{
			cout << kv.first << "->" << kv.second << endl;
		}
		cout << "~~~~~~~~~~~~" << endl;
	}
	cout << endl << endl << endl;
	
	QueryGraph qga("name");
	UndirectedGraph<int> uga;
	qga.RemoveNonApplicableMappings(mappings, uga, true);
}
#endif
