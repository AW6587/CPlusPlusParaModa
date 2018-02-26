template <class TVertex>
class Edge
{
	public:
		TVertex Source;
		TVertex Target;

		Edge(TVertex source, TVertex target);
		Edge();
		std::string ToString();

	    bool Equals(Edge obj);
};

#include "edge.cpp.h"
