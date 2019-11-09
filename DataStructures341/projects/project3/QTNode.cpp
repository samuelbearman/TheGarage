#include "QTNode.h"
#include <string>

// Default Constructor for a QTNode
QTNode::QTNode() {

    northEast = NULL;
    northWest = NULL;
    southEast = NULL;
    southWest = NULL;

}

// Overloaded constructor for QTNode
QTNode::QTNode(const BBox &region) {

    m_bounds = region;
    northEast = NULL;
    northWest = NULL;
    southEast = NULL;
    southWest = NULL;

}

// Destructor for a QTNode
// Deletes children then itself
QTNode::~QTNode() {

    if (southWest != NULL) delete southWest;
    if (southEast != NULL) delete southEast;
    if (northWest != NULL) delete northWest;
    if (northEast != NULL) delete northEast;

}

// ITERATOR CLASS THINGS

// Postfix '++' operator for the QTNode iterator class
// returns the current iteration and then increments after the operation
QTNode::iterator QTNode::iterator::operator++(int dummy) {

    if (m_pointer <= 4) {
        this->m_iterator = m_leaves[m_pointer++];
        return *this;
    } else {
        this->m_iterator = m_leaves[m_pointer];
        return *this;
    }
    
}

// Prefix '++' operator for the QTNode iterator class
// increments the iterator and then returns that iteration
QTNode::iterator& QTNode::iterator::operator++() {

    if (m_pointer <= 4) {
        this->m_iterator = m_leaves[++m_pointer];
        return *this;
    } else {
        this->m_iterator = m_leaves[m_pointer];
        return *this;
    }
    
}


// returns an iterator that points to the very last child node of any given node
QTNode::iterator QTNode::end() {

    QTNode::iterator it;
    it.m_pointer = 3;
    it.m_iterator = northEast;
    it.m_leaves[0] = southWest;
    it.m_leaves[1] = southEast;
    it.m_leaves[2] = northWest;
    it.m_leaves[3] = northEast;

    return it;

}


// returns an iterator that points to the very first child node of any given node
QTNode::iterator QTNode::begin() {

    QTNode::iterator it;
    it.m_pointer = 0;
    it.m_iterator = southWest;
    it.m_leaves[0] = southWest;
    it.m_leaves[1] = southEast;
    it.m_leaves[2] = northWest;
    it.m_leaves[3] = northEast;

    return it;
    
}

// Dereferencing operator
// returns the pointer the iterator is pointing to as a QTNode
QTNode* QTNode::iterator::operator*() {

    return m_leaves[m_pointer];

}


// Default iterator constructor
QTNode::iterator::iterator() {

    m_iterator = NULL;
    int m_pointer = 0;
    
}


// Overloaded '=' operator for the QTNode iterator class
// equates to iterators to each other
QTNode::iterator QTNode::iterator::operator=(const QTNode::iterator &other) {

    m_iterator->m_bounds = other.m_iterator->m_bounds; 
    m_iterator->m_point = other.m_iterator->m_point;
    
}


// Overloaded '==' operator for the QTNode iterator class
// evaluates if two iterators are equal
// return true for equals
// returns false for not
bool QTNode::iterator::operator==(const QTNode::iterator &other) {

    if (m_iterator->m_point == other.m_iterator->m_point) {
        return true;
    } else {
        return false;
    }
}


// Overloaded '!=' operator for the QTNode iterator class
// evaluates if two iterators are not equal
// return false for not equals
// returns true for equals

bool QTNode::iterator::operator!=(const QTNode::iterator &other) {

    if (m_iterator->m_point == other.m_iterator->m_point) {
        return false;
    } else {
        return true;
    }

}

// END OF ITERATOR STUFF



