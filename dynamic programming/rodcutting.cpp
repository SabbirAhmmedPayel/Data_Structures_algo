#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to solve the Rod Cutting problem using Dynamic Programming
int rodCutting(vector<int>& prices, int n) {
    vector<int> dp(n + 1, 0); // dp[i] will store the maximum revenue for rod length i

    // Build the dp array iteratively
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            dp[i] = max(dp[i], prices[j - 1] + dp[i - j]);
        }
    }
    return dp[n];
}

int main() {
    int n;
    cout << "Enter the length of the rod: ";
    cin >> n;

    vector<int> prices(n);
    cout << "Enter the prices of rod pieces of length 1 to " << n << ": ";
    for (int i = 0; i < n; i++) {
        cin >> prices[i];
    }

    int maxRevenue = rodCutting(prices, n);
    cout << "The maximum revenue that can be obtained is: " << maxRevenue << endl;

    return 0;
}
