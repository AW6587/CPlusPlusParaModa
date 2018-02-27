#include <iostream>

using namespace std;

template <class TVertex>
Edge<TVertex>::Edge(TVertex source, TVertex target)
{
	Source = source;
	Target = target;
}

template <class TVertex>
Edge<TVertex>::Edge()
{
}


template <class TVertex>
string Edge<TVertex>::ToString()
    {
        return to_string(Source) + "->" + to_string(Target);
    }

template <class TVertex>
bool Edge<TVertex>::Equals(Edge<TVertex> obj)
{
    return (Source == (obj.Source) && Target == obj.Target)
        || (Source == (obj.Target) && Target == (obj.Source));
}

template <class TVertex>
bool Edge<TVertex>::operator==(const Edge<TVertex>& other) const
{
	return (Source == other.Source && Target == other.Target)
		|| (Source == other.Target && Target == other.Source);
}

namespace std
{
	template<class TVertex>
	struct hash<Edge<TVertex> >
	{
		std::size_t operator()(const Edge<TVertex>& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			return ((hash<TVertex>()(k.Source)
				^ (hash<TVertex>()(k.Target) << 1)) >> 1);
		}
	};
}
