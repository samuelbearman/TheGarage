#ifndef SQ_LIST_H
#define SQ_LIST_H

#include "Int341.h"
#include "DNode.h"
#include <iostream>
#include "INode.h"
#include <stddef.h>
#include <list>
#include <cmath>
#include <stdexcept>

class SqList {
    public:
        SqList();
        SqList(const SqList& other);
        const SqList& operator=(const SqList& rhs);
        ~SqList();
        void dump();
        void consolidate();
        void add(const Int341& data);
        Int341 remove(const Int341& data);
        Int341 removeAt(int pos);
        Int341& operator[](int pos);
        int indexOf(const Int341& data);
        int numItems();

    private:
        std::list<INode> m_iList;
        int m_size;
};

#endif

