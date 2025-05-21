#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

std::mutex mtx;
std::condition_variable cv;
int readCount = 0;
bool writerActive = false;

void reader(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[Reader " << id << "] trying to read...\n";

    cv.wait(lock, [] { return !writerActive; }); // Wait if a writer is active

    readCount++;
    std::cout << ">> [Reader " << id << "] started reading. (Active Readers: " << readCount << ")\n";

    lock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate reading
    lock.lock();

    readCount--;
    std::cout << "<< [Reader " << id << "] finished reading.\n";
    if (readCount == 0) {
        std::cout << "[Reader " << id << "] was last reader, notifying writers...\n";
        cv.notify_all();
    }

    lock.unlock();
}

void writer(int id) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "[Writer " << id << "] wants to write...\n";

    cv.wait(lock, [] { return readCount == 0 && !writerActive; });

    writerActive = true;
    std::cout << ">> [Writer " << id << "] started writing.\n";

    lock.unlock();
    std::this_thread::sleep_for(std::chrono::seconds(3)); // Simulate writing
    lock.lock();

    writerActive = false;
    std::cout << "<< [Writer " << id << "] finished writing.\n";
    cv.notify_all();

    lock.unlock();
}

int main() {
    std::vector<std::thread> threads;
    int choice, id = 1;

    while (true) {
        std::cout << "\n1. Add Reader\n2. Add Writer\n3. Exit\nEnter choice: ";
        std::cin >> choice;

        if (choice == 1) {
            threads.push_back(std::thread(reader, id++));
        } else if (choice == 2) {
            threads.push_back(std::thread(writer, id++));
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }

    for (auto &t : threads)
        if (t.joinable())
            t.join();

    return 0;
}
