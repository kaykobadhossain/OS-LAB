#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    int bt[n], at[n], wt[n], tat[n], priority[n], idx[n];
    bool completed[n] = {false}; // Track completed processes
    int temp[n + 1]; // For completion times

    // Input burst time, arrival time, and priority
    for (int i = 0; i < n; ++i) {
        idx[i] = i + 1; // Track process IDs
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> at[i];
        cout << "Process " << i + 1 << " Priority (lower number = higher priority): ";
        cin >> priority[i];
    }

    // Sort by arrival time to process in order of arrival
    int sorted_idx[n];
    for (int i = 0; i < n; ++i) sorted_idx[i] = i;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (at[sorted_idx[j]] > at[sorted_idx[j + 1]]) {
                swap(sorted_idx[j], sorted_idx[j + 1]);
            }
        }
    }

    // Priority Scheduling
    int current_time = at[sorted_idx[0]]; // Start at first arrival
    int completed_count = 0;
    double twt = 0, ttat = 0;

    cout << "\nPR\tBT\tAT\tPriority\tWT\tTAT\n";
    while (completed_count < n) {
        // Find the process with highest priority (lowest priority number) among arrived processes
        int min_priority = 1e9, min_idx = -1;
        for (int i = 0; i < n; ++i) {
            if (!completed[i] && at[i] <= current_time && priority[i] < min_priority) {
                min_priority = priority[i];
                min_idx = i;
            }
        }

        if (min_idx == -1) {
            // No process ready; advance time to next arrival
            current_time++;
            continue;
        }

        // Process the selected process
        completed[min_idx] = true;
        temp[completed_count] = max(at[min_idx], current_time); // Start time
        wt[min_idx] = temp[completed_count] - at[min_idx]; // Waiting time
        tat[min_idx] = wt[min_idx] + bt[min_idx]; // Turnaround time
        current_time = temp[completed_count] + bt[min_idx]; // Update current time
        twt += wt[min_idx];
        ttat += tat[min_idx];

        // Output for this process
        cout << "P" << idx[min_idx] << "\t" << bt[min_idx] << "\t" << at[min_idx] << "\t"
             << priority[min_idx] << "\t\t" << wt[min_idx] << "\t" << tat[min_idx] << "\n";

        completed_count++;
    }

    cout << "\nAverage Waiting Time: " << twt / n << "\n";
    cout << "Average Turnaround Time: " << ttat / n << "\n";

    return 0;
}