#include "SqList.h"

// Default constructor
SqList::SqList() {
   
    m_size = 0;
}

// Copy constructor
// creates brand new copy of the SqList
SqList::SqList(const SqList& other) {

    m_iList = other.m_iList;
    m_size = other.m_size;

    DNode* temp = m_iList.begin()->m_dNode;
    DNode* newNode; 
    DNode* newList = NULL;
    DNode* inc = NULL;

    DNode* begin = newNode;

    // looping structure to copy all DNodes into a new list
    while(temp) {
        newNode = new DNode;
        newNode->m_data = temp->m_data;

        if(newList == NULL) {
            newList = inc = newNode;
        } else {
            inc->m_next = newNode;
        }
        inc = newNode;
        temp = temp->m_next;
    }

    // clears list, puts new Inode pointing to new list and consolidates
    m_iList.clear();
    INode x(newList);
    m_iList.push_back(x);
    m_iList.front().m_size = m_size;
    consolidate();
}

// asignemnt operator
// allows user to make brand new copy of the SqList
const SqList & SqList::operator=(const SqList& rhs) {

    m_iList = rhs.m_iList;
    m_size = rhs.m_size;

    DNode* temp = m_iList.begin()->m_dNode;
    DNode* newNode; 
    DNode* newList = NULL;
    DNode* inc = NULL;

    DNode* begin = newNode;

    //while loop to copy and make new DNode list
    while(temp) {
        newNode = new DNode;
        newNode->m_data = temp->m_data;

        if(newList == NULL) {
            newList = inc = newNode;
        } else {
            inc->m_next = newNode;
        }
        inc = newNode;
        temp = temp->m_next;
    }

    // clears old list, makes new Inode pointing to new list and consolidates
    m_iList.clear();
    INode x(newList);
    m_iList.push_back(x);
    m_iList.front().m_size = m_size;
    consolidate();
}

// destructor 
// detroys all content in the SqList
SqList::~SqList() {

    if(m_iList.empty()) {
        delete m_iList.begin()->m_dNode;
        m_iList.clear();
    } else { 
        DNode* curr = m_iList.begin()->m_dNode->m_next;
        DNode* temp;
        // loop to delete all INodes
        while(temp != NULL) { 
            temp = curr->m_next;
            delete curr;
            curr = temp;;
        }
        delete temp;
        delete curr;
        m_iList.clear();
    }
}

// index operator
// allows the user to index using "[]" to find element at that cuurent index
Int341 & SqList::operator[](int pos) {

    std::list<INode>::iterator it;
    std::list<INode>::iterator prev_it;

    it = m_iList.begin();
    prev_it = m_iList.begin();

    // first check to see if index is in the very last sublist
    if(pos >= (m_size - m_iList.back().m_size)) {
        int iIndex = pos - (m_size - m_iList.back().m_size);
        if(iIndex == 0) {
            DNode* temp = m_iList.back().m_dNode;
            return temp->m_data;
        } else {
            DNode* temp = m_iList.back().m_dNode;
            //loop from first dnode until reached
            for(int i = 0; i < iIndex; i++) {
                temp = temp->m_next;
            }
            //return that Inode
            return temp->m_data;
        }
    }

    // if it is not in the last inode, we iterate until we find it
    int currIndex = m_iList.begin()->m_size;
    int prevIndex = 0;

    //iterating over all inodes
    for(it = m_iList.begin(); it != m_iList.end(); ++it) {
       
        //if its in the previous Inode, continue to find in that inode
        if(pos < currIndex && pos > prevIndex) {
            int iIndex = pos - prevIndex;
            if(pos == 0) {
                return it->m_dNode->m_data;
            } else {
                DNode* temp = prev_it->m_dNode;
                //loop until it found
                for(int i = 0; i < iIndex; i++) {
                    temp = temp->m_next;
                }
                //return found DNode
                return temp->m_data;
            }
        }
        //indexing operators, replaed and incremented each iteration
        prevIndex += currIndex;
        prev_it = it;
        currIndex += it->m_size;
    }
}

// dump, used for debugging purposes
// shows the contents of the SqList and its sublists
void SqList::dump() {

    std::list<INode>::iterator it;

    int inodeNum = 0;
    for(it = m_iList.begin(); it != m_iList.end(); ++it) {
        std::cout << inodeNum << " (" << it->m_size << ") : "; 
        it->dump(it->m_size);
        std::cout << " " << std::endl;
        inodeNum++;
    }
}


