#include <iostream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include "QueryGraph.h"
#include "ExpansionTreeNode.h"

using namespace std;


string toLower(string input)
{
	string output = "";
	for(int i = 0; i < input.length(); i++)
	{
		output += putchar(tolower(input.at(i)));
	}
	return output;
}

bool ExpansionTreeNode::operator==(const ExpansionTreeNode & other) const
{
	if (other.IsRootNode && IsRootNode) return true;

    return toLower(NodeName).compare(toLower(other.NodeName)) == 0;
}

bool ExpansionTreeNode::operator<(const ExpansionTreeNode & other) const
{
	return Level < other.Level;
}

ExpansionTreeNode::ExpansionTreeNode() : QueryGraph("")
{
}

bool ExpansionTreeNode::Equals(ExpansionTreeNode obj)
{
    if (obj.IsRootNode && IsRootNode) return true;

    return toLower(NodeName).compare(toLower(obj.NodeName)) == 0;
}

int ExpansionTreeNode::GetHashCode()
{
	return IsRootNode ? ((hash<int>()(Level)
		   ^ (hash<string>()(NodeName) << 1)) >> 1) : hash<string>()(QueryGraph.Identifier);
}

string ExpansionTreeNode::ToString()
{
	stringstream ss;
	ss << "Node: Name: " << NodeName << "; Level - " << Level << "; Is Root - ";
	ss << IsRootNode << "; Number of QueryGraph edges -  " << QueryGraph.edgeCount();
	return ss.str();
}
