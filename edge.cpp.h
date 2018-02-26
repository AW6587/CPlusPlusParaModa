#include <iostream>

using namespace std;

template <class TVertex>
Edge<TVertex>::Edge(TVertex source, TVertex target)
{
	Source = source;
	Target = target;
}

template <class TVertex>
string Edge<TVertex>::ToString()
    {
        return to_string(Source) + "->" + to_string(Target);
    }

template <class TVertex>
bool Edge<TVertex>::Equals(Edge obj)
{
    return (Source == (obj.Source) && Target == obj.Target)
        || (Source == (obj.Target) && Target == (obj.Source));
}
