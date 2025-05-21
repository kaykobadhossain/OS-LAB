#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, quantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> quantum;

    int bt[n], at[n], wt[n], tat[n], idx[n], rem_bt[n];
    bool completed[n] = {false}; // Track completed processes

    // Input burst time and arrival time
    for (int i = 0; i < n; ++i) {
        idx[i] = i + 1; // Track process IDs
        cout << "Process " << i + 1 << " Burst Time: ";
        cin >> bt[i];
        cout << "Process " << i + 1 << " Arrival Time: ";
        cin >> at[i];
        rem_bt[i] = bt[i]; // Remaining burst time
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

    // Round Robin Scheduling
    queue<int> ready_queue;
    int current_time = at[sorted_idx[0]]; // Start at first arrival
    int completed_count = 0, next_process = 0;
    double twt = 0, ttat = 0;

    // Initialize queue with first process if arrived
    if (current_time >= at[sorted_idx[0]]) {
        ready_queue.push(sorted_idx[0]);
        next_process++;
    }

    cout << "\nPR\tBT\tAT\tWT\tTAT\n";
    while (completed_count < n) {
        if (ready_queue.empty()) {
            // No process ready; advance time to next arrival
            current_time++;
            // Add arrived processes to queue
            while (next_process < n && at[sorted_idx[next_process]] <= current_time) {
                ready_queue.push(sorted_idx[next_process]);
                next_process++;
            }
            continue;
        }

        // Process the front of the queue
        int curr = ready_queue.front();
        ready_queue.pop();

        // Execute for quantum or remaining burst time
        int exec_time = min(quantum, rem_bt[curr]);
        current_time = max(current_time, at[curr]) + exec_time; // Start at arrival or current time
        rem_bt[curr] -= exec_time;

        // Add arrived processes to queue
        while (next_process < n && at[sorted_idx[next_process]] <= current_time) {
            ready_queue.push(sorted_idx[next_process]);
            next_process++;
        }

        if (rem_bt[curr] > 0) {
            // Process not finished; requeue
            ready_queue.push(curr);
        } else {
            // Process completed
            completed[curr] = true;
            wt[curr] = current_time - at[curr] - bt[curr]; // Waiting time
            tat[curr] = wt[curr] + bt[curr]; // Turnaround time
            twt += wt[curr];
            ttat += tat[curr];
            completed_count++;
            // Output for this process
            cout << "P" << idx[curr] << "\t" << bt[curr] << "\t" << at[curr] << "\t"
                 << wt[curr] << "\t" << tat[curr] << "\n";
        }
    }

    cout << "\nAverage Waiting Time: " << twt / n << "\n";
    cout << "Average Turnaround Time: " << ttat / n << "\n";

    return 0;
}