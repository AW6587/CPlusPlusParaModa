#include <iostream>
#include <fstream>
#include <map>
#include <vector>

#include "edge.h"
#include "UndirectedGraph.h"
#include "GraphProcessor.h"

int main()
{
	UndirectedGraph<int> newGraphInstance;
	GraphProcessor::LoadGraph("testFile.txt", &newGraphInstance);
}
