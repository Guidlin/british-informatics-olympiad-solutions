/*
The 2002 British Informatics Olympiad
Question 1: Lojban

Time complexity: O(n)
Space complexity: O(n)

Solved by: guidlin (Elliot Cassidy)
*/

#include <bits/stdc++.h>

using namespace std;

int search(vector<string> list, string target) {
    // Helper function that finds the first instance of target within a list using a linear search.
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == target) return i;
    }

    return -1; // Return -1 if target not found.
}

int main(void) {
    string s;
    cin >> s;

    // numbers[i] corresponds to the name of the number i in Lojban.
    vector<string> numbers = {"no", "pa", "re", "ci", "vo", "mu", "xa", "ze", "bi", "so"};

    string result = ""; // Each digit is appended to this string.
    for (int i = 0; i < s.length() / 2; i++) {
        // The length of s is guaranteed to be a multiple of 2.
        // Therefore, we can take each 2 letter substring, which represents 1 digit in
        // Lojban and search for its index within the numbers array, which corresponds to
        // the actual value of the digit in Lojban. Then, we convert this to a string and
        // append it to the result.
        result.append(to_string(search(numbers, s.substr(2*i, 2))));
    }

    cout << result << endl;
}