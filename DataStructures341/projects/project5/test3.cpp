/****************************************************************
 *
 * test3.cpp: test program for S'18 Project 5: hash tables
 *
 * Tests much larger hash tables, which makes the timing
 * more meaningful.
 *
 ****************************************************************/

#include "ProbeHashTable.h"
#include "ChainHashTable.h"
#include "getCurrentCPU.h"
#include <cstdlib>
#include <iostream>

using namespace std;

unsigned int myHashFunction(const int &data) {
    return (unsigned int) data * 149 + 47;
}

unsigned int myBadHashFunction(const int &data) {
    return (unsigned int) data;
}

main(int argc, char **argv) {
    int rm_data;
    bool found;
    clock_t startCPU, endCPU;

    ChainHashTable<int> chainHT(&myHashFunction);
    startCPU = getCurrentCPU();
    for (int i = 0; i < 100000; i++) {
	if (!chainHT.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //chainHT.dump();  // uncomment for debugging, but will print out tons!

    ProbeHashTable<int> probeHT(&myBadHashFunction, 100000);
    startCPU = getCurrentCPU();
    for (int i = 0; i < 2000000; i += 20) {
	if (!probeHT.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 insertions w/bad hash table size and func\n"
	 << "  (Should see lots of collisions)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < 2000000; i += 20) {
	if (!probeHT.find(i)) {
	    cout << "find(" << i << ") failed!" << endl;
	}
	rm_data = probeHT.remove(i, found);
	if (!found) {
	    cout << "remove(" << i << ")--not found!" << endl;
	}
	else if (rm_data != i) {
	    cout << "remove(" << i << ")--data does not match!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 finds/removes (should be empty)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT.dump();

    return 0;
}
