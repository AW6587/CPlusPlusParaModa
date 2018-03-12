all:
	g++ -std=c++11 ThreeNodes.cpp QueryGraph.cpp ExpansionTreeNode.cpp Mapping.cpp FourNodes.cpp FiveNodes.cpp ModaAlgorithms.cpp Utils.cpp Program.cpp MODATest.cpp
	./a.out runall -g testFile.txt  -n 5
