#include <iostream>
#include <algorithm>
using namespace std;

const int MAX = 10;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    if (n > MAX) {
        cout << "Error: Number of processes exceeds maximum limit (" << MAX << ").\n";
        return 1;
    }

    int bt[MAX], at[MAX], wt[MAX], tat[MAX], idx[MAX];
    int temp[MAX + 1]; // For completion times

    // Input burst time and arrival time
    for (int i = 0; i < n; ++i) {
        idx[i] = i + 1; // Track process IDs
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> at[i];
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (at[j] > at[j + 1]) {
                swap(at[j], at[j + 1]);
                swap(bt[j], bt[j + 1]);
                swap(idx[j], idx[j + 1]);
            }
        }
    }

    // Calculate waiting time and turnaround time
    temp[0] = at[0]; // Start at first process's arrival time
    wt[0] = 0;
    tat[0] = bt[0];
    double twt = 0, ttat = tat[0];

    for (int i = 1; i < n; ++i) {
        temp[i] = max(at[i], temp[i - 1] + bt[i - 1]); // Start time
        wt[i] = temp[i] - at[i]; // Waiting time
        tat[i] = wt[i] + bt[i];  // Turnaround time
        twt += wt[i];
        ttat += tat[i];
    }

    // Output results
    cout << "\nPR\tBT\tAT\tWT\tTAT\n";
    for (int i = 0; i < n; ++i) {
        cout << "P" << idx[i] << "\t" << bt[i] << "\t" << at[i] << "\t" << wt[i] << "\t" << tat[i] << "\n";
    }
    cout << "\nAverage Waiting Time: " << twt / n << "\n";
    cout << "Average Turnaround Time: " << ttat / n << "\n";

    return 0;
}