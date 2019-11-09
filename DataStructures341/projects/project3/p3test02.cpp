#include <utility>
#include <cstdlib>
#include <cstdio>
#include "Point.h"
#include "BBox.h"
#include "QTNode.h"
#include "QTree.h"

using namespace std;

int main(int argc, char **argv) {
    
    BBox bBox;
    Point p1, p2;
    QTree myQT;
    bool retbool;
    int retint;
    int data;
    vector<Point> ptList;

    // First point added
    myQT.add(Point(4096, 4096), 1);
    // Second pt should interact w/bounds set on first point
    // Should be handled efficiently: minimal node building/destroying
    // Resulting BBox should be {(4096,4096), dim=2}
    myQT.add(Point(4096, 4097), 2);
    //myQT.dump();
    // Third point should just add into available quadrant; root should be same
    myQT.add(Point(4097, 4097), 3);
    //myQT.dump();

    // Trigger tree expansion by exceeding bounds of root;
    // new BBox should be {(4096, 4096), dim=4
    myQT.add(Point(4098, 4098), 10);
    //myQT.dump();

    // Trigger tree expansion yet again, by very large amount
    // new BBox should be {(0,0), dim=16384
    myQT.add(Point(8193, 8193), 20);
    myQT.dump();

    //std::cout << myQT.m_root->northEast->m_point;

    //retbool = myQT.find(Point(8193, 8193), data);
    //cout << "find() of good pt returned " << (retbool ? "true" : "false");
    //if (retbool) {
	//cout << ", w/data " << data;
    //}
    //cout << endl;

    //retbool = myQT.find(Point(0, 0), data);
    //cout << "find() of nonexistent pt returned " << (retbool ? "true" : "false") << endl;

    //retint = myQT.findPoints(BBox(Point(3072, 3072), 2048), ptList);
    //cout << "findPoints(): should find 4 pts, claims it found " << retint << endl;
    //cout << "  Actual " << ptList.size() << " values returned:";
    //for (int i = 0; i < ptList.size(); i++) cout << " " << ptList[i];
    //cout << endl;

    retbool = myQT.remove(Point(8193, 8193));
    cout << "Remove of existing pt returned " << (retbool ? "true" : "false") << "; dump should be much simpler" << endl;
    myQT.dump();
    retbool = myQT.remove(Point(0, 0));
    cout << "Remove of nonexistent pt returned " << (retbool ? "true" : "false") << endl;

    return 0;
}
