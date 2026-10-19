#include <iostream>
using namespace std;

int main() {
    int n, W;
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter truck capacity: ";
    cin >> W;

    int weight[100], utility[100];

    cout << "Enter weight and utility of each item:\n";
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> weight[i] >> utility[i];
    }

    int dp[101][1001];

    // Initialize DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = 0;
        }
    }

    // Dynamic Programming
    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (weight[i - 1] <= w) {
                int include = utility[i - 1] +
                              dp[i - 1][w - weight[i - 1]];
                int exclude = dp[i - 1][w];
                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    cout << "\nMaximum Utility = " << dp[n][W] << endl;

    // Find selected items
    int w = W;
    cout << "Selected Items:\n";
    for (int i = n; i > 0; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            cout << "Item " << i
                 << " (Weight = " << weight[i - 1]
                 << ", Utility = " << utility[i - 1] << ")\n";
            w -= weight[i - 1];
        }
    }

    return 0;
}