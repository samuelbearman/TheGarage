/****************************************************************
 *
 * test2.cpp: test program for S'18 Project 5: hash tables
 *
 * Tests simple C-string values
 *
 ****************************************************************/

#include "ProbeHashTable.h"
#include "ChainHashTable.h"
#include "getCurrentCPU.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "words.h"
#include <string.h>
#include <stdio.h>

using namespace std;

struct cStr341 {
    const char *m_str;
    bool operator!=(const cStr341 &other) { return strcmp(m_str, other.m_str); }
    bool operator==(const cStr341 &other) { return !(*this != other); }

    friend ostream& operator<<(ostream& sout, const cStr341& data) {
	sout << data.m_str;
	return sout;
    }
};

unsigned int myHashFunction(const cStr341 &data) {
    const unsigned int hCoeff = 33 ;  // Suggested as good value in text
    unsigned int hCode = 0;

    for (const char *cp = data.m_str; *cp != '\0'; cp++) {
	hCode = hCode * hCoeff + *cp;
    }
    return hCode;
}

main(int argc, char **argv) {
    cStr341 data, rm_data;
    bool found;
    clock_t startCPU, endCPU;

    ChainHashTable<cStr341> chainHT(&myHashFunction);
    
    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data.m_str = words[i];
	if (!chainHT.insert(data)) {
	    cout << "insert(" << data << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
     //chainHT.dump();

    ProbeHashTable<cStr341> probeHT2(&myHashFunction);
    ProbeHashTable<cStr341> probeHT(&myHashFunction, 70001);

    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data.m_str = words[i];
	if (!probeHT2.insert(data)) {
	    cout << "insert(" << data << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "[ProbeHashTable: Simple test]\n"
	 << "= After " << 80 << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT2.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data.m_str = words[i];
	if (!probeHT2.find(data)) {
	    cout << "find(" << data << ") failed!" << endl;
	}
	rm_data = probeHT2.remove(data, found);
	if (!found) {
	    cout << "remove(" << data << ")--not found!" << endl;
	}
	else if (rm_data != data) {
	    cout << "remove(" << data << ")--data does not match!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " finds/removes\n"
	 << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT2.dump();

  //
  // Now, big tests  (dumps turned off--too long)
  //
    startCPU = getCurrentCPU();
    for (int i = 0; i < numWords; i++) {
	data.m_str = words[i];
	if (!probeHT.insert(data)) {
	    cout << "insert(" << data << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "[ProbeHashTable: Full test]\n"
	 << "= After " << numWords << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < numWords; i++) {
	data.m_str = words[i];
	if (!probeHT.find(data)) {
	    cout << "find(" << data << ") failed!" << endl;
	}
	rm_data = probeHT.remove(data, found);
	if (!found) {
	    cout << "remove(" << data << ")--not found!" << endl;
	}
	else if (rm_data != data) {
	    cout << "remove(" << data << ")--data does not match!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " finds/removes\n"
	 << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT.dump();

    return 0;
}
