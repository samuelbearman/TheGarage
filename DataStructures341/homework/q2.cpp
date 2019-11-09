#include <iostream>
using namespace std;


int binarySearch(int* myNums, int cnt, int val) {

    int mid = cnt / 2;
    int subArray = 0;

    if (cnt == 0) {
        return -1;
    } // if list is empty

    if (val > myNums[cnt - 1]) {
        return -1;
    } // if val is higher than highest value

    if (val < myNums[0]) {
        return -1;
    } // if val is less than lowest value

    if (myNums[mid] == val) {
        return mid;
    } // if the mid value is the value
    
    if (myNums[mid] < val) {
        subArray = binarySearch(&myNums[mid], cnt - mid, val) + mid;
    } // if the val is larger than the mid point

    if (myNums[mid] > val) {
        subArray = binarySearch(myNums, cnt - mid, val);
    } // if the val is lower than the mid point

    if (myNums[subArray] == val) {
        return subArray;
    } else {
        return -1;
    } //final check to confirm value and return the answer to main, else if not there return -1
}

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
            cout << "binarySearch reported " << pos << endl;
        }
    } while (val != 0);

}
