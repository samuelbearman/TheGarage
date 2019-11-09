#include <iostream>
using namespace std;

//

int binarySearch(int* myNums, int cnt, int val) {

    int start = 0;
    int end = cnt;
    int mid = cnt / 2;

    while(start <= end && myNums[mid] != val) {
        if(myNums[mid] < val) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
        mid = (start + end) / 2;
    }

    if(myNums[mid] == val) {
        return mid;
    } else {
        return -1;
    }
}
//

int main() {

    int val, myNums[1000];
    int cnt = -1;
    int pos = 0; 

    cout << "Enter the numbers from smallest to largest, 0 to stop\n";
    do {
        cin >> myNums[++cnt];
    } while (myNums[cnt] != 0);
    //fill code

    do {
        cout << "Enter number to search for: ";
        cin >> val;
        if (val != 0) {
            pos = binarySearch(myNums, cnt, val);
            cout << "binarySeacrh reported " << pos << endl;
        }
    } while (val != 0);

    return 0;
}

