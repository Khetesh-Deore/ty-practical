#include <iostream>
#include <algorithm>
using namespace std;

struct Item 
{
    int value, weight;
    double ratio;
};

// Comparison function
bool cmp(Item a, Item b)
{
    return a.ratio > b.ratio;
}

// For tracking best combination
int bestInclude[50];  // stores best selection (1/0)
int includeSet[50];   // temporary include array

double bound(int i, int w, int p, int n, int W, Item arr[])
{
    if (w >= W) return 0;
    double result = p;
    int tw = w;
          
    while (i < n && tw + arr[i].weight <= W)
    {
        tw += arr[i].weight;
        result += arr[i].value;
        i++;
    }

    if (i < n)
        result += (W - tw) * arr[i].ratio;

    return result;
}

// Recursive Branch and Bound with item tracking
void knapsack(int i, int w, int p, int &maxProfit, int n, int W, Item arr[])
{
    if (i == n) return;

    double ub = bound(i, w, p, n, W, arr);

    if (ub <= maxProfit) return;

    // Include current item if possible
    if (w + arr[i].weight <= W)
    {
        includeSet[i] = 1;

        int newProfit = p + arr[i].value;
        if (newProfit > maxProfit)
        {
            maxProfit = newProfit;
            // Save current best combination
            for (int k = 0; k < n; k++)
                bestInclude[k] = includeSet[k];
        }

        knapsack(i + 1, w + arr[i].weight, newProfit, maxProfit, n, W, arr);

        includeSet[i] = 0; // backtrack
    }

    // Exclude current item
    knapsack(i + 1, w, p, maxProfit, n, W, arr);
}

int main()
{
    int n, W;
    cout << "Enter the number of campaigns: ";
    cin >> n;

    Item arr[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Enter reach value of campaign " << i + 1 << ": ";
        cin >> arr[i].value;
        cout << "Enter cost of campaign " << i + 1 << ": ";
        cin >> arr[i].weight;
        arr[i].ratio = (double)arr[i].value / arr[i].weight;
    }

    cout << "Enter total budget: ";
    cin >> W;

    sort(arr, arr + n, cmp);

    int maxProfit = 0;
    for (int i = 0; i < n; i++)
    {
        includeSet[i] = 0;
        bestInclude[i] = 0;
    }

    knapsack(0, 0, 0, maxProfit, n, W, arr);

    // Display results
    int totalCost = 0;
    cout << "\nSelected Campaigns:\n";
    for (int i = 0; i < n; i++)
    {
        if (bestInclude[i] == 1)
        {
            cout << "Campaign " << i + 1
                 << " (Cost: " << arr[i].weight
                 << ", Reach: " << arr[i].value << ")\n";
            totalCost += arr[i].weight;
        }
    }

    cout << "\nTotal Cost Used: " << totalCost;
    cout << "\nMaximum Reach Achieved: " << maxProfit << endl;

    return 0;
}
