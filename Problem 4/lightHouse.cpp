#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>  // Include this header for reverse function

using namespace std;

struct Lighthouse {
    int x, y;
};

double angle_between(const Lighthouse &p1, const Lighthouse &p2) {
    return atan2(p2.y - p1.y, p2.x - p1.x);
}

int rotate_beam(const vector<Lighthouse> &lighthouses, int start_index, int end_index) {
    int n = lighthouses.size();
    vector<bool> visited(n, false);
    visited[start_index] = true;
    int count = 0;
    int current_index = start_index;

    while (current_index != end_index) {
        count++;
        double best_angle = numeric_limits<double>::infinity();
        int next_index = -1;
        for (int i = 0; i < n; ++i) {
            if (!visited[i] && i != current_index) {
                double angle = angle_between(lighthouses[current_index], lighthouses[i]);
                if (angle < best_angle) {
                    best_angle = angle;
                    next_index = i;
                }
            }
        }
        if (next_index == -1) {
            return numeric_limits<int>::infinity();
        }
        visited[next_index] = true;
        current_index = next_index;
    }

    return count;
}

int min_lighthouses(vector<Lighthouse> lighthouses) {
    int n = lighthouses.size();
    int min_count = numeric_limits<int>::infinity();
    
    for (int direction = -1; direction <= 1; direction += 2) {  // counterclockwise and clockwise
        int start_index = 0;
        int end_index = n - 1;
        if (direction == 1) {
            reverse(lighthouses.begin(), lighthouses.end());
            swap(start_index, end_index);
        }
        min_count = min(min_count, rotate_beam(lighthouses, start_index, end_index));
        if (direction == 1) {
            reverse(lighthouses.begin(), lighthouses.end());
        }
    }

    return min_count;
}

int main() {
    int N;
    cin >> N;
    vector<Lighthouse> lighthouses(N);
    
    for (int i = 0; i < N; ++i) {
        cin >> lighthouses[i].x >> lighthouses[i].y;
    }

    int result = min_lighthouses(lighthouses);

    cout << result << endl;

    return 0;
}

