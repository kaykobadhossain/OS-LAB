#include <iostream>
#include <vector>
using namespace std;

// বাফার এবং সম্পর্কিত ভেরিয়েবল
const int BUFFER_SIZE = 5;
vector<int> buffer; // শেয়ারড বাফার
int producerCounter = 0; // Producer আইডি কাউন্টার
int consumerCounter = 0; // Consumer আইডি কাউন্টার
vector<int> activeProducers; // সক্রিয় Producerদের তালিকা
vector<int> activeConsumers; // সক্রিয় Consumerদের তালিকা

// মেনু প্রদর্শন ফাংশন
void showMenu() {
    cout << "\nSelect Options:\n";
    cout << "1 -> Produce \n";
    cout << "2 -> Consume \n";
    cout << "0 -> Quit \n";
    cout << ">> ";
}

// Producer যোগ ফাংশন
void addProducer() {
    if (buffer.size() >= BUFFER_SIZE) {
        cout << "[Producer] rejected! Buffer full\n";
        return;
    }

    producerCounter++;
    activeProducers.push_back(producerCounter);
    
    // বাফারে ডেটা যোগ করা
    int data = producerCounter * 100; // প্রতিটি Producerের জন্য ইউনিক ডেটা
    buffer.push_back(data);
    
    cout << ">> [producer " << producerCounter << "] added a product: " << data << endl;
}

// Consumer যোগ ফাংশন
void addConsumer() {
    if (buffer.empty()) {
        cout << "[Consumer] don not get the product! Buffer empty Visit Later\n";
        return;
    }

    consumerCounter++;
    activeConsumers.push_back(consumerCounter);
    
    // বাফার থেকে ডেটা নেওয়া
    int data = buffer.front();
    buffer.erase(buffer.begin());
    
    cout << ">> [Consumer " << consumerCounter << "] data: " << data << endl;
}
int main() {
    int choice;

    // শুরুতে বাফারে ৩টি প্রাথমিক ডেটা যোগ করা
    buffer.push_back(100);
    buffer.push_back(200);
    buffer.push_back(300);
    cout << "first the buffer value: 100, 200, 300\n";

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addProducer();
                break;
            case 2:
                addConsumer();
                break;
            case 0:
                cout << "Quit\n";
                return 0;
            default:
                cout << "Invalid\n";
        }
    }
}