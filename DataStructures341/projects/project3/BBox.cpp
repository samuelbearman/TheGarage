//
// Definition of struct to manage 2-D bounding box
// Assumptions:
//   1) bounding box dimension is power of 2
//   2) bounding box is aligned to some multiple of dimension
//   3) Values in box are [m_bL.m_x .. m_bL.m_x+m_dim) (i.e., lower bound
//      is inclusive, upper bound is exclusive)
// Provided by Prof. Park for CMSC 341
//

#include "BBox.h"
#include "Point.h"


BBox::BBox() {}  // Needed because of existence of other constructors

BBox::BBox(const Point &bottomLeft, unsigned int dim) {
    m_bL = bottomLeft;
    m_dim = dim;
}

//
// Determines whether pt is within the bounding box.
//
// Return value:
//   true if in bounding box, else false
//
bool
BBox::inBounds(const Point &pt) const {
    return (pt.m_x >= m_bL.m_x && pt.m_x <= m_bL.m_x + (m_dim - 1) &&
	    pt.m_y >= m_bL.m_y && pt.m_y <= m_bL.m_y + (m_dim - 1));
}

//
// Determines whether we intersect at any point with other bounding box.
//
// Return value:
//   true if in bounding boxes intersect, else false
//
bool
BBox::overlaps(const BBox &other) const {
    // Bounding boxes overlap IFF there is overlap, in either order
    // (the "or"s), in both x and y dimensions (the "and")
    bool x_overlap = (m_bL.m_x <= other.m_bL.m_x ?
		      m_bL.m_x + m_dim > other.m_bL.m_x :
		      other.m_bL.m_x + other.m_dim > m_bL.m_x);
    bool y_overlap = (m_bL.m_y <= other.m_bL.m_y ?
		      m_bL.m_y + m_dim > other.m_bL.m_y :
		      other.m_bL.m_y + other.m_dim > m_bL.m_y);
    return x_overlap && y_overlap;
}
    
//
// Helper function used by calcBBox()
//
static unsigned int
findMSBSet(unsigned int pattern) {
    int bit = 0;
    if (pattern) {
	// Do binary search for highest-order differing bit
	for (int i = 16; i; i >>= 1) {
	    if (pattern >> bit + i) bit += i;
	}
	bit++;  // this maps to range 1..32
    }
    return bit;
}

//
// Reconfigures BBox to be largest bounding box that:
//   1) contains both points; but which...
//   2) will divide the two points into separate quadrants at the
//      immediate next level.
// Note this is the same thing as "smallest bounding box that still
// holds both points".
//
// It does this by taking each dimension (x vs. y) independently,
// and taking binary encoding of the coordinate and seeing what the
// most significant differing bit is.  Each bit, starting from the
// most siginificant, acts like a sign telling us which direction
// branch to take; the most significant differing bit therefore tells
// us the level at which the two points diverge in the binary tree (in
// one dimension). In combining the two dimensions, the dimension with
// the higher point of divergence will determine when the the two points
// diverge in the quadtree.
// 
void
BBox::resize(const Point &pt1, const Point &pt2) {
    unsigned int diffBits;
    unsigned int sw, swMax, mask;

    // First find smallest single quadrant range for X and Y dimensions
    swMax = findMSBSet(pt1.m_x ^ pt2.m_x);
    sw = findMSBSet(pt1.m_y ^ pt2.m_y);
    // Now determine which dimension has highest order bounding range
    if (sw > swMax) swMax = sw;
    // Generate aligned bounds of actual enclosing box
    m_dim = 1 << swMax;
    mask = ~((unsigned int) m_dim - 1);
    m_bL.m_x = pt1.m_x & mask;
    m_bL.m_y = pt1.m_y & mask;
}

//
// Takes existing BBox and expands it to the next larger power-of-2.
// Also handles proper alignment.
// E.g.: BBox {(32, 32), dim=8} would be grown to {(32, 32), dim=16},
// but {(24, 24), dim=8} would be grown to {(16, 16), dim=16}
//
// HINT: useful for creating new nodes *above* existing node in quadtree,
// in order to expand outwards to cover new node beyond current root's
// bounding box.
//
void
BBox::grow() {
    unsigned int mask;

    m_dim *= 2;
    mask = ~((unsigned int) m_dim - 1);
    m_bL.m_x &= mask;
    m_bL.m_y &= mask;
}

std::ostream& operator<<(std::ostream &sout, const BBox &bBox) {
    sout << "{botLeft=" << bBox.m_bL << ", dim=" << bBox.m_dim << "}";
    return sout;
}

