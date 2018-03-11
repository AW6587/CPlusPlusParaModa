#include <map>
#include <sstream>
#include <string>
#include <fstream>
#include "nlohmann/json.hpp"
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "QueryGraph.h"

using json = nlohmann::json; 
using namespace std;

QueryGraph::QueryGraph(string label) : UndirectedGraph<int>()
{
	Identifier = label;
}

QueryGraph::QueryGraph(string label, bool allowParralelEdges) : UndirectedGraph<int>(allowParralelEdges)
{
	Identifier = label;
}

//subgraphSize defaults to -1
bool QueryGraph::IsComplete(int subgraphSize)
{
	if (subgraphSize <= 1) 
	{
		subgraphSize = VertexCount();
	}
    return EdgeCount() == ((subgraphSize * (subgraphSize - 1)) / 2);
}

//subgraphSize defaults to -1
bool QueryGraph::IsTree(int subgraphSize)
{
	if (subgraphSize <= 1) 
	{
		subgraphSize = VertexCount();
	}
    return EdgeCount() == (subgraphSize - 1);
}

vector<int> numsInQuotes(string input)
{
	vector<int> retVal;
	bool inString = false;
	stringstream ss;
	while(input.length() > 0)
	{	
		if(input.at(0) == '\"')
		{
			if(inString == true)
			{
				inString = false;
				// put ss into vector and clear it;
				retVal.push_back(0);
				ss >> retVal[retVal.size() - 1];
				ss.clear();
				ss.str("");
			}
			else
			{
				inString = true;
			}
		}
		else if(inString)
		{
			ss << input.at(0);
		}
		input = input.substr(1);
	}
	return retVal;
}

vector<Mapping> QueryGraph::ReadMappingsFromFile(string filename)
{
	std::ifstream i(filename);
	json jsonFile;
	i >> jsonFile;
	vector<Mapping> mappings;
	
	for(auto & item : jsonFile)
	{
		Mapping temp;
		temp.Id = item["Id"];
		
		stringstream functionSStream;
		functionSStream << item["Function"];
		string functionString = functionSStream.str();
		vector<int> keys = numsInQuotes(functionString);
		for(int & integer : keys)
		{
			temp.Function[integer] = item["Function"][to_string(integer)];
		}
		
		temp.SubGraphEdgeCount = item["SubGraphEdgeCount"];
		mappings.push_back(temp);
	}

    return mappings;
}

//TODO: if time, write a compressed version of the string to the file, and decompres above
string QueryGraph::WriteMappingsToFile(vector<Mapping> mappings)
{
	stringstream fileName;
	fileName << mappings.size();
	fileName << "#";
	fileName << Identifier;
	fileName << ".ser";

	stringstream ss;
	ss << "[";
	
	int mappingCount = 0;
	for(auto & mapping : mappings)
	{
		mappingCount++;
		ss << "{\"Id\":" << mapping.Id << ",";
		ss << "\"Function\":{";
		int itemCount = 0;
		for(auto & item : mapping.Function)
		{
			itemCount++;
			ss << "\"" << item.first << "\":" << item.second;
			if(itemCount < mapping.Function.size())
			{
				ss << ",";
			} 
		}
		ss << "}";
		ss << ",\"SubGraphEdgeCount\":" << mapping.SubGraphEdgeCount << "}";
		if(mappingCount < mappings.size())
		{
			ss << ",";
		}
	}
	ss << "]";
	
	ofstream outfile;
	outfile.open(fileName.str());
	outfile << ss.rdbuf();
	outfile.close();
	
	return fileName.str();
}

void QueryGraph::RemoveNonApplicableMappings(vector<Mapping> mappings, 
	UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly)
{
	//TODO: finish this
}

bool QueryGraph::AddVerticesAndEdgeRange(vector<Edge<int> > edges)
{
	return UndirectedGraph<int>::AddVerticesAndEdgeRange(edges);
}

int QueryGraph::edgeCount()
{
	return UndirectedGraph<int>::edgeCount;
}
