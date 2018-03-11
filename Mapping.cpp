#include <iostream>
#include <map>
#include <sstream>
#include "edge.h"
#include "UndirectedGraph.h"
#include "Mapping.h"
#include "Utils.h"
using namespace std;

Mapping::Mapping()
{
	Id = -1;
}

Mapping::Mapping(const Mapping & mapping)
{
	Function = mapping.Function;
	Id = mapping.Id;
	SubGraphEdgeCount = mapping.SubGraphEdgeCount;
}

Mapping::Mapping(std::map<int, int> function, int subGraphEdgeCount)
{
	Function = function;
	Id = -1;
	SubGraphEdgeCount = subGraphEdgeCount;
}

Edge<int> Mapping::GetImage(UndirectedGraph<int> inputGraph, Edge<int> newlyAddedEdge)
{
	Edge<int> image;
	if (inputGraph.TryGetEdge(Function[newlyAddedEdge.Source], Function[newlyAddedEdge.Target], &image))
	{
	    return image;
	}
	return Edge<int>(Utils::DefaultEdgeNodeVal, Utils::DefaultEdgeNodeVal);
}

bool Mapping::Equals(Mapping other)
{
	if (Id >= 0 || other.Id >= 0) 
	{
		return Id == other.Id;
	}
	
	return Function == other.Function;
}

bool Mapping::operator==(const Mapping &other) const
{ 
	if (Id >= 0 || other.Id >= 0) 
	{
		return Id == other.Id;
	}
	
	return Function == other.Function;
}

string Mapping::GetMappedNodes()
{
	string retVal = "";
	for(auto & kv : Function)
	{
		retVal += to_string(kv.first);
		retVal += "-";
	}
	return retVal;
}

string Mapping::ToString()
{
	ostringstream ss;
	ss << "[";
	for(auto & item : Function)
	{
		ss << item.first << "-";
	}
	ss << "] => [";
	for(auto & item : Function)
	{
		ss << item.second << "-";
	}
	ss << "]" << endl;
	return ss.str();
}

namespace std {

  template <>
  struct hash<Mapping>
  {
    size_t operator()(const Mapping& m) const
    {
		if (m.Id >= 0) 
		{
			return m.Id;
		}
		return ((hash<int>()(m.Id)
               ^ (hash<int>()(m.SubGraphEdgeCount) << 1)) >> 1);

    }
  };

}
