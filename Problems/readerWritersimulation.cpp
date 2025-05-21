#include <iostream>
#include <vector>
using namespace std;

int readCount = 0;
bool writerActive = false;
int writerId = -1;
int readerCounter = 0;
int writerCounter = 0;
vector<int> activeReaders;
vector<int> activeWriters;

void showMenu() {
    cout << "\nChoose an option:\n";
    cout << "1 -> Add reader\n";
    cout << "2 -> Add writer\n";
    cout << "3 -> Quit a reader\n";
    cout << "4 -> Quit writer\n";
    cout << "5 -> Show current status\n";
    cout << "0 -> Exit\n";
    cout << ">> ";
}

void addReader() {
    if (writerActive) {
        cout << "[Reader] denied! A writer is writing right now (Writer " << writerId << ").\n";
        return;
    }

    readerCounter++;
    readCount++;
    activeReaders.push_back(readerCounter);

    if (readCount == 1)
        cout << "[Reader " << readerCounter << "] is the first reader, locking resource...\n";

    cout << ">> [Reader " << readerCounter << "] started reading.\n";
}

void quitReader() {
    if (readCount == 0) {
        cout << "No readers to quit.\n";
        return;
    }

    int id = activeReaders.back();
    activeReaders.pop_back();
    readCount--;

    cout << "<< [Reader " << id << "] finished reading.\n";

    if (readCount == 0) {
        cout << "[Reader " << id << "] was last reader, unlocking resource...\n";
    }
}

void addWriter() {
    if (writerActive || readCount > 0) {
        cout << "[Writer] denied! Either a writer is active or readers are present.\n";
        return;
    }

    writerCounter++;
    writerId = writerCounter;
    writerActive = true;
    activeWriters.push_back(writerId);

    cout << "[Writer " << writerId << "] started writing.\n";
}

void quitWriter() {
    if (!writerActive) {
        cout << "No writer is currently writing.\n";
        return;
    }

    cout << "<< [Writer " << writerId << "] finished writing.\n";
    activeWriters.pop_back();
    writerActive = false;
    writerId = -1;
}

void showStatus() {
    cout << "\n--- Current Status ---\n";
    cout << "Active Readers: ";
    for (int id : activeReaders) cout << id << " ";
    if (activeReaders.empty()) cout << "None";
    cout << "\n";

    if (writerActive)
        cout << "Writer " << writerId << " is writing.\n";
    else
        cout << "No active writer.\n";
    cout << "----------------------\n";
}

int main() {
    int choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                addReader();
                break;
            case 2:
                addWriter();
                break;
            case 3:
                quitReader();
                break;
            case 4:
                quitWriter();
                break;
            case 5:
                showStatus();
                break;
            case 0:
                cout << "Exiting simulation.\n";
                return 0;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}