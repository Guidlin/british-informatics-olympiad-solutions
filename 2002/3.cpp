/*
The 2002 British Informatics Olympiad
Question 3: Mops

Time complexity: O(n^(3/2))
Space complexity: O(n)

Solved by: guidlin (Elliot Cassidy)
*/

// This problem effectively asks us what the least number of 1s we can use in order to express a value.
// As we can use the operations of addition and multiplication, it would make sense to find the closest
// number to the target (the number that we are being asked to express as 1s) that is not prime, i.e.
// that can be divided into 2 numbers that are not 1 and itself.

// In order to solve this problem, we use memoisation (Competitive Programmer's Handbook p.65). This
// means we create a vector (dynamic array) of size n (the target), where each index i is the shortest possible way
// to express the number using only 1s. Hereon out, I will refer to the number of 1s used to express a number
// as its "length".


#include <bits/stdc++.h>

using namespace std;

vector<int> expressions; // expressions[i] stores the minimum length of i.

// This is a helper function that finds the two divisors of a number x that can be expressed with the shortest length.
pair<int, int> optimal_divisor(int x) {
    int optimal = -1, minimum = 99999999, lastVisited = -1; // Variables that store: the factor of x that can be used to express x with the shortest length, the shortest length, the last factor that has been visited.
    // This loop 
    for (int i = 2; i < x; i++) {
        if (x % i == 0) {
            if (lastVisited == x/i) break; // If we have visited a factor that has already been visited, all possible factors have been visited.
            lastVisited = i; 

            // The length required to express x as two factors a and b, will be length(a)+length(b) as x = a * b.
            // This means that in order to get the length required to express x, I can just add the minimum length 
            // required in order to express the two factors of x (a and b) together.
            int length = expressions[i-1] + expressions[(x/i) - 1]; 
            if (length < minimum) {
                // In the case that the combined length of a and b is shorter than the pre-existing minimum length
                // to express x as two factors, update the value for the factor that can be used to express x with
                // the shortest length, and the minimum length required to express x.
                optimal = i;
                minimum = length;
            }
        }
    }
    return {optimal, minimum}; // Return the value of the optimal factor to express x and the length of this factor.
}

// This is the function that actually fills the expressions vector (which contains the minimum length to express i-1, where i is the
// index of the vector). 
void solve(int n) {
    for (int i = 0; i < n; i++) {
        if (i == 0) expressions.push_back(1); // This is the base case: if we are expressing the number 1, we only require a length of 1.
        else {
            auto [od, length] = optimal_divisor(i+1); // Unpack the integer pair of the optimal divisor and the minimum length required to express i.
            int incremented = expressions[i-1]+1; // The length of i can also be expressed as one plus the length of i-1 (expression[i-1]+1). 
            if (od == -1 || length > incremented) {
                // If the number in question was prime or the mop expression of i is shorter by just adding another 1 to the previous mop expression
                // rather than multiplying the optimal factors together, the shortest way to express i would be to add another 1 onto the expression
                // of i-1.
                expressions.push_back(expressions[i-1]+1);
            } else {
                // Otherwise, the minimum length is given by multiplying the optimal factors together.
                expressions.push_back(length);
            }
        }
    }
}

int main(void) {
    // Take inputs
    int n;
    cin >> n;
    solve(n); // Call the function that populates the vector.
    cout << expressions[n-1] << endl; // The last index in the vector will be our solution.
}