#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();
    
    // DP table, where dp[i][j] means s[0..i-1] matches p[0..j-1]
    vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));

    // Empty pattern matches empty string
    dp[0][0] = true;

    // Handle cases where pattern starts with `*`
    for (int j = 1; j <= n; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];  // Matching 0 occurrence of the previous character
        }
    }

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (p[j - 1] == s[i - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1]; // Single character match
            } else if (p[j - 1] == '*') {
                // Case 1: Match 0 occurrence of the preceding element (i.e., skip `*`)
                dp[i][j] = dp[i][j - 2];
                
                // Case 2: Match 1 or more occurrences (if the previous character matches or is a dot)
                if (p[j - 2] == s[i - 1] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j] || dp[i - 1][j];
                }
            }
        }
    }

    // The result will be stored in dp[m][n], which tells if the whole string matches the whole pattern
    return dp[m][n];
}

int main() {
    string s = "aab";
    string p = "c*a*b";

    if (isMatch(s, p)) {
        cout << "The string matches the pattern." << endl;
    } else {
        cout << "The string does not match the pattern." << endl;
    }

    return 0;
}
