#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include <queue>

using namespace std;

class Graph
{
	int** matrix;
	bool is_safe(int x, int y);
	int symbol_to_int(char);
	bool under_attack(int x_king, int y_king, int x_pawn, int y_pawn);
public:
	Graph();
	int king_breadth_travel(string king, string pawn_1, string pawn_2);
	friend ostream& operator<<(ostream& os, Graph& A);
};