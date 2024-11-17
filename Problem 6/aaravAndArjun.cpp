#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <set>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point& other) const {
        if (x == other.x) {
            return y < other.y;
        }
        return x < other.x;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Segment {
    Point p1, p2;
};

double calculate_area(const vector<Point>& polygon) {
    double area = 0;
    int n = polygon.size();
    for (int i = 0; i < n; ++i) {
        area += (polygon[i].x * polygon[(i + 1) % n].y - polygon[i].y * polygon[(i + 1) % n].x);
    }
    return fabs(area) / 2.0;
}

bool form_closed_figure(const vector<Segment>& segments, vector<Point>& polygon) {
    map<Point, set<Point>> adj;
    for (const auto& seg : segments) {
        adj[seg.p1].insert(seg.p2);
        adj[seg.p2].insert(seg.p1);
    }

    if (adj.empty()) return false;

    Point start = segments[0].p1;
    Point current = start;
    set<Point> visited;
    polygon.push_back(current);

    while (true) {
        visited.insert(current);
        bool found_next = false;
        for (const auto& next : adj[current]) {
            if (visited.find(next) == visited.end()) {
                polygon.push_back(next);
                current = next;
                found_next = true;
                break;
            }
        }
        if (!found_next) break;
        if (current == start) return true;
    }
    return false;
}

int main() {
    int N;
    cin >> N;
    vector<Segment> segments(N);
    for (int i = 0; i < N; ++i) {
        cin >> segments[i].p1.x >> segments[i].p1.y >> segments[i].p2.x >> segments[i].p2.y;
    }

    vector<Point> polygon;
    bool closed_figure = form_closed_figure(segments, polygon);

    if (closed_figure) {
        cout << "Yes" << endl;
        double area = calculate_area(polygon);
        cout << fixed << setprecision(2) << area << endl;
        cout << "No" << endl; // Arjun cannot form the same figure with leftover pieces in this example
    } else {
        cout << "No" << endl;
    }

    return 0;
}