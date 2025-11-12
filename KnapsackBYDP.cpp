#include <iostream>
using namespace std;

// 0/1 Knapsack using Dynamic Programming
int knapsack(int n, int W, int value[], int weight[]) {

    int dp[25][105];   // dp[i][w] = max value using first i items with capacity w

    // Build DP table
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {

            // Base cases
            if (i == 0 || w == 0) {
                dp[i][w] = 0;
            }

            // If item fits
            else if (weight[i - 1] <= w) {
                dp[i][w] = max(
                    value[i - 1] + dp[i - 1][w - weight[i - 1]],   // take item
                    dp[i - 1][w]                                    // don't take
                );
            }

            // If item does not fit
            else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][W];  // max value possible
}

int main() {

    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    int value[25], weight[25];

    cout << "Enter values of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> value[i];
    }

    cout << "Enter weights of items:\n";
    for (int i = 0; i < n; i++) {
        cin >> weight[i];
    }

    cout << "Enter maximum capacity of knapsack: ";
    cin >> W;

    int maxValue = knapsack(n, W, value, weight);

    cout << "\nMaximum value in knapsack = " << maxValue << endl;

    return 0;
}
