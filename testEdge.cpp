#include <iostream>
#include <string>
#include "edge.h"

using namespace std;

int main()
{
//									1
	// 1 2						/		\
	// 1 3					2				3
	// 1 4								/
	// 4 3							4
	
	Edge<int> a(1, 2);
	Edge<int> b(1, 3);
	Edge<int> c(1, 4);
	Edge<int> d(4, 3);
	
	cout << a.ToString() << endl;
	cout << b.ToString() << endl;
	cout << c.ToString() << endl;
	cout << d.ToString() << endl;
}
