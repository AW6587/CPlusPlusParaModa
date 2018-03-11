#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "edge.h"
#include "UndirectedGraph.h"
#include "GraphProcessor.h"

int main()
{
	UndirectedGraph<int> newGraphInstance1;
	cout << GraphProcessor::LoadGraph("testFile.txt", &newGraphInstance1) << endl;
	cout << newGraphInstance1.ToString() << endl;
	
	// UndirectedGraph<int> newGraphInstance2 = LoackGraph("testFile.txt", true);
}
