/*
The 2010 British Informatics Olympiad
Question 3: Juggl(ug)ing

Time complexity: O(A*B*C), where A, B and C represent the capacity of each jug.
Space complexity: O(A*B*C), where A, B and C represent the capacity of each jug.

Solved by: guidlin (Elliot Cassidy)
*/

// This problem requires us to find the minimum number of steps to end with exactly n ounces in any jug, 
// starting from all jugs being empty. Each step consists of one of three operations: filling a jug, emptying
// a jug and pouring one jug into another until either the source is empty or the destination is full. This
// naturally induces a tree representation, with tree depth corresponding to the number of operations performed.
// This means we are looking for the shallowest occurence of a jug filled with n ounces of water. This allows us
// to use BFS (Competitive Programmer's Handbook p.119), which is much more efficient than DFS (Competitive 
// Programmer's Handbook p.117) in this instance.


#include <bits/stdc++.h>

using namespace std;

int capacities[3];

// This is a helper function that translates a vector into a string so that it can be hashed for storage in an unordered_set.
string translate(vector<int> volumes) {
    string result = "";
    for (int i : volumes)
        result += to_string(i)+",";
    return result;
}


// This is a helper function that checks whether or not there is a jug filled with n ounces in a set of jugs -- this checks whether
// or not the problem has been solved.
bool check(vector<int> volumes, int n) {
    for (int i : volumes)
        if (i == n)
            return true;
    return false;
}

// The following functions represent the three operations that can be performed on a set of jugs:

// Helper function that fills the jug at index x.
vector<int> fill(int x, vector<int> volumes) {
    volumes[x] = capacities[x];
    return volumes;
}


// Helper function that empties the jug at index x.
vector<int> empty(int x, vector<int> volumes) {
    volumes[x] = 0;
    return volumes;
}

// Helper function that completely pours the contents of one jug into another, until either the source is empty 
// or the destination is full.
vector<int> pour(int pourer, int pouree, vector<int> volumes) {
    int diff = capacities[pouree] - volumes[pouree];
    int amount = min(diff, volumes[pourer]);
    volumes[pourer] -= amount;
    volumes[pouree] += amount;
    return volumes;
}

int main(void) {
    // Take inputs
    int j, n;
    cin >> j >> n;
    vector<int> volumes(j, 0);
    for (int i = 0; i < j; i++) {
        cin >> capacities[i];
    }

    // Breadth-first search (Competitive Programmer's Handbook p.119):
    queue<pair<vector<int>, int>> q; // Pair represents the state of the jugs and the depth (number of operations).
    unordered_set<string> visited;
    q.push({volumes, 0});

    int depth = -1; // Variable that stores the depth of the shallowest occurence of a jug filled with n ounces of water.
    while (!q.empty()) {
        auto [f, d] = q.front();
        q.pop();

        if (check(f, n)) {
            // If the there is a jug filled with n ounces of water, then we have found the shallowest solution and can
            // say that the shallowest occurence of a jug filled with n ounces of water is at the current depth.
            depth = d;
            break;
        }
        
        // This loop generates all the possible subsequent moves from the current state by iterating through each jug of the
        // current state and performing every single operation possible on it. If an operation being performed on a jug leads
        // us down an already explored path, we do not visit it.
        for (int i = 0; i < j; i++) {
            vector<int> filled = fill(i, f);
            if (!visited.count(translate(filled))) {
                q.push({filled, d+1});
                visited.insert(translate(filled));
            }
                
            vector<int> emptied = empty(i, f);
            if (!visited.count(translate(emptied))) {
                q.push({emptied, d+1});
                visited.insert(translate(emptied));
            }
                
            for (int k = 0; k < j; k++) {
                // This iterates through every jug that is not jug i, pouring the water from jug i into jug k.
                if (k == i) continue;
                vector<int> poured = pour(i, k, f);
                if (!visited.count(translate(poured))) {
                    q.push({poured, d+1});
                    visited.insert(translate(poured));
                }
            }
        }
    }

    cout << depth << endl; // Print solution
}