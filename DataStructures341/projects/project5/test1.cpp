/****************************************************************
 *
 * test1.cpp: test program for S'18 Project 5: hash tables
 *
 * Tests simple int values
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
    cout << "============================================================\n"
	 << "= Initial chained hash table\n"
	 << "============================================================"
	 << endl;
    chainHT.dump();  // Should show empty table
    
    startCPU = getCurrentCPU();
    for (int i = 0; i < 1000; i++) {
	if (!chainHT.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 1000 insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    chainHT.dump();

    ProbeHashTable<int> probeHT(&myHashFunction);
    cout << "============================================================\n"
	 << "= Initial probe hash table\n"
	 << "============================================================"
	 << endl;
    probeHT.dump();
    startCPU = getCurrentCPU();
    for (int i = 0; i < 2020; i += 20) {
	if (!probeHT.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 101 insertions (should see perfect hash)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < 2020; i += 20) {
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
	 << "= After 101 finds/removes (every bucket should be DELETED)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < 101; i++) {
	if (!probeHT.insert(rand())) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 101 random insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT.dump();

    ProbeHashTable<int> probeHT2(&myBadHashFunction, 100);
    for (int i = 0; i < 2000; i += 20) {
	if (!probeHT2.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    cout << "============================================================\n"
	 << "= After 100 insertions w/bad hash table size and func\n"
	 << "  (Should see lots of collisions)\n"
	 << "============================================================"
	 << endl;
    probeHT2.dump(); 
    return 0;
}
