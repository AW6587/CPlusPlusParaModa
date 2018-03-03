class Mapping
{
	public:
		int Id;
		
		// This represents the [f(h) = g] relation. Meaning key is h and value is g.
		std::map<int, int> Function;
		
		/// <summary>
		/// Count of all the edges in the input subgraph G that fit the query graph (---Function.Keys).
		/// This count is for the induced subgraph
		/// </summary>
		int SubGraphEdgeCount;
		
		Mapping();

		Mapping(const Mapping & mapping);

		Mapping(std::map<int, int> function, int subGraphEdgeCount);

		/// <summary>
		/// Gets the corresponding image of the <see cref="newlyAddedEdge"/> in the <see cref="inputGraph"/>.
		/// Use only for when (InducedSubGraph.EdgeCount > currentQueryGraphEdgeCount)
		/// </summary>
		/// <param name="inputGraph"></param>
		/// <param name="newlyAddedEdge"></param>
		/// <returns></returns>
		Edge<int> GetImage(UndirectedGraph<int> inputGraph, Edge<int> newlyAddedEdge);

		bool operator==(const Mapping &other) const;

		bool Equals(Mapping other);
		
		
		//  override int GetHashCode();

		/// <summary>
		/// Retruns the nodes in the input graph that the query graph mapped to.
		/// It's returned as a string where the nodes values are concatenated with '-'
		/// </summary>
		/// <returns></returns>
		string GetMappedNodes();

		string ToString();
};
#include "Mapping.cpp"
