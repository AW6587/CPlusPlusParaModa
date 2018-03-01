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


bool contains(vector<int> vect, int a)
{
	for(int i = 0; i < vect.size(); i++)
	{
		if(vect[i] == a)
		{
			return true;
		}
	}
	return false;
}

bool mapEquality(map<int,int> aMap, map<int,int> bMap)
{
	vector<int> a, b;
	if (aMap.size() != bMap.size()) 
	{
		return false;
	}
	
	for(auto & kv : aMap)
	{
		a.push_back(kv.second);
	}
	
	for(auto & kv : bMap)
	{
		b.push_back(kv.second);
	}
	
	for (int i = 0; i < a.size(); i++)
	{
		if (!contains(b, a[i]))
		{
			return false;
		}
	}
	return true;
}

void printMap(map<int,int> a)
{
	for(auto & kv : a)
	{
		cout << kv.first << "->" << kv.second << endl;
	}
}

void QueryGraph::RemoveNonApplicableMappings(vector<Mapping> mappings, 
	UndirectedGraph<int> inputGraph, bool checkInducedMappingOnly)
{
	if(mappings.size() < 2)
	{
		return;
	}
	
	int subgraphSize = VertexCount();
	vector<Mapping> mapGroups;
	int startSize = mappings.size();
	
	while(mapGroups.size() < startSize)
	{
		// add All maps that match mappings[0]
		Mapping mappingToMatch = mappings[0];
		for(int i = 0; i < mappings.size(); i ++)
		{
			if(mapEquality(mappingToMatch.Function, mappings[i].Function))
			{
				mapGroups.push_back(mappingToMatch);
			}
		}
		// delete All maps that match mappings[0]
		for(int i = mappings.size() - 1; i >= 0; i--)
		{
			if(mapEquality(mappingToMatch.Function, mappings[i].Function))
			{
				mappings.erase(mappings.begin() + i);
			}
		}
	}
	
	#ifdef TEST_QUERY_GRAPH
	for(auto & mapping : mappings)
	{
		for(auto & kv : mapping.Function)
		{
			cout << kv.first << "->" << kv.second << endl;
		}
		cout << "~~~~~~~~~~~~" << endl;
	}
	cout << endl << endl << endl;
	#endif
	
	vector<Mapping> toAdd;
	vector<Edge<int> > queryGraphEdges = Edges();
	
	for(auto & group : mapGroups)
	{
		vector<int> g_nodes;
		for(auto & i : group.Function)
		{
			g_nodes.push_back(i.first);
		}
		
		vector<Edge<int> > inducedSubGraphEdges;
		for (int i = 0; i < subgraphSize - 1; i++)
		{
			for (int j = (i + 1); j < subgraphSize; j++)
			{
				Edge<int> edge_g;
				if (inputGraph.TryGetEdge(g_nodes[i], g_nodes[j], &edge_g))
				{
					inducedSubGraphEdges.push_back(edge_g);
				}
			}
		}
	}
}
