#ifndef QTNODE_H
#define QTNODE_H

#include <vector>
#include "Point.h"
#include "BBox.h"
#include <string>

#define QT_NUM_KIDS 4

class QTNode {
public:
    class iterator {
    public:
	iterator();

	iterator operator=(const QTNode::iterator &other);
	bool operator==(const QTNode::iterator &other);
	bool operator!=(const QTNode::iterator &other);
	iterator &operator++();          // Prefix: e.g. "++it"
	iterator operator++(int dummy);  // Postfix: "it++"
	QTNode *operator*();
    friend class QTNode;
    
    private:
	// Add data members here to record state of current iterator position
    QTNode* m_iterator;
    QTNode* m_leaves[4];
    int m_pointer;
    };

    QTNode();
    QTNode(const BBox &region);
    ~QTNode();
    bool add(const Point &pt, int data);  // actually, add/replace
    bool remove(const Point &pt, bool &empty);
    bool find(const Point &pt, int &data);
    int findPoints(const BBox &region, std::vector<Point> &found);
    void dump();

    iterator begin();
    iterator end();

    BBox m_bounds;  // The bounding box for this node
    Point m_point;  // If leaf node (i.e., no kids), m_point, m_data hold the
    int m_data;     // actual point and data value the user inserted.
    // YOu must add data member(s) to store pointers to child QTNode's

    QTNode *northEast;
    QTNode *northWest;
    QTNode *southEast;
    QTNode *southWest;


    //
    // YOU CAN ADD ANY OTHER CONSTRUCTORS, MEMBER FUNCTIONS, MEMBER DATA, ETC.
    // AS NEEDED.
    //


};
#endif
