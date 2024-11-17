#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// Directions for moving in the grid
const int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

// Function to check if bands are interlocked using BFS
bool checkInterlock(const vector<string>& grid, int x, int y, char band, vector<vector<bool>>& visited) {
    int n = grid.size();
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    visited[x][y] = true;
    
    while (!q.empty()) {
        pair<int, int> cell = q.front(); q.pop();
        int cx = cell.first;
        int cy = cell.second;
        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (grid[nx][ny] == band && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push(make_pair(nx, ny));
                } else if (grid[nx][ny] != band && grid[nx][ny] != '.') {
                    return true; // Interlocked
                }
            }
        }
    }
    return false;
}

// Function to count overlaps using BFS
int countOverlaps(const vector<string>& grid, int x, int y, char band, vector<vector<bool>>& visited) {
    int n = grid.size();
    queue<pair<int, int>> q;
    q.push(make_pair(x, y));
    visited[x][y] = true;
    int overlapCount = 0;
    
    while (!q.empty()) {
        pair<int, int> cell = q.front(); q.pop();
        int cx = cell.first;
        int cy = cell.second;
        for (auto& dir : directions) {
            int nx = cx + dir[0];
            int ny = cy + dir[1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (grid[nx][ny] == band && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push(make_pair(nx, ny));
                } else if (grid[nx][ny] != band && grid[nx][ny] != '.') {
                    overlapCount++;
                }
            }
        }
    }
    return overlapCount;
}

int main() {
    int S;
    cin >> S;
    vector<string> grid(S);
    for (int i = 0; i < S; ++i) {
        cin >> grid[i];
    }

    vector<vector<bool>> visited(S, vector<bool>(S, false));
    bool interlocked = false;
    int totalOverlaps = 0;

    // Check bands with character '1'
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            if (grid[i][j] == '1' && !visited[i][j]) {
                if (checkInterlock(grid, i, j, '1', visited)) {
                    interlocked = true;
                    break;
                }
                totalOverlaps += countOverlaps(grid, i, j, '1', visited);
            }
        }
        if (interlocked) break;
    }

    // Reset visited for the next band
    fill(visited.begin(), visited.end(), vector<bool>(S, false));

    // Check bands with character '2'
    for (int i = 0; i < S; ++i) {
        for (int j = 0; j < S; ++j) {
            if (grid[i][j] == '2' && !visited[i][j]) {
                if (checkInterlock(grid, i, j, '2', visited)) {
                    interlocked = true;
                    break;
                }
                totalOverlaps += countOverlaps(grid, i, j, '2', visited);
            }
        }
        if (interlocked) break;
    }

    if (interlocked) {
        cout << "Impossible" << endl;
    } else {
        cout << totalOverlaps / 2 << endl; // Divide by 2 to avoid double-counting overlaps
    }

    return 0;
}
