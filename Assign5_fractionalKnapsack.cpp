#include <iostream>
using namespace std;

struct Item 
{
    double value;
    double weight;
};

// Function to calculate maximum value in knapsack
double fractionalKnapsack(Item items[], int n, double capacity) 
{
    double ratio[50];  // To store value/weight ratio
    int i, j;

    // Step 1: Calculate value/weight ratio
    for (i = 0; i < n; i++) 
    {
        ratio[i] = items[i].value / items[i].weight;
    }

    // Step 2: Sort items in descending order of ratio
    for (i = 0; i < n - 1; i++) 
    {
        for (j = i + 1; j < n; j++) 
        {
            if (ratio[i] < ratio[j]) 
            {
                double tempRatio = ratio[i];
                ratio[i] = ratio[j];

                Item temp = items[i];
                items[i] = items[j];
                items[j] = temp;
            }
        }
    }

    // Step 3: Select items for the knapsack
    double remaining = capacity;
    double totalValue = 0;

    for (i = 0; i < n; i++) {
        if (items[i].weight <= remaining) 
        {
            // Take full item
            totalValue += items[i].value;
            remaining -= items[i].weight;
        } 
        else 
        {
            // Take fraction of the item
            totalValue += ratio[i] * remaining;
            break;
        }
    }

    return totalValue;
}

int main() 
{
    int n;
    double capacity;

    cout << "Enter number of items: ";
    cin >> n;

    Item items[n];
    cout << "Enter value and weight of each item:\n";
    for (int i = 0; i < n; i++) 
    {
        cout << "Item " << i + 1 << ":\n";
        cout << "Value: ";
        cin >> items[i].value;
        cout << "Weight: ";
        cin >> items[i].weight;
    }

    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    double maxValue = fractionalKnapsack(items, n, capacity);
    cout << "\nMaximum value that can be obtained = " << maxValue << endl;

    return 0;
}