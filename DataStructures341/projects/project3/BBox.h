#ifndef BBOX_H
#define BBOX_H

#include <iostream>
#include "Point.h"

//
// Definition of struct to manage 2-D bounding box
// Assumptions:
//   1) bounding box dimension is power of 2
//   2) bounding box is aligned to some multiple of dimension
//   3) Values in box are [m_bL.m_x .. m_bL.m_x+m_dim) (i.e., lower bound
//      is inclusive, upper bound is exclusive)
// Provided by Prof. Park for CMSC 341
//

class BBox {
public:
    BBox();
    BBox(const Point &bottomLeft, unsigned int dim);

    bool inBounds(const Point &pt) const;
    bool overlaps(const BBox &other) const;
    void resize(const Point &pt1, const Point &pt2);
    void grow();

    Point m_bL;         // bottom-left corner of bounding box
    unsigned int m_dim; // bounding box size (assumes square box)

    friend std::ostream& operator<<(std::ostream &sout, const BBox &bBox);

};

#endif
