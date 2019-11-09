#include "QTree.h"

// Default QTree constructor
QTree::QTree() {

    m_root = new QTNode(BBox (Point(0,0), 64));


}

// QTree destructor
QTree::~QTree() {

    delete m_root;

}

// dump
// prints the entire contents of the QTree
void QTree::dump() {

    std::cout << "=======================================" << std::endl;
    std::cout << " START Dump of quadtree" << std::endl;
    std::cout << "---------------------------------------" << std::endl;
    
    m_root->dump();

    std::cout << "---------------------------------------" << std::endl;
    std::cout << " END Dump of quadtree" << std::endl;
    std::cout << "=======================================" << std::endl;

}


// findPoints
// finds all points in a QTree given a BBox region and pushes all points into a vector called found
int QTree::findPoints(const BBox &region, std::vector<Point> &found) {

    if (m_root->southEast == NULL && m_root->southWest == NULL && m_root->northEast == NULL && m_root->northWest == NULL) {
        if (m_root->m_bounds.overlaps(region)) {
            found.push_back(m_root->m_point);
            return 1;
        } else {
            return 0;
        } 
    } else {
        m_root->findPoints(region, found);
    }

}




// finds a point in a QTree given a point and data
// returns true if found
// returns false if not
bool QTree::find(const Point pt, int &data) {

    bool answer = NULL;
    if (m_root->m_point == pt && m_root->southEast == NULL && m_root->southWest == NULL && m_root->northEast == NULL && m_root->northWest == NULL) {
        data = m_root->m_data;
        return true;
    } else {
        answer = m_root->find(pt, data);
        return answer;
    }

}

// remove
// finds a point in the QTree and removes it from the QTree
// returns true if removed
// return false if not found 
// after removal, performs a 'root prune' of the tree
bool QTree::remove(const Point pt) {

    // This removes a specific point in the QTree
    // uses recursion to remove a point
    //
    bool empty = NULL;
    bool answer = NULL;
    if (m_root->m_point == pt) {
        m_root->m_point.m_x = 0;
        m_root->m_point.m_y = 0;
        m_root->m_data = 0;
    } else {
        answer = m_root->remove(pt, empty);
    }



    // CONMDITONAL HERE
    // after removal, check to see if m_root needs top be pruned
    
    QTNode *temp = m_root;
    QTNode *prev;
    
    bool stillPruning = NULL;
    int counter = 0;
    bool NE = NULL;
    bool NW = NULL;
    bool SE = NULL;
    bool SW = NULL;

    if (m_root->northWest) counter++;
    if (m_root->northEast) counter++;
    if (m_root->southWest) counter++;
    if (m_root->southEast) counter++;

    if (counter > 1) {
        stillPruning = false;
        counter = 0;
    } else {
        stillPruning = true;
        counter = 0;
    }

    while (stillPruning != false) {
        if (temp->northWest != NULL) {
            counter++;
            NW = true;
        }
        if (temp->northEast != NULL) {
            counter++; 
            NE = true;
        }
        if (temp->southWest != NULL) {
            counter++; 
            SW = true;
        }
        if (temp->southEast != NULL) {
            counter++; 
            SE = true;
        }
        
        if (counter == 1) {
            // case where theres only one child
            // make that child new root and delete above
            if (NW == true) {
                prev = temp;
                temp = temp->northWest;
                NW = NULL;
            }
            if (NE == true) {
                prev = temp;
                temp = temp->northEast;
                NE = NULL;
            }
            if (SW == true) {
                prev = temp;
                temp = temp->southWest;
                SW = NULL;
            }
            if (SE == true) {
                prev = temp;
                temp = temp->southEast;
                SE = NULL;
            }
            counter = 0;
        } else {
            // more than one child at root
            // just return back removed answer
            return answer;
        }
        prev->northWest = NULL;
        prev->southWest = NULL;
        prev->northEast = NULL;
        prev->southEast = NULL;
        delete m_root;
        m_root = temp;
    }
    prev = NULL;
    temp = NULL;

    return answer; 
}


