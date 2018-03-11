#include <iostream>
#include "BreadthFirstSearchAlgorithm.h"

using namespace std;

int main()
{
	AdjacencyGraph<int> b;
	BreadthFirstSearchAlgorithm a(b);
	a.Compute();
}
