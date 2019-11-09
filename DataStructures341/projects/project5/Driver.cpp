#include "ProbeHashTable.h"
#include "ChainHashTable.h"
#include "getCurrentCPU.h"
#include <cstdlib>
#include <iostream>
#include "words.h"
#include <string.h>
#include <stdio.h>

using namespace std;

unsigned int myHashFunction(const int &data) {
    return (unsigned int) data * 149 + 47;
}

unsigned int myBadHashFunction(const int &data) {
    return (unsigned int) data;
}

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
    
    int rm_data;
    bool found;
    clock_t startCPU, endCPU;

	std::cout << "Test1.cpp" <<std::endl;
	std::cout << std::endl;

    ChainHashTable<int> chainHT(&myHashFunction);
    cout << "============================================================\n"
	 << "= Initial chained hash table\n"
	 << "============================================================"
	 << endl;
    chainHT.dump();  // Should show empty table
    
    startCPU = getCurrentCPU();
    for (int i = 0; i < 101; i++) {
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







	std::cout << "Test2.cpp" <<std::endl;
	std::cout << std::endl;





	cStr341 data2, rm_data2;

	ChainHashTable<cStr341> chainHT3(&myHashFunction);
    
    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data2.m_str = words[i];
	if (!chainHT3.insert(data2)) {
	    cout << "insert(" << data2 << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
     //chainHT3.dump();

    ProbeHashTable<cStr341> probeHT3(&myHashFunction);
    ProbeHashTable<cStr341> probeHT4(&myHashFunction, 70001);

    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data2.m_str = words[i];
	if (!probeHT3.insert(data2)) {
	    cout << "insert(" << data2 << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "[ProbeHashTable: Simple test]\n"
	 << "= After " << 80 << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT3.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < 80; i++) {
	data2.m_str = words[i];
	if (!probeHT3.find(data2)) {
	    cout << "find(" << data2 << ") failed!" << endl;
	}
	rm_data2 = probeHT3.remove(data2, found);
	if (!found) {
	    cout << "remove(" << data2 << ")--not found!" << endl;
	}
	else if (rm_data2 != data2) {
	    cout << "remove(" << data2 << ")--data does not match!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " finds/removes\n"
	 << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    probeHT3.dump();

  //
  // Now, big tests  (dumps turned off--too long)
  //
    startCPU = getCurrentCPU();
    for (int i = 0; i < numWords; i++) {
	data2.m_str = words[i];
	if (!probeHT4.insert(data2)) {
	    cout << "insert(" << data2 << ") failed!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "[ProbeHashTable: Full test]\n"
	 << "= After " << numWords << " insertions\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT4.dump();

    startCPU = getCurrentCPU();
    for (int i = 0; i < numWords; i++) {
	data2.m_str = words[i];
	if (!probeHT4.find(data2)) {
	    cout << "find(" << data2 << ") failed!" << endl;
	}
	rm_data2 = probeHT4.remove(data2, found);
	if (!found) {
	    cout << "remove(" << data2 << ")--not found!" << endl;
	}
	else if (rm_data2 != data2) {
	    cout << "remove(" << data2 << ")--data does not match!" << endl;
	}
    }
    endCPU = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After " << numWords << " finds/removes\n"
	 << "  (~80% of buckets should be DELETED, rest EMPTY)\n"
	 << "(" << (endCPU - startCPU) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT4.dump();





	clock_t startCPU1, endCPU1;



	std::cout << "Test3.cpp" <<std::endl;
	std::cout << std::endl;

	ChainHashTable<int> chainHT2(&myHashFunction);
    startCPU1 = getCurrentCPU();
    for (int i = 0; i < 101; i++) {
	if (!chainHT2.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU1 = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 insertions\n"
	 << "(" << (endCPU1 - startCPU1) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //chainHT2.dump();  // uncomment for debugging, but will print out tons!

    ProbeHashTable<int> probeHT5(&myBadHashFunction, 100000);
    startCPU1 = getCurrentCPU();
    for (int i = 0; i < 2000000; i += 20) {
	if (!probeHT5.insert(i)) {
	    cout << "insert(" << i << ") failed!" << endl;
	}
    }
    endCPU1 = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 insertions w/bad hash table size and func\n"
	 << "  (Should see lots of collisions)\n"
	 << "(" << (endCPU1 - startCPU1) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT5.dump();

    startCPU1 = getCurrentCPU();
    for (int i = 0; i < 2000000; i += 20) {
	if (!probeHT5.find(i)) {
	    cout << "find(" << i << ") failed!" << endl;
	}
	rm_data = probeHT5.remove(i, found);
	if (!found) {
	    cout << "remove(" << i << ")--not found!" << endl;
	}
	else if (rm_data != i) {
	    cout << "remove(" << i << ")--data does not match!" << endl;
	}
    }
    endCPU1 = getCurrentCPU();
    cout << "============================================================\n"
	 << "= After 100000 finds/removes (should be empty)\n"
	 << "(" << (endCPU1 - startCPU1) << " CPU ticks)\n"
	 << "============================================================"
	 << endl;
    //probeHT5.dump();

    return 0;
}