//consolidate
// function that check to see if all sublists in the SqList are at the appropriate 
// Square dimension dictated by the number of elements
void SqList::consolidate() {

    //easy calculation for the square dimension
    int SD = 2 * ceil(sqrt(m_size));

    std::list<INode>::iterator it;
    std::list<INode>::iterator prev_it;

    prev_it = m_iList.begin(); 
    it = m_iList.begin();

    // the square dimesion only applies to lists that are bigger than 7 elements
    if(m_size > 7) {
        //iterating over all Inodes
        for(it = m_iList.begin(); it != m_iList.end(); ++it) {
            //if a lists dimension is smaller than SD
            if(it->m_size < SD) {
                //and if its previous list size was also smaller
                if(prev_it->m_size < SD && it != m_iList.begin()) {
                    //merge the two lists
                    int newSize = it->m_size; 
                    it = m_iList.erase(it);
                    it--;
                    it->m_size += newSize;
                    it++;
                }
            }
            //if the list is greater than the square dimension
            if(it->m_size > SD) {
                //insert a new INode into the list at the half way point of it sublist
                int oldSize = it->m_size;
                DNode* temp = new DNode;
                temp = it->m_dNode;
                for(int i = 0; i < it->m_size / 2; i++) {
                    temp = temp->m_next; 
                }
                it->m_size = it->m_size - (it->m_size / 2);
                INode x(temp);
                if(it == m_iList.end()) {
                    m_iList.push_back(x);
                    x.m_size = oldSize / 2;
                } else {
                    it->m_size = oldSize - it->m_size; 
                    int newSize = it->m_size;
                    it++;
                    m_iList.insert(it, x);                      
                    it--;
                    it->m_size = oldSize - newSize;
                }
                temp = NULL;
                delete temp;
            }
            prev_it = it;
        }
    }

}
// add
// allows user to add new values into the list in sorted order and mainatain the SD
void SqList::add(const Int341& data) {
  
    DNode* newNode = new DNode(data);
    
    // for first element of list
    if(m_size == 0) {
        
        INode x(newNode); // make a new INode pointing to the newNode
        m_iList.push_back(x); //push it to the back of the list
        m_size++; //increment the size of the SqList
        // if its the second element
    } else if(m_size == 1) {

        if(m_iList.begin()->m_data > data.m_data) {
            DNode* temp = new DNode;
            temp = m_iList.begin()->m_dNode;
            m_iList.begin()->add(newNode); 
            INode x(temp);
            m_iList.push_back(x);
            m_iList.end()->m_size++;
            m_size++;
            m_iList.begin()->m_data = data.m_data;
        } else {
            INode x(newNode);
            m_iList.begin()->add(newNode);
            m_iList.push_back(x);
            m_iList.end()->m_size++;
            m_size++;
        }
        //any other number of elements
    } else {
        if(m_iList.begin()->m_data > data.m_data) {
            DNode* temp = new DNode;
            temp = m_iList.begin()->m_dNode;
            m_iList.begin()->add(newNode); 
            m_iList.begin()->m_size++;
            m_size++;
            m_iList.begin()->m_data = data.m_data;
            consolidate();
        } else if(m_iList.back().m_dNode->m_data < data) {
            m_iList.back().add(newNode);
            m_iList.back().m_size++;
            m_size++;
            consolidate();
        } else {
            std::list<INode>::iterator it;
            std::list<INode>::iterator prev_it;
            prev_it = m_iList.begin();

            // iteration for elements inbetween Inodes
            for(it = m_iList.begin(); it != m_iList.end(); ++it) {
                
                if(it->m_data > data.m_data && prev_it->m_data < data.m_data) {
                    prev_it->add(newNode);
                    prev_it->m_size++;
                    m_size++;
                } 
                prev_it = it;
            }
            consolidate();
        }
    }
}

// remove
// allows user to remove elements and keep sorted order and SD
Int341 SqList::remove(const Int341& data) {
   
    Int341 answer = 0;
    std::list<INode>::iterator it;
    std::list<INode>::iterator prev_it;
    prev_it = m_iList.begin();

    //if its part of the last sublist and is what the INode is pointing to
    if(m_iList.begin()->m_data == data.m_data) {
        answer = m_iList.begin()->m_data;
        DNode* temp = m_iList.begin()->m_dNode;
        DNode* newNode = m_iList.begin()->m_dNode->m_next;
        m_iList.begin()->m_dNode = newNode;
        delete temp;
        m_iList.begin()->m_size--;
        m_size--;
    }
    
    //if its part of the sublist, but not what the Inode is pointing to  
    if(m_iList.back().m_data < data.m_data) {
        answer = m_iList.back().remove(data);
        m_iList.back().m_size--;
        m_size--;
    }

    //finding Inodes inbetween
    for(it = m_iList.begin(); it != m_iList.end(); ++it) {
        if(it->m_data == data.m_data && it != m_iList.begin()) {  
            int addSize = it->m_size;
            it = m_iList.erase(it);
            prev_it->m_size += addSize;
        } 
        if(it->m_data > data.m_data && prev_it->m_data < data.m_data) {
            answer = prev_it->remove(data);
            prev_it->m_size--;
            m_size--;
        }
        prev_it = it;
        try {
            if(answer == -1) {
                throw std::out_of_range("item to remove is not found");
            }
        }
        catch(const std::out_of_range& oor) {
            std::cerr << "Out of range error: " << oor.what() << std::endl;
        }
    }
    consolidate();
}

