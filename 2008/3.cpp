/*
The 2008 British Informatics Olympiad
Question 3: Shirts

Time complexity: O(n!), however it is effectively O(1) as n is fixed at 7.
Space complexity: O(n!), however it is effectively O(1) as n is fixed at 7.

Solved by: guidlin (Elliot Cassidy)
*/

// This problem requires us to find the minimum number of steps to order an array of numbers from 1 to 7 starting
// from the numbers being in a random order. Each step consists of one of four operations which are described in
// the question. This naturally induces a tree representation, with tree depth corresponding to the number of operations 
// performed. This means we are looking for the shallowest occurrence of a state where the numbers are in order. This
// allows us to use BFS (Competitive Programmer's Handbook p.119), which is much more efficient than DFS (Competitive 
// Programmer's Handbook p.117) in this instance.

#include <bits/stdc++.h>

using namespace std;

// The following functions represent the four operations that can be performed on a set of shirts:

// Helper function that moves the first element to the middle, shifting the remaining first three elements to the left.
string operation_1(string order) {
    int tmp = order[0];
    for (int i = 0; i < 3; i++) 
        order[i] = order[i+1];
    order[3] = tmp;
    return order;
}

// Helper function that moves the last element to the middle, shifting the remaining last three elements to the right.
string operation_2(string order) {
    int tmp = order[6];
    for (int i = 7; i > 3; i--)
        order[i] = order[i-1];
    order[3] = tmp;
    return order;
}

// Helper function that moves the middle element to the start, shifting the first three elements to the right.
string operation_3(string order) {
    int tmp = order[3];
    for(int i = 3; i > 0; i--) {
        order[i] = order[i-1];
    }
    order[0] = tmp;
    return order;
}

// Helper function that moves the middle element to the end, shifting the last three elements to the left.
string operation_4(string order) {
    int tmp = order[3];
    for (int i = 3; i < 7; i++) 
        order[i] = order[i+1];
    order[6] = tmp;
    return order;
}

int main(void) {
    // Take input
    string x;
    cin >> x;

    // Breadth-first search (Competitive Programmer's Handbook p.119):
    queue<pair<string, int>> q; // Pair represents the state of the shirts and the depth (number of operations).
    unordered_set<string> visited; 
    q.push({x, 0});

    int d = -1; // Variable that stores the depth of the shallowest occurrence of the shirts being in order.
    while (true) {
        pair<string,int> s = q.front();
        q.pop();
        if (s.first == "1234567") {
            // If the shirts are in order, then we have found the shallowest solution and can say the shallowest occurrence
            // of the shirts being in order occurs at the current depth.
            d = s.second;
            break;
        }
        // Array that stores the state after the four operations have been performed on the current state.
        string operations[4] = {operation_1(s.first), operation_2(s.first), operation_3(s.first), operation_4(s.first)}; 
       
        for (int i = 0; i < 4; i++) {
            // As each operation performed on the current state can be considered as a child node on a graph, we can append
            // it to the end of the queue, with an incremented depth. If one of these child nodes has already been explored,
            // it will lead us down a path that has already been visited and should not be re-visited.
            if (visited.count(operations[i]))
                continue;
            q.push({operations[i], s.second+1});
            visited.insert(operations[i]);
        }
    }

    cout << d << endl; // Print solution
}