//#define TEST_MAPPING
#ifdef TEST_MAPPING
#include <iostream>
#include <map>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"

using namespace std;

int main()
{
	// this just ensures that the type is hashable
	map<int, Mapping> testMap;
	map<int, int> intIntMap;
	intIntMap[1] = 2;
	intIntMap[2] = 1;
	
	Mapping a;
	Mapping b(intIntMap, 4);
	Mapping c(b);
	
	cout << "map b == map c: " << endl;
	cout << (b == c ? "True" : "False") << endl;
	
	UndirectedGraph<int> testGraph;
	testGraph.AddVerticesAndEdge(1, 2);
	
	Edge<int> edge1(1, 2);
	Edge<int> edge2(3, 4);
	
	cout << "Getting image of 1,2: " << endl;
	cout << b.GetImage(testGraph, edge1).ToString() << endl;
	cout << "Getting image of 3,4: " << endl;
	cout << b.GetImage(testGraph, edge2).ToString() << endl;
	
	cout << b.GetMappedNodes() << endl;
	
	cout << b.ToString() << endl;
}
#endif
