#ifndef I_NODE_H
#define I_NODE_H

#include "Int341.h"
#include "DNode.h"
#include <stddef.h>
class INode {
    public:
        INode();
        INode(DNode* node);
        ~INode();
        void add(DNode* node);
        Int341 remove(Int341 data);
        void dump(int size);
        int size();

        DNode* m_dNode;
        int m_data;
        int m_size;
};

#endif
