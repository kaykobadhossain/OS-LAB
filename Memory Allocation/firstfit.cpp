#include <iostream>
using namespace std;

void BestFit(int blockSize[], int m, int processSize[], int n)
{
    int allocation[n];

    for(int i = 0; i < n; i++)
        allocation[i] = -1; // initially not allocated

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(blockSize[j] >= processSize[i])
            {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    cout << "\nProcess\t\tSize\t\tAllocated Block\n";
    for(int i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << processSize[i] << "\t\t";
        if(allocation[i] != -1)
            cout << allocation[i] + 1  << endl;
        else
            cout << "Not Allocated" << endl;
    }
}

int main()
{
    int m, n, blockSize[10], processSize[10];
    cout << "Enter number of blocks: ";
    cin >> m;
    cout << "Enter block sizes:\n";
    for(int i = 0; i < m; i++)
        cin >> blockSize[i];

    cout << "Enter number of processes: ";
    cin >> n;
    cout << "Enter process sizes:\n";
    for(int i = 0; i < n; i++)
        cin >> processSize[i];

    BestFit(blockSize, m, processSize, n);

    return 0;
}
