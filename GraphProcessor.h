#ifndef __GRAPH_PROCESSOR_H
#define __GRAPH_PROCESSOR_H

#include <string>
#include <sstream>
#include <experimental/filesystem>
#include <vector>
namespace fs = std::experimental::filesystem;
#include "QueryGraph.h"

namespace GraphProcessor
{
	// this only works if T is an int. Specialized versions of this template will be needed
	// if we need to use it with other types.
	template<class T>
	inline string LoadGraph(string filename, UndirectedGraph<T> *newGraphInstance)
	{
		vector<string> lines;

		string line;
		std::ifstream inFile (filename);
		if (inFile.is_open())
		{
			while ( getline (inFile,line) )
			{
				lines.push_back(line);
			}
			inFile.close();
		};

		clock_t timer = clock();
		for(auto & line : lines)
		{
			vector<string> tmp;
			if(line.at(0) == '#')
			{
				continue;
			}

			//line separate tmp into an array of strings. One string for each vertex.
			string token;
			std::istringstream tokenStream(line);
			while (std::getline(tokenStream, token, '\t'))
			{
				tmp.push_back(token);
			}

			newGraphInstance->AddVerticesAndEdge(Edge<T>(std::stoi(tmp[0]), std::stoi(tmp[1])));

		}
		ostringstream ss;
		int nodeCount = newGraphInstance->VertexCount();
        int edgeCount = newGraphInstance->EdgeCount();
        double inv = (nodeCount * nodeCount * 1.0) / edgeCount;
        int sparse = inv > 64;
		ostringstream invDeg;
		invDeg << inv << " (" << (inv > 64 ? "Sparse" : "Dense") << " Graph)";

		ss << "\tFile loaded: " << filename << "\n\nNumber of lines in file:\t";
		ss << edgeCount << "\nNumber of nodes:\t\t" << nodeCount;
		ss << "\nInv Degree:\t" << invDeg.str() << "\nTime Taken to Process:\t";
		ss << clock() - timer << "ms";

		return ss.str();

	}

	// returns UndirectedGraph pointer
	// ModaTest writer will need to handle a pointer because C++ does
	// not allow passing by reference for objects
	inline UndirectedGraph<int> *LoadGraph(string filename, bool isQueryGraph = false)
	{
		vector<string> lines;
		string line;
		std::ifstream inFile (filename);
		if (inFile.is_open())
		{
			while ( getline(inFile,line) )
			{
				lines.push_back(line);
			}
			inFile.close();
		}

		UndirectedGraph<int> *newGraphInstance;
		if (isQueryGraph)
		{
			//string testFile = "testFile";
			//*newGraphInstance = new QueryGraph(testFile);
			newGraphInstance = new QueryGraph((fs::path(filename).stem()).string()) { };
		}
		else
		{
			newGraphInstance = new UndirectedGraph<int>();
		}
		vector<string> tmp;
		for (auto line : lines)
		{
			if (line.at(0) == '#')
			{
				continue;
			}
			//line separate tmp into an array of strings. One string for each vertex.
			string token;
			std::istringstream tokenStream(line);
			while (std::getline(tokenStream, token, '\t'))
			{
				tmp.push_back(token);
			}
			newGraphInstance->AddVerticesAndEdge(std::stoi(tmp[0]), std::stoi(tmp[1]));
		}

		return newGraphInstance;
	}
}

#endif

