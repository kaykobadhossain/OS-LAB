#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

int n=5;
int arr[]={1,2,3,4,5};
int arr[]={10,20,30,40};
int sum1=0,sum2=0;

mutex mutex1, mutex2;

void thread_function(int id) {
    if (id == 1) {
        cout<<"thread"<<id<<"running"<<endl;
        for (int i = 1; i <= 5/2; ++i) {
        cout << "Thread " << id << endl;
        sum1+=arr[i];
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    } else {
        cout<<"thread"<<1<<endl;
        cout << "Thread " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

int main() {
    cout << "Main: Creating threads...\n";

    thread t1(thread_function, 1);
    thread t2(thread_function, 2);

    cout << "Main: Threads created, waiting for completion...\n";

    // Join threads
    t1.join();
    t2.join();

    cout << "Main: Both threads completed\n";

    return 0;
}