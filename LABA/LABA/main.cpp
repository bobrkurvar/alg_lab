#include <iostream>
#include <iomanip>

using namespace std;


bool isSafe(int x, int y, int n, int** board) { return (x >= 0 && x < n && y >= 0 && y < n && board[x][y] == 0); }
int** best_board;

bool move(int n, int x, int y, int move_count, int& max_move_count, int** board) {
    const int move_x[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };
    const int move_y[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };

    board[x][y] = move_count;
    if (move_count == n * n) {
        for (int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j)
                best_board[i][j] = board[i][j];
        }
        return true;
    }

    for (int i = 0; i < 8; ++i) {
        int nextX = x + move_x[i];
        int nextY = y + move_y[i];

        if (isSafe(nextX, nextY, n, board)) {
            if (move(n, nextX, nextY, move_count + 1, max_move_count, board)) {
                return true;
            }
        }
    }
    if (move_count > max_move_count) {
        max_move_count = move_count;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                best_board[i][j] = board[i][j];
        }
    }

    board[x][y] = 0;
    return false;
}

void printBoard(int n, int** board) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(3) << board[j][i] << " ";
        }
        cout << endl;
    }
}

int main() {
    setlocale(0, "");
    int n, x, y;
    cout << "Enter n: ";
    cin >> n;
    cout << "Enter x: ";
    cin >> x;
    cout << "Enter y: ";
    cin >> y;

    int max_count = 1;

    int** board = new int* [n];
    best_board = new int* [n];
    for (int i = 0; i < n; ++i) {
        board[i] = new int[n];
        best_board[i] = new int[n];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = 0;
            best_board[i][j] = 0;
        }
    }

    best_board[x][y] = 1;
    if (!move(n, x, y, 1, max_count, board))
        cout << "No solution" << '\n';
    printBoard(n, best_board);
}