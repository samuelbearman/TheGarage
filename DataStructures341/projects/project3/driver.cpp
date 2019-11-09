#include "QTree.h"
#include "QTNode.h"
#include <iostream>
int main() {


//    QTNode* temp = new QTNode (BBox(Point(4096,4096), 3));
//
//    QTNode* southTest = new QTNode (BBox(Point(2048,2048), 7));
//    temp->southWest = southTest;

//    QTNode y(BBox(Point(4096,4098), 17));


    QTree myQT;
    myQT.add(Point(34,34), 1);
    myQT.add(Point(1,1), 2);
    myQT.add(Point(34, 0), 10);
    myQT.add(Point(0, 34), 14);



    QTNode::iterator it = myQT.m_root->begin();
    QTNode::iterator last_it = myQT.m_root->end();

    QTNode* qtnode = myQT.m_root;
    
    for (QTNode::iterator it = qtnode->begin(); it != qtnode->end(); it++) {
        QTNode* kid_qtnode = *it;
        if (kid_qtnode != NULL) {
            std::cout << kid_qtnode->m_bounds << std::endl;
        }

    }

    //QTNode* x = *it;
    //QTNode* y = *last_it;
    //
    //std::cout << x->m_bounds << std::endl;
    //std::cout << y->m_bounds << std::endl;    

    //it++; 
    //x = *it;
    //std::cout << x->m_bounds << std::endl;
   


//    if (x == y) {
//        std::cout << "true";
//    } else {
//        std::cout << "false";
//    }

//    QTree myQT;
//
//    myQT.add(Point(100,100), 1);
//    myQT.add(Point(5,5), 2);
//    myQT.add(Point(10,10), 10);
    //myQT.dump();

    //int thing = 0;
    //bool test = NULL;
    //test  = myQT.find(Point(5,5), thing);
    //if (test == true) {
    //    std::cout << "the point is there"<< std::endl;
    //} else if (test == false) {
    //    std::cout << "the point is not there" << std::endl;
    //}

    //test = myQT.find(Point(5,10), thing); 
    //if (test == true) {
    //    std::cout << "the point is there"<< std::endl;
    //} else if (test == false) {
    //    std::cout << "the point is not there" << std::endl;
    //}


    //myQT.remove(Point(36, 36));
    //myQT.remove(Point(25,25));
    //myQT.dump();


    //myQT.remove(Point(100, 100));; 

    //myQT.dump();


    //std::cout << x.m_root->northEast->m_bounds << std::endl;
    //std::cout << x.m_root->southEast->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->northWest->m_bounds << std::endl; 

    //QTree x;
    //x.add(Point(36,36), 6);
    ////std::cout << std::endl;
    ////x.add(Point(37,37), 8);
    ////x.add(Point(45, 25), 67);

    //x.add(Point(2,2), 88);

    //x.dump();
    //delete x.m_root->southWest;
    //delete x.m_root->northEast;
    //delete x.m_root;
    //
    //x.add(Point(52,10), 33);

    //if (x.m_root->southWest == NULL) 
    //    std::cout << "southWest null" <<  std::endl;
    //if (x.m_root->northWest == NULL)   
    //    std::cout << "northwest null" <<  std::endl;
    //if (x.m_root->northEast == NULL)   
    //    std::cout << "northEast null" <<  std::endl;
    //if (x.m_root->southEast == NULL)   
    //    std::cout << "southEast null" <<  std::endl;

    //x.remove(Point(36,36));

    //std::cout << std::endl;


    //std::cout << x.m_root->m_bounds << std::endl;
    //std::cout << x.m_root->m_point<< std::endl;
   
    //if (x.m_root->southWest == NULL) 
    //    std::cout << "southWest null" << std::endl;
    //if (x.m_root->northWest == NULL)  
    //    std::cout << "northwest null" << std::endl;
    //if (x.m_root->northEast == NULL)  
    //    std::cout << "northEast null" << std::endl;
    //if (x.m_root->southEast == NULL)  
    //    std::cout << "southEast null" << std::endl;

    //std::cout << x.m_root->northEast->m_bounds << std::endl;
    //std::cout << x.m_root->southEast->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->northWest->m_bounds << std::endl; 
    //std::cout << x.m_root->southEast->southEast->m_bounds << std::endl;
    //std::cout << x.m_root->southEast->northWest->m_bounds << std::endl;
    //std::cout << x.m_root->southEast->southEast->m_point << std::endl;
    //std::cout << x.m_root->southEast->northWest->m_point << std::endl;


    //std::cout << x.m_root->m_bounds<< std::endl;
    //std::cout << x.m_root->m_point<< std::endl;
    //std::cout << x.m_root->northEast->southWest->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->northEast->m_point << std::endl;
    //std::cout << x.m_root->northEast->m_data << std::endl;
    //
    //std::cout << std::endl;

    //std::cout << x.m_root->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->m_point << std::endl;
    //std::cout << x.m_root->southWest->m_data << std::endl;

    //std::cout << std::endl;
    //std::cout << x.m_root->northEast->m_bounds << std::endl;
    //std::cout << x.m_root->northEast->m_point << std::endl;
    //std::cout << x.m_root->northEast->m_data << std::endl;
    //x.add(Point(25,25), 17);
    //x.add(Point(36,36), 45);

    //x.add(Point(15,15), 67);

    //std::cout << std::endl;
    //std::cout << x.m_root->northWest->m_bounds << std::endl;
    //std::cout << x.m_root->northWest->m_point << std::endl;
    //std::cout << x.m_root->northWest->m_data << std::endl;
    //std::cout << x.m_root->m_bounds << std::endl;
    //std::cout << x.m_root->m_point << std::endl;
    //std::cout << x.m_root->m_data << std::endl;

    //std::cout << std::endl;

    //std::cout << x.m_root->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->m_point << std::endl;
    //std::cout << x.m_root->southWest->m_data << std::endl;
    //
    //std::cout << std::endl;

    //std::cout << x.m_root->southEast->m_bounds << std::endl;
    //std::cout << x.m_root->southEast->m_point << std::endl;
    //std::cout << x.m_root->southEast->m_data << std::endl;

    //std::cout << std::endl;

    //std::cout << x.m_root->northWest->m_bounds << std::endl;
    //std::cout << x.m_root->northWest->m_point << std::endl;
    //std::cout << x.m_root->northWest->m_data << std::endl;

    //std::cout << std::endl;

    //std::cout << x.m_root->northEast->m_bounds << std::endl;
    //std::cout << x.m_root->northEast->m_point << std::endl;
    //std::cout << x.m_root->northEast->m_data << std::endl;

    //std::cout << std::endl;

    //std::cout << x.m_root->southWest->northEast->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->northEast->m_point << std::endl;
    //std::cout << x.m_root->southWest->northEast->m_data << std::endl;

    //std::cout << std::endl;

    //std::cout << x.m_root->southWest->southWest->m_bounds << std::endl;
    //std::cout << x.m_root->southWest->southWest->m_point << std::endl;
    //std::cout << x.m_root->southWest->southWest->m_data << std::endl;

    //if(x.m_root->southWest->southWest != NULL) {
    //    std::cout << "South West is child" << std::endl;
    //}

    //if(x.m_root->southWest->southEast != NULL) {
    //    std::cout << "South East is a child" << std::endl;
    //}

    //if(x.m_root->southWest->northEast != NULL) {
    //    std::cout << "North East is a child" << std::endl;
    //}

    //if(x.m_root->southWest->northWest != NULL) {
    //    std::cout << "North West is a child" << std::endl;
    //}

    return 0;


}
