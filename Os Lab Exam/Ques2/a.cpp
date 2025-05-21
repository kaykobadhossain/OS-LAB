#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <thread>
#include <mutex>
#include <chrono>
using namespace std;

mutex mutex1, mutex2;


int accountA = 500; // Initial balance of account A
int accountB = 0; // Initial balance of account B


void *transfer(void *arg) {
    int amount = *((int *)arg);

    mutex2.lock();

    if (accountA >= amount) {

        mutex1.lock();

        sleep(1); // Some preemption delay by other thread
        accountA -= amount;
        accountB += amount;

        mutex1.unlock();

    }

mutex2.unlock();

printf("Transfer %d: A=%d, B=%d (Total: %d)\n",
amount, accountA, accountB, accountA + accountB);
return NULL;
}


int main() {
pthread_t thread1, thread2;
int amount1 = 100, amount2 = 500;


pthread_create(&thread1, NULL, transfer, &amount1);
pthread_create(&thread2, NULL, transfer, &amount2);


pthread_join(thread1, NULL);
pthread_join(thread2, NULL);

printf("Final balances: A=%d, B=%d (Total: %d)\n",
accountA, accountB, accountA + accountB);
return 0;
}