// removeAt
// allows user to remove an item from the list at a certain index
Int341 SqList::removeAt(int pos) {

    std::list<INode>::iterator it;
    std::list<INode>::iterator prev_it;

    it = m_iList.begin();
    prev_it = m_iList.begin();

    int index = m_iList.begin()->m_size;;
    int prev_index = 0;

    //if its the first element
    if(pos == 0) {
        DNode* temp = m_iList.begin()->m_dNode;
        DNode* curr = new DNode;
        curr = temp->m_next;
        m_iList.begin()->m_dNode = curr;
        delete temp;
        m_iList.begin()->m_size--;
        m_size--;
    }else if(m_iList.empty()) {
        throw std::out_of_range("item not found ");
    } else if(pos > m_size) {
        throw std::out_of_range("item not found");
    } else if(pos < 0) {
        throw std::out_of_range("item not found");
    } else if(pos >= (m_size - m_iList.back().m_size)) {
        //if it is part of the last sublist
        int iIndex = pos - (m_size - m_iList.back().m_size);
        //if it is the DNode that INode points to 
        if(iIndex == 0) {
                DNode* temp = m_iList.back().m_dNode;
                it = m_iList.end();
                it--;
                it--;
                DNode* curr = it->m_dNode;
                for(int i = 0; i < it->m_size - 1; i++) {
                    curr = curr->m_next;
                }
                m_iList.back().m_dNode = curr;
                curr->m_next = temp->m_next;
                delete temp;
                it->m_size--;
                m_size--;
        } else {
            //if its part of the last sublist, but not the one INode is pointing to
            DNode* temp = m_iList.back().m_dNode;
            DNode* prev = new DNode;
            for(int i = 0; i < iIndex; i++) {
                prev = temp;
                temp = temp->m_next;
            }
            prev->m_next = temp->m_next;
            delete temp;
            m_iList.back().m_size--;
            m_size--;
        }
    } else {
        // finding the INode it is pointing to
        int currIndex = m_iList.begin()->m_size;
        int prevIndex = 0;

        //iterating over all INodes
        for(it = m_iList.begin(); it != m_iList.end(); ++it) {
           
            // if inbetween prev and current iteration INodes
            if(pos <= currIndex && pos >= prevIndex) {
                int iIndex = pos - prevIndex;
                if(pos == 0) {
                    DNode* temp = it->m_dNode;
                    DNode* curr = prev_it->m_dNode;
                    for(int i = 0; i < it->m_size - 1; i++) {
                        curr = curr->m_next;
                    }
                    it->m_dNode = curr;
                    curr->m_next = temp->m_next;
                    delete temp;
                    it->m_size--;
                    m_size--;
                } else {
                    DNode* temp = prev_it->m_dNode;
                    DNode* prev = new DNode;
                    for(int i = 0; i < iIndex; i++) {
                        prev = temp;
                        temp = temp->m_next;
                    }
                    prev->m_next = temp->m_next;
                    delete temp;
                    it->m_size--;
                    m_size--;
                }
            }
            prevIndex += currIndex;
            prev_it = it;
            currIndex += it->m_size;
        }
    }
    consolidate();
}

// indexOf
// finds the index of a given piece of data
int SqList::indexOf(const Int341& data) {

    std::list<INode>::iterator it;
    std::list<INode>::iterator prev_it;
    prev_it = m_iList.begin();

    //if its the first element of the list
    if(m_iList.begin()->m_data == data.m_data) {
        return 0;
    } else {
        int currIndex = m_iList.begin()->m_size;
        int prevIndex = 0;
        //iterating over all INodes
        for(it = m_iList.begin(); it != m_iList.end(); ++it) {
           
            //if between the previous and current INode
            if(data < it->m_dNode->m_data && data > prev_it->m_dNode->m_data) {
                DNode* temp = prev_it->m_dNode;    
                int iIndex = 0;
                for(int i = 0; i < prev_it->m_size; i++) {
                    if(temp->m_data == data) {
                        
                    }
                    iIndex++;
                    temp = temp->m_next;
                }
            }
            prevIndex += currIndex;
            prev_it = it;
            currIndex += it->m_size;
        }
    }
}

// numItems
// returns the number of items in the list
int SqList::numItems() {

    return m_size;
}
