#include <iostream>
#include <thread>
#include <chrono>

void thread_function(int id) {
    // Simulate some work: print ID and a counter
    for (int i = 1; i <= 5; ++i) {
        std::cout << "Thread " << id << ": Count " << i << "\n";
        // Add a small delay to make output interleaved and readable
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::cout << "Main: Creating threads...\n";

    // Create two threads, passing integer IDs
    std::thread t1(thread_function, 1);
    std::thread t2(thread_function, 2);

    std::cout << "Main: Threads created, waiting for completion...\n";

    // Join threads to wait for completion
    t1.join();
    t2.join();

    std::cout << "Main: Both threads completed\n";

    return 0;
}