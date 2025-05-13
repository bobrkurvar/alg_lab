#include <iostream>
#include <ostream>
#include <string>
#include "graph.h"
#include <queue>

int main()
{
	Graph graph;
	cout << graph.king_breadth_travel("c3", "b7", "c5") << "\n\n";
	cout << graph << '\n';
}