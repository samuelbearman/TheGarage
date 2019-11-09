#ifndef POINT_H
#define POINT_H

#include <iostream>

//
// Definition of a simple struct to manage 2-D point coordinates
// Provided by Prof. Park for CMSC 341
// Should be self-explanatory.  Note that "==" is overloaded
//

class Point {
public:
    Point();
    Point(unsigned int x, unsigned int y);
    bool operator== (const Point &other) const;

    unsigned int m_x;
    unsigned int m_y;

    friend std::ostream& operator<<(std::ostream &sout, const Point &pt);
};

#endif
    
