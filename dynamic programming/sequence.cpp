#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int sequenceAlignment(const string& X, const string& Y, int gapPenalty, int mismatchPenalty) {
    int m = X.length();
    int n = Y.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Initialize DP table
    for (int i = 0; i <= m; i++) dp[i][0] = i * gapPenalty;
    for (int j = 0; j <= n; j++) dp[0][j] = j * gapPenalty;

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int match = dp[i - 1][j - 1] + (X[i - 1] == Y[j - 1] ? 0 : mismatchPenalty);
            int insert = dp[i][j - 1] + gapPenalty;
            int del = dp[i - 1][j] + gapPenalty;
            dp[i][j] = min({match, insert, del});
        }
    }
    return dp[m][n];
}

int main() {
    string X, Y;
    int gapPenalty, mismatchPenalty;

    cout << "Enter the first string: ";
    cin >> X;
    cout << "Enter the second string: ";
    cin >> Y;
    cout << "Enter the gap penalty: ";
    cin >> gapPenalty;
    cout << "Enter the mismatch penalty: ";
    cin >> mismatchPenalty;

    int result = sequenceAlignment(X, Y, gapPenalty, mismatchPenalty);
    cout << "The minimum alignment cost is: " << result << endl;

    return 0;
}
