#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int arr1[] = {1 ,2,3 ,4 ,5}; 
int arr1[] = {10 ,20,30 ,40};

void *sum(void *arg) {
    if(id==1){
    for (int i = 1; i <= 5/2; ++i) {
        cout << "Thread " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    }
    else{
        for (int i = 1; i <= 5/2; ++i) {
        cout << "Thread " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
        cout << "Thread " << id<<endl;
    }
}

int main() {

    cout << "Main: Creating threads...\n";

    pthread_t thread1, thread2;
    int sum1 = 100, sum2 = 500;


    pthread_create(&thread1, NULL, sum, &sum1);
    pthread_create(&thread2, NULL, sum, &sum2);


    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);


    cout << "Main: Both threads completed\n";
    cout<<"Sum of half part first Sum:"<<sum1<<endl;
    cout<<"Sum of second half part first Sum:"<<sum2<<endl;

    return 0;
}