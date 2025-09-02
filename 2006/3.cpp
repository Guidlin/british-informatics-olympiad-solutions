/*
The 2006 British Informatics Olympiad
Question 3: Drats

Time complexity: O(d*s)
Space complexity: O(d*s)

Solved by: guidlin (Elliot Cassidy)
*/

#include <bits/stdc++.h>

using namespace std;

int main(void) {
    // Take inputs
    int s, d;
    cin >> s >> d;

    // Initialise 2D vector to implement tabulation, where the first index represents the depth (number of drats thrown)
    // and the second index represents the number of ways to achieve a score s using those number of drats.
    vector<vector<int>> solutions(d+1, vector<int>(s+1, 0));

    // Calculate the number of ways to achieve a score using one drat.
    for (int i = 1; i <= s; i++)
        if (i % 2 == 0 && i <= 40)
            solutions[1][i] += 1;

    // The number of ways to achieve a score using d drats is equal to the sum of is the sum of solutions[i-1][j-x] 
    // for all valid drat scores x.
    for (int i = 2; i <= d; i++) 
        for (int j = 1; j <= s; j++) 
            for (int k = max(j-20, 0); k < j; k++)
                solutions[i][j] += solutions[i-1][k];
            
    cout << solutions[d][s] << endl; // Print solutions
}