// findPoints
// finds all points given a specific BBox and pushes all points to a vector called found
// returns an int that is the number of found points
int QTNode::findPoints(const BBox &region, std::vector<Point> &found) {

    int answer = 0;
    if (northEast == NULL && northWest == NULL && southEast == NULL && southWest == NULL) {
        if (region.overlaps(m_bounds)) {
            found.push_back(m_point);
            return 1;
        } else {
            return 0;
        }
    }

    if (southWest != NULL) {
        if (southWest->m_bounds.overlaps(region)) {
            answer += southWest->findPoints(region, found);
        }
    }
    if (southEast != NULL) {
        if (southEast->m_bounds.overlaps(region)) {
            answer += northEast->findPoints(region, found);
        }
    } 
    if (northWest != NULL) {
        if (northWest->m_bounds.overlaps(region)) {
            answer += northWest->findPoints(region, found);
        }
    }
    if (northEast != NULL) {
        if (northEast->m_bounds.overlaps(region)) {
            answer += northEast->findPoints(region, found);
        }
    }
    return answer;

}




// find
// takes a point and data values and finds them in the subTree rooted at current 
// QTNode.
// returns true if found, false if not
bool QTNode::find(const Point &pt, int &data) {

    if (northEast == NULL && northWest == NULL && southEast == NULL && southWest == NULL) {
        if (pt == m_point) {
            data = m_data;
            return true;
        } else {
            return false;
        }
    }
    bool answer = NULL;
    if (northEast != NULL) {
        if (northEast->m_bounds.inBounds(pt)) {
            answer = northEast->find(pt, data);
            if (answer == true) {
                return true;
            } else {
                return false;
            }
        }
    }
    if (southEast != NULL) {
        if (southEast->m_bounds.inBounds(pt)) {
            answer = southEast->find(pt, data);
            if (answer == true) {
                return true;
            } else {
                return false;
            }

        }
    }
    if (northWest != NULL) {
        if (northWest->m_bounds.inBounds(pt)) {
            answer = northWest->find(pt, data);
            if (answer == true) {
                return true;
            } else {
                return false;
            }

        }
    }
    if (southWest != NULL) {
        if (southWest->m_bounds.inBounds(pt)) {
            answer = southWest->find(pt, data);
            if (answer == true) {
                return true;
            } else {
                return false;
            }
        }
    } 
}


// dump
// prints out the contents of the QTNode and recurses into the rest of the tree
void QTNode::dump() {

    if (northEast == NULL && northWest == NULL && southEast == NULL && southWest == NULL) {
        std::cout << "[QTNode bounds=" << m_bounds << " is LEAF: " << m_point << ", data=" << m_data << std::endl;
        return;
    }
    if (northEast != NULL || northWest != NULL || southEast != NULL || southWest != NULL) {
        std::cout << "[QTNode bounds=" << m_bounds << " is INTERNAL: " << std::endl;
    }

    if (southWest != NULL) {
        std::cout << "Bottom-Left child: " << std::endl;
        southWest->dump(); 
    } else {
        std::cout << "Bottom-Left child: " << std::endl;
        std::cout << "[NULL]" << std::endl;
    }

    if (southEast != NULL) {
        std::cout << "Bottom-Right child: " << std::endl;
        southEast->dump(); 
    } else {
        std::cout << "Bottom-Right child: " << std::endl;
        std::cout << "[NULL]" << std::endl;
    }

    if (northWest != NULL) {
        std::cout << "Top-Left child: " << std::endl;
        northWest->dump(); 
    } else {
        std::cout << "Top-Left child: " << std::endl;
        std::cout << "[NULL]" << std::endl;
        std::cout << "]" << std::endl;
    }

    if (northEast != NULL) {
        std::cout << "Top-Right child: " << std::endl;
        northEast->dump(); 
    } else {
        std::cout << "Top-Right child: " << std::endl;
        std::cout << "[NULL]" << std::endl;
    }
}



