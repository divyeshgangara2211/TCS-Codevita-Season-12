#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

struct Position {
    int row, col;
    bool operator<(const Position& other) const {
        if (row == other.row) {
            return col < other.col;
        }
        return row < other.row;
    }
};

int n;
vector<string> circuit;
map<Position, double> resistance;

bool is_valid(int row, int col) {
    return row >= 0 && row < n && col >= 0 && col < n;
}

void bfs(Position start, Position end) {
    queue<Position> q;
    set<Position> visited;
    q.push(start);
    visited.insert(start);
    resistance[start] = 0;

    while (!q.empty()) {
        Position current = q.front();
        q.pop();

        if (current.row == end.row && current.col == end.col) {
            break;
        }

        vector<Position> neighbors;
        if (is_valid(current.row + 1, current.col) && circuit[current.row + 1][current.col] == '|') {
            neighbors.push_back({current.row + 1, current.col});
        }
        if (is_valid(current.row - 1, current.col) && circuit[current.row - 1][current.col] == '|') {
            neighbors.push_back({current.row - 1, current.col});
        }
        if (is_valid(current.row, current.col + 1) && circuit[current.row][current.col + 1] == '-') {
            neighbors.push_back({current.row, current.col + 1});
        }
        if (is_valid(current.row, current.col - 1) && circuit[current.row][current.col - 1] == '-') {
            neighbors.push_back({current.row, current.col - 1});
        }

        for (const auto& neighbor : neighbors) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                q.push(neighbor);
                resistance[neighbor] = resistance[current] + 1;
            }
        }
    }
}

int main() {
    cin >> n;
    circuit.resize(n);
    Position start = {0, 0}, end = {0, 0};
    bool first_terminal = true;
    
    for (int i = 0; i < n; ++i) {
        cin >> circuit[i];
        for (int j = 0; j < n; ++j) {
            if (circuit[i][j] == '.') {
                if (first_terminal) {
                    start = {i, j};
                    first_terminal = false;
                } else {
                    end = {i, j};
                }
            }
        }
    }

    bfs(start, end);
    cout << resistance[end] << endl;

    return 0;
}
