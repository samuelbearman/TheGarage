#include <iostream> 
using namespace std;

class Node {
    public:
        int m_data;
        Node *m_next;
};


Node* getListFromUser() {

    int num = -1;

    Node *first = new Node;
    Node *prev = new Node;
    cout << "Enter numbers in list, press 0 when done: " << endl;

    
    do {
        if (num == -1) {
            cin >> num;
            if (num == 0) {
                return NULL;
            }
            first->m_data = num;
            first->m_next = NULL;
            prev = first;
        } else if (num != 0){

            cin >> num;    
            if (num == 0) {
                prev->m_next = NULL;
                return first;
            }
            Node *newNode = new Node;
            newNode->m_data = num;
            newNode->m_next = NULL;             
            prev->m_next = newNode; 
            prev = newNode;
        }
    } while (num != 0);

    return first;

}






int main() {

    Node *head, *curr, *next;

    head = getListFromUser();
    next = head;
    while(next != NULL) {
        curr = next;
        next = curr->m_next;
        cout << "Next #: " << curr->m_data << endl;
        delete curr;
    } 
    return 0;
}