// remove
// removes a point and data from the QTNode and its children
// cleans itself up after condition of one child is met, takes child and makes
// itself the parent
// returns true if removed 
// returns false if point wasnt there 
bool QTNode::remove(const Point &pt, bool &empty) {

    // BASE CASE
    if (northEast == NULL && northWest == NULL && southEast == NULL && southWest == NULL) {
        // We are at the node that needs to be removed
        // empty = true
        // return true;
        if (m_point == pt) {
            empty = true;
            return true;
        } else {
            // In the case we are at the node it should be at
            // and it is not the same point, then we 
            // set empty to false and return back
            empty = false;

        }
    }
   


    // if the point would fit into the BBox
    // call remove on it again 
    // if if comes back and its false, it means the point was not there, return false again
    // else the point must have been there, so we delete it
    if (northEast != NULL && northEast->m_bounds.inBounds(pt)) {
        northEast->remove(pt, empty);
        if (empty == false) {
            return false;
        } else {
            delete northEast;
            northEast = NULL;   
            
        }


        // Now the question is, is there any LEAF Nodes left and if so, 
        // is it the only remaining leaf node?
        int counter = 0;
        bool NW = NULL;
        bool SE = NULL;
        bool SW = NULL;

        if (northWest != NULL && northWest->northEast == NULL && northWest->northWest == NULL && northWest->southEast == NULL && northWest->southWest == NULL) {
            counter++;
            NW = true;
        }
        if (southEast != NULL && southEast->northEast == NULL && southEast->northWest == NULL && southEast->southEast == NULL && southEast->southWest == NULL) {
            counter++;
            SE = true;
        }
        if (southWest != NULL && southWest->northEast == NULL && southWest->northWest == NULL && southWest->southEast == NULL && southWest->southWest == NULL) {
            counter++;
            SW = true;
        }

        // if the counter is 1, then there is only one child
        // pull it up and delete
        if (counter == 1) {
            if (NW == true) {
                m_point = northWest->m_point;
                m_data = northWest->m_data;
                delete northWest;
                northWest = NULL;
            }
            if (SE == true) {
                m_point = southEast->m_point;
                m_data = southEast->m_data;
                delete southEast;
                southEast = NULL;
            }
            if (SW == true) {
                m_point = southWest->m_point;
                m_data = southWest->m_data;
                delete southWest;
                southWest = NULL;
            }

        } else {
            // Case where there is more than one child
            // just return 
            return empty;
        }
    }




    // if the point would fit into the BBox
    // call remove on it again 
    // if if comes back and its false, it means the point was not there, return false again
    // else the point must have been there, so we delete it
    if (northWest != NULL && northWest->m_bounds.inBounds(pt)) {
        northWest->remove(pt, empty);
        if (empty == false) {
            return false;
        } else {
            delete northWest;
            northWest = NULL;   
        }


        // now if the current node we are at has only one remaining child
        // pull that child up into us and delete
        int counter = 0;
        bool NE = NULL;
        bool SE = NULL;
        bool SW = NULL;

        if (northEast != NULL && northEast->northEast == NULL && northEast->northWest == NULL && northEast->southEast == NULL && northEast->southWest == NULL) {
            counter++;
            NE = true;
        }
        if (southEast != NULL && southEast->northEast == NULL && southEast->northWest == NULL && southEast->southEast == NULL && southEast->southWest == NULL) {
            counter++;
            SE = true;
        }
        if (southWest != NULL && southWest->northEast == NULL && southWest->northWest == NULL && southWest->southEast == NULL && southWest->southWest == NULL) {
            counter++;
            SW = true;
        }

        // if the counter is 1, then there is only one child
        // pull it up and delete
        if (counter == 1) {
            if (NE == true) {
                m_point = northEast->m_point;
                m_data = northEast->m_data;
                delete northEast;
                northEast = NULL;
            }
            if (SE == true) {
                m_point = southEast->m_point;
                m_data = southEast->m_data;
                delete southEast;
                southEast = NULL;
            }
            if (SW == true) {
                m_point = southWest->m_point;
                m_data = southWest->m_data;
                delete southWest;
                southWest = NULL;
            }

        } else {
            // Case where there is more than one child
            // just return 
            return empty;
        }
    }



    if (southWest != NULL && southWest->m_bounds.inBounds(pt)) {
        southWest->remove(pt, empty);
        if (empty == false) {
            return false;
        } else {
            delete southWest;
            southWest = NULL;   
        }


        // now if the current node we are at has only one remaining child
        // pull that child up into us and delete
        int counter = 0;
        bool NE = NULL;
        bool SE = NULL;
        bool NW = NULL;

        if (northEast != NULL && northEast->northEast == NULL && northEast->northWest == NULL && northEast->southEast == NULL && northEast->southWest == NULL) {
            counter++;
            NE = true;
        }
        if (southEast != NULL && southEast->northEast == NULL && southEast->northWest == NULL && southEast->southEast == NULL && southEast->southWest == NULL) {
            counter++;
            SE = true;
        }
        if (northWest != NULL && northWest->northEast == NULL && northWest->northWest == NULL && northWest->southEast == NULL && northWest->southWest == NULL) {
            counter++;
            NW = true;
        }

        // if the counter is 1, then there is only one child
        // pull it up and delete
        if (counter == 1) {
            if (NE == true) {
                m_point = northEast->m_point;
                m_data = northEast->m_data;
                delete northEast;
                northEast = NULL;
            }
            if (SE == true) {
                m_point = southEast->m_point;
                m_data = southEast->m_data;
                delete southEast;
                southEast = NULL;
            }
            if (NW == true) {
                m_point = northWest->m_point;
                m_data = northWest->m_data;
                delete northWest;
                northWest = NULL;
            }

        } else {
            // Case where there is more than one child
            // just return 
            return empty;
        }
    }


    if (southEast != NULL && southEast->m_bounds.inBounds(pt)) {
        southEast->remove(pt, empty);
        if (empty == false) {
            return false;
        } else {
            delete southEast;
            southEast = NULL;   
        }


        // now if the current node we are at has only one remaining child
        // pull that child up into us and delete
        int counter = 0;
        bool NE = NULL;
        bool SW = NULL;
        bool NW = NULL;

        if (northEast != NULL && northEast->northEast == NULL && northEast->northWest == NULL && northEast->southEast == NULL && northEast->southWest == NULL) {
            counter++;
            NE = true;
        }
        if (southWest != NULL && southWest->northEast == NULL && southWest->northWest == NULL && southWest->southEast == NULL && southWest->southWest == NULL) {
            counter++;
            SW = true;
        }
        if (northWest != NULL && northWest->northEast == NULL && northWest->northWest == NULL && northWest->southEast == NULL && northWest->southWest == NULL) {
            counter++;
            NW = true;
        }

        // if the counter is 1, then there is only one child
        // pull it up and delete
        if (counter == 1) {
            if (NE == true) {
                m_point = northEast->m_point;
                m_data = northEast->m_data;
                delete northEast;
                northEast = NULL;
            }
            if (SW == true) {
                m_point = southWest->m_point;
                m_data = southWest->m_data;
                delete southWest;
                southWest = NULL;
            }
            if (NW == true) {
                m_point = northWest->m_point;
                m_data = northWest->m_data;
                delete northWest;
                northWest = NULL;
            }

        } else {
            // Case where there is more than one child
            // just return 
            return empty;
        }
    }
}



