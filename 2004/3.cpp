/*
The 2004 British Informatics Olympiad
Question 3: Morse Code

Time complexity: O(4^n)
Space complexity: O(n)

Solved by: guidlin (Elliot Cassidy)
*/

// In this problem, we are given a string p and are asked how many other strings with the same length carry the same Morse code representation as p. 

#include <bits/stdc++.h>

using namespace std;

// Define array that maps each letter in the English alphabet to its corresponding Morse code represenation.
string dictionary[26] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

// Function that encodes English plaintext string to Morse code.
string translate(string plaintext) {
    string result = "";
    for (char p : plaintext) {
        result.append(dictionary[((int) p)-97]);
    }
    return result;
}

// Function that checks if a section of a string is valid Morse code.
bool is_valid_code(string x) {
    for (string i : {"..--", ".-.-", "---.", "----"}) 
        if (i == x) return false;
    return true;
}

// Traverse the Morse string from left to right. At each position, we consider all possible segments of the next 
// 1, 2, 3 or 4 characters since all valid Morse code letters fall within this length. 
int solutions = 0;
void solve(string n, int maxLength) {
    if (n.size() == 0 && maxLength == 0) {
        // The Morse string is empty, with the correct number of letters, which is counted as one valid interpretation.
        solutions++;
        return; 
    } else if (maxLength == 0) 
        // The number of chunks we have used exceeds the number of characters in the input.
        return;

    for (int i = 1; i <= 4; i++) {
        // The length of the segment exceeds the length of the remaining Morse string. 
        if (i > n.size()) 
            break;
        
            // The problem states that four combinations of dots and dashes are invalid; check that the segment is a valid Morse letter and not one of these.
        if (!is_valid_code(n.substr(0, i))) 
            break; 
        
            // Each time we find a valid segment, we recursively process the remainder of the string.
        solve(n.substr(i), maxLength-1);
    }
}

int main(void) {
    string p;
    cin >> p;
    solve(translate(p), p.length());
    cout << solutions << endl;
}