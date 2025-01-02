#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to find the length of LCS using DP table
int lcs(string X, string Y) {
    int m = X.length();
    int n = Y.length();

    // Create a DP table to store the lengths of LCS
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1; // If characters match
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]); // If they don't match
            }
        }
    }

    // The length of the longest common subsequence
    return dp[m][n];
}

int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    
    cout << "Length of LCS: " << lcs(X, Y) << endl;
    return 0;
}