// helper function
// Takes in a BBox that is the bigger and a smaller size and figures out 
// which quadrant the smaller would be placed into
int findQuadrant(const BBox &bigger, const BBox &smaller) {

    // if the bottom left corner of smaller is the same as biggers
    // then it ust be in the southWest quadrant
    // if the bottom left of smaller is the center point of bigger
    // i.e. bigger m_bL + (m_dim / 2)
    // then it must be the northEast quadrant

    if (smaller.m_bL == bigger.m_bL) {
        // SOUTH WEST 
        //std::cout << "old root placed in SW";
        return 1;
    }
    if (smaller.m_bL.m_x == bigger.m_bL.m_x + (bigger.m_dim / 2) && smaller.m_bL.m_y == bigger.m_bL.m_y + (bigger.m_dim / 2)) {
        // NORTH EAST
        //std::cout << "old root placed in NE";
        return 4;
    }
    if (smaller.m_bL.m_x == bigger.m_bL.m_x + (bigger.m_dim / 2) && smaller.m_bL.m_y == bigger.m_bL.m_y) {
        // SOUTH EAST
        //std::cout << "old root placed in SE";
        return 2;
    }
    if (smaller.m_bL.m_x == bigger.m_bL.m_x && smaller.m_bL.m_y == bigger.m_bL.m_y + (bigger.m_dim / 2)) {
        // NORTH WEST 
        //std::cout << "old root placed in NW";
        return 3; 
    }
}


// add
// adds in a new point to the QTree
// returns true if added
bool QTree::add(const Point &pt, int data) {
    
    // QTree itself only does the first two nodes itself
    // after that, the QTNode add handles everything else
    // if its the first point added, assign point to the m_root
    // point and done
    //
    // if it the second point, resixe the m_root BBox using resize()
    // and put the two points in the appropriate quadrants
    //
    // if neither of these conditions are true, call add on the root
    //

    // there is no point at m_root
    // its either the first or third or more points
    // if no point and all children are null, it is the first point being added
    // if no point and has atleast one child, then it is atleast the 3rd or higher point
    // if there is a point, then we must be adding the second point, resize and split

    // NEW CONDITIONAL
    // if the point begin added at any given time is bigger than the set bounding box 
    // we need to change the m_root to a new bounding box for each case above so that it will fit


    if (m_root->m_data == 0) {
        if (m_root->southEast == NULL && m_root->southWest == NULL && m_root->northEast == NULL && m_root->northWest == NULL) {
            // CONDIOTIONAL FOR GROWING
            while (pt.m_x >= (m_root->m_bounds.m_bL.m_x + m_root->m_bounds.m_dim) || pt.m_y >= (m_root->m_bounds.m_bL.m_y + m_root->m_bounds.m_dim)) { 
                // Create a new root node and set its BBox to the old roots
                // call grow on that new Node
                // then must determine where the old m_root needs to go realtive to 
                // the new BBox of newNode
                m_root->m_bounds.grow(); 
            }
                m_root->m_point = pt;
                m_root->m_data = data;
        } else {
            while (pt.m_x >= (m_root->m_bounds.m_bL.m_x + m_root->m_bounds.m_dim) || pt.m_y >= (m_root->m_bounds.m_bL.m_y + m_root->m_bounds.m_dim)) { 
                // CONDITIONAL FOR GROWING
                // while loop to loop and grow on the fly
                // need to determine which quadrant old m_root is to be placed in based
                // on growth
                QTNode *newRoot = new QTNode;
                newRoot->m_bounds = m_root->m_bounds;
                newRoot->m_bounds.grow();
                // Before making this the new root, we need to figure out
                // what quadrant the old root would be stored in
                // HELPER FUNCTION?
                // Pass in old BBox m_bL Point to inBounds?
                int region = findQuadrant(newRoot->m_bounds, m_root->m_bounds);
                switch (region) {
                    case 1:
                        // SOUTH WEST
                        newRoot->southWest = m_root;
                        break;
                    case 2:
                        // SOUTH EAST
                        newRoot->southEast = m_root;
                        break;
                    case 3:
                        // NORTH WEST
                        newRoot->northWest = m_root;
                        break;
                    case 4:
                        // NORTH EAST
                        newRoot->northEast = m_root;
                        break;
                }
                m_root = newRoot;
                newRoot = NULL;
            }
            m_root->add(pt, data);
        }
    } else {
        // adding second point, resize and find quadrants for two nodes
        m_root->m_bounds.resize(m_root->m_point, pt);
        m_root->add(pt, data);
    }
}


