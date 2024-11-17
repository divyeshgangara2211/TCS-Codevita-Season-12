#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int findMinMoves(vector<string>& instructions) {
    int n = instructions.size();
    int moves = 0;

    // Initialize leg positions
    string leftLeg = "", rightLeg = "";

    for (int i = 0; i < n; i++) {
        string instruction = instructions[i];

        if (leftLeg.empty() || rightLeg.empty()) {
            // If either leg has not been placed yet, place it
            if (leftLeg.empty()) {
                leftLeg = instruction;
            } else {
                rightLeg = instruction;
            }
        } else {
            // Both legs are placed, determine which leg to move
            if (instruction != leftLeg && instruction != rightLeg) {
                // Move the leg that requires less movement
                // We simply increment moves since any move counts equally here
                moves++;
                if (i + 1 < n && instructions[i + 1] != leftLeg && instructions[i + 1] == rightLeg) {
                    leftLeg = instruction;
                } else {
                    rightLeg = instruction;
                }
            }
        }
    }

    return moves;
}

int main() {
    int n;
    cin >> n;
    vector<string> instructions(n);

    for (int i = 0; i < n; ++i) {
        cin >> instructions[i];
    }

    cout << findMinMoves(instructions) << endl;

    return 0;
}
