#pragma once
#include <iostream>

class ExpansionTreeNode
{
	public:
		bool operator==(const ExpansionTreeNode & other) const;
		bool operator<(const ExpansionTreeNode & other) const;
		ExpansionTreeNode();
        ExpansionTreeNode(QueryGraph other);
		int Level;
		std::string NodeName;
		ExpansionTreeNode *ParentNode;
		bool IsRootNode;

		QueryGraph QueryGraph;
		
		bool Equals(ExpansionTreeNode obj);
		
		int GetHashCode();
		string ToString();
};
