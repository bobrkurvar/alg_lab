#include <iostream>
#include <ostream>
#include <string>
#include "graph.h"
#include <queue>
#include <vector>

int Graph::symbol_to_int(char ch) {
	switch (ch)
	{
	case 'a':
		return 0;
	case 'b':
		return 1;
	case 'c':
		return 2;
	case 'd':
		return 3;
	case 'e':
		return 4;
	case 'f':
		return 5;
	case 'g':
		return 6;
	case 'h':
		return 7;
	}
	return -1;
}


bool Graph::is_safe(int x, int y) { return ((x > 7) || (y > 7) || (x < 0) || (y < 0)) ? false : true; }


bool Graph::under_attack(int x_king, int y_king, int x_pawn, int y_pawn)
{
	if (((x_king == x_pawn + 1) || (x_king == x_pawn - 1)) && y_king == y_pawn + 1)
		return true;

	return false;
}



Graph::Graph()
{
	matrix = new int* [8];
	for (int i = 0; i < 8; ++i)
		matrix[i] = new int[8];

	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 8; ++j)
			matrix[i][j] = 0;
	}
}

int Graph::king_breadth_travel(string king, string pawn_1, string pawn_2)
{
	int y_king = (king[1] - '0') - 1;
	int x_king = symbol_to_int(king[0]);
	cout << "king: x: " << to_string(x_king) << " y: " << to_string(y_king) << '\n';
	int  y_pawn_1 = (pawn_1[1] - '0') - 1;
	int x_pawn_1 = symbol_to_int(pawn_1[0]);
	cout << "pawn_1: x: " << to_string(x_pawn_1) << " y: " << to_string(y_pawn_1) << '\n';
	int y_pawn_2 = (pawn_2[1] - '0') - 1;
	int x_pawn_2 = symbol_to_int(pawn_2[0]);
	cout << "pawn_2 x: " << to_string(x_pawn_2) << " y: " << to_string(y_pawn_2) << "\n\n";
	queue<pair<int, int>> tops;
	pair<int, int> king_top(x_king, y_king);
	tops.push(king_top);
	int cnt = 1;
	while (!tops.empty())
	{
		pair<int, int> x = tops.front();
		float min_dist = sqrt((x.first - x_pawn_1) * (x.first - x_pawn_1) + (x.second - y_pawn_1) * (x.second - y_pawn_1));
		cout << '(' << to_string(x.first) << ", " << to_string(x.second) << ")\t";
		for (int i = -1; i < 2; ++i)
		{
			for (int j = -1; j < 2; ++j) {
				if (i == 0 && j == 0)
					continue;
				if (x.first + j == x_pawn_1 && x.second + i == y_pawn_1) {

					cout << "\n\n";
					return cnt;
				}
				if (is_safe(x.first + i, x.second + j))
				{
					if (!under_attack(x.first + i, x.second + j, x_pawn_1, y_pawn_1) && !under_attack(x.first + i, x.second + j, x_pawn_2, y_pawn_2))
					{
						pair<int, int> tmp_top(x.first + i, x.second + j);
						if (matrix[tmp_top.first][tmp_top.second] == 0) {
							matrix[tmp_top.first][tmp_top.second] = 1;
							cout << '(' << to_string(tmp_top.first) << ", " << to_string(tmp_top.second) << ") " << to_string(matrix[tmp_top.first][tmp_top.second]) << ' ';
							float cur_dist = sqrt((tmp_top.first - x_pawn_1) * (tmp_top.first - x_pawn_1) + (tmp_top.second - y_pawn_1) * (tmp_top.second - y_pawn_1));
							if (cur_dist < min_dist)
							{
								tops.pop();
								tops.push(tmp_top);
								min_dist = cur_dist;
							}
						}
					}
				}
			}
		}
		cout << '\n';
		cnt++;
	}
	return 0;
}

ostream& operator<<(ostream& os, Graph& A)
{
	for (int i = 7; i >= 0; --i)
	{
		os << i << '\t';
		for (int j = 0; j < 8; ++j)
			os << to_string(A.matrix[j][i]) << '\t';
		os << '\n';
	}
	os << '\n';
	os << '\t';
	for (int i = 0; i < 8; ++i)
		cout << i << '\t';
	return os;
}
