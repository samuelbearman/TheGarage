#ifndef QTREE_H
#define QTREE_H

#include "Point.h"
#include "BBox.h"
#include "QTNode.h"

class QTree {
public:
    QTree();
    ~QTree();
    bool add(const Point &pt, int data);  // actually, add/replace
    bool remove(const Point pt);
    bool find(const Point pt, int &data);
    int findPoints(const BBox &region, std::vector<Point> &found);
    void dump();

    QTNode *m_root;

private:


};

#endif