// Helper function that takes a point and BBox and finds where that point would go if the box was split
int calcQuadrant(const Point &pt, const BBox &region) {
    int answer = 0;

    if (pt.m_x >= (region.m_bL.m_x + region.m_dim / 2)) {
        answer += 3; 
        //must be in a eastern quadrant
    } else {
        answer += 4;
        //in a western quadrant
    }
    if (pt.m_y >= (region.m_bL.m_y + region.m_dim / 2)) {

        //must be in a northern quadrant
    } else { 
        answer -= 2;
        //in a southern quadrant
    }
    return answer;
    // KEY
    // 1 is South East
    // 2 is South West
    // 3 is North East
    // 4 is North West
}


// adds a QTNode to the current QTNode
// returns true if added
bool QTNode::add(const Point &pt, int data) {

    // Case where we are at a node that is a node with no children and has a point in it
    // i.e. a leaf node, however we have established at this point it needs to be inserted 
    // at this place, shifts the old point down and creates 2 new nodes
    //
    if (northEast == NULL && northWest == NULL && southEast == NULL && southWest == NULL) {
        if (m_data != 0) {
        
        // finds which quardant the point would potentially belong in based on BBox of current node
        // repurposed for the point already at the current node to be shifted down
        
            //Calculate the region for the new point begin added
            Point newPoint;
            int region = calcQuadrant(pt, m_bounds); 
            switch(region) { 
                case 1:
                    // setting the correct BBox and creating the new node and settinmg the values of BBox
                    newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2); 
                    newPoint.m_y = m_bounds.m_bL.m_y;
                    southEast = new QTNode;
                    southEast->m_bounds.m_bL = newPoint;
                    southEast->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    southEast->m_point = pt;
                    southEast->m_data = data;

                    // CONDITIONAL
                    // if the old point still fits inside this new BOX
                    // call add with the old point
                    // RECURSIVE
                    if(southEast->m_bounds.inBounds(m_point)) {
                        southEast->add(m_point, m_data);
                        return true;
                    }
                    //south east
                    break;
                case 2:
                    // setting the correct BBox and creating the new node and settinmg the values of BBox
                    newPoint.m_x = m_bounds.m_bL.m_x; 
                    newPoint.m_y = m_bounds.m_bL.m_y;
                    southWest = new QTNode;
                    southWest->m_bounds.m_bL = newPoint;
                    southWest->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    southWest->m_point = pt;
                    southWest->m_data = data;

                    // CONDITIONAL
                    // if the old point still fits inside this new BOX
                    // call add with the old point
                    // RECURSIVE

                    if(southWest->m_bounds.inBounds(m_point)) {
                        southWest->add(m_point, m_data);
                        return true;
                    }
                    //south west
                    break;
                case 3:
                    // setting the correct BBox and creating the new node and settinmg the values of BBox
                    newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2);
                    newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2); 
                    northEast = new QTNode;
                    northEast->m_bounds.m_bL = newPoint;
                    northEast->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    northEast->m_point = pt;
                    northEast->m_data = data;

                    // CONDITIONAL
                    // if the old point still fits inside this new BOX
                    // call add with the old point
                    // RECURSIVE

                    if(northEast->m_bounds.inBounds(m_point)) {
                        northEast->add(m_point, m_data);
                        return true;
                    }
                    //north east
                    break;
                case 4:
                    // setting the correct BBox and creating the new node and settinmg the values of BBox
                    newPoint.m_x = m_bounds.m_bL.m_x;
                    newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2); 
                    northWest = new QTNode;
                    northWest->m_bounds.m_bL = newPoint;
                    northWest->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    northWest->m_point = pt;
                    northWest->m_data = data;

                    // CONDITIONAL
                    // if the old point still fits inside this new BOX
                    // call add with the old point
                    // RECURSIVE

                    if(northWest->m_bounds.inBounds(m_point)) {
                        northWest->add(m_point, m_data);
                        return true;
                    }
                    //north west
                    break;
            }
            
            // CONDITIONAL STATEMENT HERE
            // If the two nodes are in the same quadrant once split, it then needs to 'add' again until they are at
            // own separate boxes
            // test if now newly created box above holds the old leaf point
            // if so, add that old leaf point to the newly created point


            // Calculate region for the old point inside the leaf node 
            region = calcQuadrant(m_point, m_bounds);
            switch(region) { 
                case 1:
                    newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2); 
                    newPoint.m_y = m_bounds.m_bL.m_y;
                    southEast = new QTNode;
                    southEast->m_bounds.m_bL = newPoint;
                    southEast->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    southEast->m_point = m_point;
                    southEast->m_data = m_data;

                    //south east
                    break;
                case 2:
                    newPoint.m_x = m_bounds.m_bL.m_x; 
                    newPoint.m_y = m_bounds.m_bL.m_y;
                    southWest = new QTNode;
                    southWest->m_bounds.m_bL = newPoint;
                    southWest->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    southWest->m_point = m_point;
                    southWest->m_data = m_data;

                    //south west
                    break;
                case 3:
                    newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2); 
                    newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2);
                    northEast = new QTNode;
                    northEast->m_bounds.m_bL = newPoint;
                    northEast->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    northEast->m_point = m_point;
                    northEast->m_data = m_data;

                    //north east
                    break;
                case 4:
                    newPoint.m_x = m_bounds.m_bL.m_x; 
                    newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2);
                    northWest = new QTNode;
                    northWest->m_bounds.m_bL = newPoint;
                    northWest->m_bounds.m_dim = m_bounds.m_dim / 2;
                    
                    //Now that the BBox has been set, transfer the point and data values over aswell

                    northWest->m_point = m_point;
                    northWest->m_data = m_data;

                    //north west
                    break;
            }

            // after finding the quadrants the nodes belong, create new nodes at those places
            // set the BBoxes and insert the points


            // set now new internal node's data members to zero 
            m_point.m_x = 0;
            m_point.m_y = 0;
            m_data = 0;
            return true; 
        }
    }

    // So if there is a child node that isnt Null, then this is a internal node
    // meaning that child node or a non existant node is where we insert at

    // Checks to see if child nodes are the position of insertion
    if (northEast != NULL) { 
        // check using inBounds to see if point goes in here
        // if not in bounds move to next
        if (northEast->m_bounds.inBounds(pt)) {
            northEast->add(pt, data);
            return true;
        }
            // returns true, call add on this node
    }
        // The node is not NULL, meaning it is either another internal node or it is a leaf node
        // either way, test using helper function to see if the point fits into this quardant
        // if it does, create new node and insert there

    if(northWest != NULL) {
        if (northWest->m_bounds.inBounds(pt)) {
            northWest->add(pt, data);
            return true;
        }
    }

    if(southEast != NULL) {
        if (southEast->m_bounds.inBounds(pt)) {
            southEast->add(pt, data);  
            return true;
        }
    }

    if(southWest != NULL) {
        if (southWest->m_bounds.inBounds(pt)) {
            southWest->add(pt, data);
            return true;
        }
    }

    // if one of these do not execute, then the point must be inserted at a new node
    // find which quadrant the node must be in and insert it
    //
        // 1 is South East
        // 2 is South West
        // 3 is North East
        // 4 is North West

    Point newPoint;
    int region = calcQuadrant(pt, m_bounds);
    switch(region) {
    case 1:
        newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2); 
        newPoint.m_y = m_bounds.m_bL.m_y;
        southEast = new QTNode;
        southEast->m_bounds.m_bL = newPoint;
        southEast->m_bounds.m_dim = m_bounds.m_dim / 2;

        southEast->m_point = pt;
        southEast->m_data = data;
        return true;
        break;
    case 2:
        newPoint.m_x = m_bounds.m_bL.m_x; 
        newPoint.m_y = m_bounds.m_bL.m_y;
        southWest = new QTNode;
        southWest->m_bounds.m_bL = newPoint;
        southWest->m_bounds.m_dim = m_bounds.m_dim / 2;

        southWest->m_point = pt;
        southWest->m_data = data;
        return true;
        break;
    case 3:
        newPoint.m_x = m_bounds.m_bL.m_x + (m_bounds.m_dim / 2); 
        newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2);
        northEast = new QTNode;
        northEast->m_bounds.m_bL = newPoint;
        northEast->m_bounds.m_dim = m_bounds.m_dim / 2;

        northEast->m_point = pt;
        northEast->m_data = data;
        return true;
        break;
    case 4:
        newPoint.m_x = m_bounds.m_bL.m_x; 
        newPoint.m_y = m_bounds.m_bL.m_y + (m_bounds.m_dim / 2);
        northWest = new QTNode;
        northWest->m_bounds.m_bL = newPoint;
        northWest->m_bounds.m_dim = m_bounds.m_dim / 2;

        northWest->m_point = pt;
        northWest->m_data = data;
        return true;
        break;
    } 
}
