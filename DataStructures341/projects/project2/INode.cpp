#include "INode.h"
#include <iostream>

INode::INode() {
    
    m_dNode = NULL;
    m_size = 0;
    m_data = 0;

}

INode::INode(DNode* node) {
    m_dNode = node;
    m_size = 1;
    m_data = node->m_data.m_data;
}

INode::~INode() {


}

// add 
// allows to easily add the given DNode to the list in sorted order
void INode::add(DNode* node) {



    if(m_dNode == NULL || m_dNode->m_data >= node->m_data) {
        node->m_next = m_dNode;
        m_dNode = node;
    } else {
        DNode* temp = m_dNode;
        while(temp->m_next != NULL && temp->m_next->m_data < node->m_data) {
            temp = temp->m_next;    
        }
        node->m_next = temp->m_next;
        temp->m_next = node;
    }
}

// dump
// used for debugging, prints contents of list
void INode::dump(int size) {

    DNode *temp = m_dNode;
    for(int i = 0; i < size; i++) {
        std::cout << temp->m_data.m_data << " ";
        temp = temp->m_next;
    }
    //std::cout << "END" << std::endl;
}

// remove
// allows easy removal of given data from sublist
Int341 INode::remove(Int341 data) {

    Int341 answer = -1;
    DNode *temp = m_dNode;
    DNode *prev = m_dNode;;

    while(temp != NULL) {
        if(temp->m_data == data) {
            answer = temp->m_data;
            prev->m_next = temp->m_next;
            delete temp;
        }
        prev = temp;
        temp = temp->m_next;
    }
    return answer;
}

// size
// retuns the size of a sublist
int INode::size() {

    return m_size;

}

