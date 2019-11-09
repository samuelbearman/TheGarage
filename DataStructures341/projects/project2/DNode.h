#ifndef D_NODE_H
#define D_NODE_H

#include "Int341.h"
#include <stddef.h>
class DNode {
    public:
        DNode();
        DNode(Int341 x);

        Int341 m_data;
        DNode* m_next;
};

#endif

