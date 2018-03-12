#ifndef __GRAPH_PROCESSOR_H
#define __GRAPH_PROCESSOR_H

#include <sstream>

namespace GraphProcessor
{
	// this only works if T is an int. Specialized versions of this template will be needed
	// if we need to use it with other types.
	template<class T>
	inline string LoadGraph(string filename, UndirectedGraph<T> *newGraphInstance)
	{
		vector<string> lines;

		string line;
		ifstream inFile (filename);
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
			istringstream tokenStream(line);
			while (std::getline(tokenStream, token, '\t'))
			{
				tmp.push_back(token);
			}

			newGraphInstance->AddVerticesAndEdge(Edge<T>(stoi(tmp[0]), stoi(tmp[1])));

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

	inline UndirectedGraph<int> LoadGraph(std::string filename, bool isQueryGraph = false)
	{
	  vector<string> lines;

	  string line;
	  ifstream inFile (filename);
	  if (inFile.is_open())
	  {
		while ( getline (inFile,line) )
		{
		  lines.push_back(line);
		}
		inFile.close();
	  }
	  UndirectedGraph<int> newGraphInstance;
	  if (isQueryGraph)
	  {
		newGraphInstance = new QueryGraph(filename.substr(0, filename.find('.') + 1));
	  }
	  else
	  {
		newGraphInstance = new UndirectedGraph<int>();
	  }

	for(auto & line : lines)
	  {
		vector<string> tmp;
		if (line.at(0) == '#')
		{
		  continue;
		}

		string token;
		istringstream tokenStream(line);
		while (std::getline(tokenStream, token, '\t'))
		{
		  if(token.size() > 0)
		  {
			tmp.push_back(token);
		  }
		}
		if (tmp.size() < 2)
		{
		  continue;
		}
		//newGraphInstance.AddVerticesAndEdge(new Edge<int>(tmp[0], tmp[1]));
		newGraphInstance.AddVerticesAndEdge(stoi(tmp[0]), stoi(tmp[1]));
	  }
	  return newGraphInstance;
	}
}

#endif
