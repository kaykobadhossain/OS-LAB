#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

using namespace std;

// বাফারের সর্বোচ্চ সাইজ
const int BUFFER_SIZE = 5;
queue<int> buffer; // শেয়ারড বাফার
mutex mtx; // মিউটেক্স লক
condition_variable not_full, not_empty; // কন্ডিশন ভেরিয়েবল

// প্রডিউসার ফাংশন
void producer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        // বাফার পূর্ণ হলে অপেক্ষা করো
        not_full.wait(lock, [] { return buffer.size() < BUFFER_SIZE; });
        
        // ডেটা তৈরি ও বাফারে রাখো
        buffer.push(i);
        cout << "Producer " << id << " producing the data: " << i << endl;
        
        lock.unlock();
        not_empty.notify_one(); // কনজিউমারকে জানাও
        this_thread::sleep_for(chrono::milliseconds(1000)); // সিমুলেশনের জন্য ডিলে
    }
}

// কনজিউমার ফাংশন
void consumer(int id) {
    for (int i = 0; i < 10; ++i) {
        unique_lock<mutex> lock(mtx);
        // বাফার খালি হলে অপেক্ষা করো
        not_empty.wait(lock, [] { return !buffer.empty(); });
        
        // বাফার থেকে ডেটা নাও
        int data = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed the data: " << data << endl;
        
        lock.unlock();
        not_full.notify_one(); // প্রডিউসারকে জানাও
        this_thread::sleep_for(chrono::milliseconds(2000)); // সিমুলেশনের জন্য ডিলে
    }
}

int main() {
    // শুরুতে বাফারে ৩টি প্রোডাক্ট পুশ করা
    {
        lock_guard<mutex> lock(mtx); // মিউটেক্স লক করে নিরাপদে পুশ করা
        buffer.push(100);
        buffer.push(200);
        buffer.push(300);
        cout << "First Added 3 products: 100, 200, 300" << endl;
    }
    not_empty.notify_one(); // কনজিউমারকে জানানো হলো যে বাফারে ডেটা আছে
    // প্রডিউসার এবং কনজিউমার থ্রেড তৈরি
    thread prod(producer, 1);
    thread cons(consumer, 1);
    
    // থ্রেডগুলো শেষ হওয়ার জন্য অপেক্ষা
    prod.join();
    cons.join();
    
    return 0;
}