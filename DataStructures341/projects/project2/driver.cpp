#include "Int341.h"
#include "INode.h"
#include "SqList.h"

int main() {




    SqList x;
    //SqList y;
    x.add(Int341(1));
    x.add(Int341(2));
    x.add(Int341(99));
    x.add(Int341(4));
    x.add(Int341(5));
    x.add(Int341(6));
    x.add(Int341(7));
    x.add(Int341(9));
    x.add(Int341(10));

    ////Int341 test = x[2];
//  //  std::cout << test.m_data;

    x.dump();
    //std::cout << std::endl;;
    int i = x.indexOf(2);
    std::cout << i << std::endl;
    x.dump();

    //SqList z(x);
    //z.dump();
    //std::cout << std::endl;;

    //z.add(Int341(88));
    //x.dump();
    //std::cout << std::endl;;
    //z.dump();
    //x.remove(Int341(3));
    //std::cout << "x " << std::endl;
    //x.dump();


    //y = x;
    ////x.removeAt(5);
    //std::cout << "y " << std::endl;
    //y.dump();
    //std::cout << std::endl;;
    //
    //x.add(Int341(11));
    //std::cout << "x after add" << std::endl;
    //x.dump();
    ////y = x; 
    //std::cout << "y after add" << std::endl; 
    //y.dump();


    //DNode* newNode = new DNode(Int341(1));
    //INode x(newNode);
    //std::cout << x.m_dNode->m_data.m_data << std::endl;
    return 0;
}

