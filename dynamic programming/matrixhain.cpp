#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Function to find the minimum number of scalar multiplications using DP
int matrixChainOrder(vector<int>& dims) {
    int n = dims.size();
    
    // dp[i][j] will store the minimum number of scalar multiplications
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // Chain length L from 2 to n-1
    for (int L = 2; L < n; L++) {
        for (int i = 1; i < n - L + 1; i++) {
            int j = i + L - 1;
            dp[i][j] = INT_MAX;

            // Try all possible places to split the chain
            for (int k = i; k < j; k++) {
                int q = dp[i][k] + dp[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                dp[i][j] = min(dp[i][j], q);
            }
        }
    }

    // The minimum number of multiplications is stored in dp[1][n-1]
    return dp[1][n - 1];
}

int main() {
    vector<int> dims = {1, 2, 3, 4, 3};
    
    cout << "Minimum number of multiplications: " << matrixChainOrder(dims) << endl;
    return 0;
}
