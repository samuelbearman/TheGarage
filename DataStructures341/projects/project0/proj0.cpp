// File: proj0.cpp
//
// CMSC 341 Spring 2018 Project 0
//
// Program to print out a randomized sequence of the
// numbers from 0 to 9, Using a really dumb algorithm.
//
// Why does this program segfault??!?!?!?!
// (You are NOT supposed to actually fix this code, though!!!)
//

#include <cstdlib>
#include <string>
#include <iostream>

using namespace std;

main() {
    string *str[10];
    int num_left;
    int pick;
    string *sptr;

    // Fill array with freshly-constructed strings
    for (int i = 0; i < 10; i++) {
        str[i] = new string(1, static_cast<char>('0' + i));
        num_left++;
    }

    // Now, scramble by picking a slot at random, making sure it's not
    // already been processed, then printing, deleting and nulling out
    while (num_left > 0) {
        pick = rand() % 10;
        sptr = str[pick];
        if (sptr = NULL) {  // NULL indicates we already processed this;
            continue;       // skip and continue looping
        }
        cout << *str[pick] << endl;
        delete str[pick];
        str[pick] = NULL;
        --num_left;
    }
}
