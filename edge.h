#ifndef __EDGE_H
#define __EDGE_H
template <class TVertex>
class Edge
{
	public:
		bool operator==(const Edge<TVertex> & other) const;
		TVertex Source;
		TVertex Target;

		Edge(TVertex source, TVertex target);
		Edge();
		std::string ToString();

	    bool Equals(Edge obj);
};

#include "edge.cpp.h"
#endif
