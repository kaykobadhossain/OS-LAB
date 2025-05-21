#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mutex1, mutex2;

void thread_function(int id) {
    if (id == 1) {
        // Thread 1: Lock mutex1, then try mutex2
        cout << "Thread " << id << ": Acquiring mutex1...\n";
        mutex1.lock();
        cout << "Thread " << id << ": Acquired mutex1\n";

        // Simulate work
        this_thread::sleep_for(chrono::seconds(1));

        cout << "Thread " << id << ": Attempting to acquire mutex2...\n";
        mutex2.lock();
        cout << "Thread " << id << ": Acquired mutex2\n";

        // Critical section
        cout << "Thread " << id << ": In critical section\n";

        mutex2.unlock();
        cout << "Thread " << id << ": Released mutex2\n";
        mutex1.unlock();
        cout << "Thread " << id << ": Released mutex1\n";
    } else {
        // Thread 2: Lock mutex2, then try mutex1
        cout << "Thread " << id << ": Acquiring mutex2...\n";
        mutex2.lock();
        cout << "Thread " << id << ": Acquired mutex2\n";

        // Simulate work
        this_thread::sleep_for(chrono::seconds(1));

        cout << "Thread " << id << ": Attempting to acquire mutex1...\n";
        mutex1.lock();
        cout << "Thread " << id << ": Acquired mutex1\n";

        // Critical section
        cout << "Thread " << id << ": In critical section\n";

        mutex1.unlock();
        cout << "Thread " << id << ": Released mutex1\n";
        mutex2.unlock();
        cout << "Thread " << id << ": Released mutex2\n";
    }
}

int main() {
    cout << "Main: Creating threads...\n";

    // Create threads, passing integer IDs
    thread t1(thread_function, 1);
    thread t2(thread_function, 2);

    cout << "Main: Threads created, waiting for completion...\n";

    // Join threads
    t1.join();
    t2.join();

    cout << "Main: Both threads completed\n";

    return 0;
}