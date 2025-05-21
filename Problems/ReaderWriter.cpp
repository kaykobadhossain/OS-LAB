#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

using namespace std;

mutex mtx;
mutex readCountMutex;
int readCount = 0;

void reader(int id) {
    while (true) {
        cout << "[Reader " << id << "] trying to read...\n";
        
        // Entry section for reader
        readCountMutex.lock();
        readCount++;
        if (readCount == 1) {
            cout << "[Reader " << id << "] is the first reader, locking resource...\n";
            mtx.lock(); // first reader locks resource for writers
        }
        readCountMutex.unlock();

        // Reading section
        cout << ">> [Reader " << id << "] started reading.\n";
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "<< [Reader " << id << "] finished reading.\n";

        // Exit section for reader
        readCountMutex.lock();
        readCount--;
        if (readCount == 0) {
            cout << "[Reader " << id << "] was last reader, unlocking resource...\n";
            mtx.unlock(); // last reader unlocks resource for writers
        }
        readCountMutex.unlock();

        this_thread::sleep_for(chrono::milliseconds(800)); // Pause before next attempt
    }
}

void writer(int id) {
    while (true) {
        cout << "\n[Writer " << id << "] wants to write...\n";

        mtx.lock(); // Writer locks the resource
        cout << "\t>> [Writer " << id << "] started writing.\n";
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "\t<< [Writer " << id << "] finished writing.\n";
        mtx.unlock();

        this_thread::sleep_for(chrono::milliseconds(1200)); // Pause before next attempt
    }
}

int main() {
    vector<thread> readers, writers;

    for (int i = 0; i < 3; ++i)
        readers.push_back(thread(reader, i + 1));
    for (int i = 0; i < 2; ++i)
        writers.push_back(thread(writer, i + 1));

    for (auto &r : readers) r.join();
    for (auto &w : writers) w.join();

    return 0;
}
