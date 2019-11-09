/*
 * Name: Samuel Bearman
 * File: CipherString.cpp CMSC 202, Fall 2017
 * Date: 11/2/2017
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp is the linekd list file that manages the nodes and functions of the
 * linked list for Cipher.cpp. It utilizes a function for loading cipher letters into linked
 * list, functions for evaluating encryptions and deryptions, and an overloaded friend function
 * for outputing linked list.
 *
 *
 * */
#include "CipherString.h"

using namespace std;

// CipherString Constructor
// This is the Constructor of the actual linked list class, 
CipherString::CipherString() {
  
    m_size = 0;
    m_head = NULL;
    m_tail = NULL;
}

// CipherString overloaded consructor
// This allows for the constructor to take in file info to pass to loadMessage
CipherString::CipherString(const char* c) {

    m_size = 0;
    m_head = NULL;
    m_tail = NULL;
    // calls load message and passes in filename
    loadMessage(c);
}

// loadMessage
// loadMessage passes the arguments in and loads the correct file and loads letters into linked
// list
void CipherString::loadMessage(const char* c){

    char letter = ' ';
    string line = " ";
    ifstream cipherFile(c);
    getline(cipherFile, line);
    // loop used to fill in linkes list nodes and link them all
    for(unsigned int i = 0; i < line.size(); i++) {
        // fills nodes apporpriately, whether it is first node or last
        letter = line[i];
        Node *temp = new Node;
        temp->setChar(letter);
        temp->setNext(NULL);
        if(m_head == NULL) {
            m_head = temp;
            m_tail = temp;
            temp = NULL;
            m_size = 1;
        } else {
            m_tail->setNext(temp);
            m_tail = temp;
            m_size++;
        }
    }     
}


// CipherString 
// Destructor for the linked list, deletes all nodes of linked list
CipherString::~CipherString() {
    // points to head of list
    Node *curr = m_head;
    // iterates through, deleteing each node
    while( curr != 0 ) {
        Node *next = curr->getNext();
        delete curr;
        curr = next;
    }
    // resets head
    m_head = 0;
}


// encryptOng
// Encrytor for the Ong Cipher, converts letters of linked list individually per the Ong 
// rules and inserts new nodes of either "ong" or "ong-" or just "-"
// THIS DOES NOT WORK FULLY, IT CAN INSERT FOR CERTAIN CASES BUT NOT OTHERS
void CipherString::encryptOng() {

    Node *curr = m_head;
   
    while(curr != NULL) {
        switch(curr->getChar()) {
            case 'a':
            case 'A':
            case 'e':
            case 'E':
            case 'i':
            case 'I':
            case 'o':
            case 'O':
            case 'u':
            case 'U':{
                if((curr->getNext())->getChar() != ' ') {
                    Node *insert = new Node;
                    insert->setNext(curr->getNext());
                    insert->setChar('-');
                    curr->setNext(insert);
                    curr = curr->getNext();
                } else {
                    curr = curr->getNext();
                }
                break;
                     }
            case ' ':
                curr = curr->getNext();
                break;
            default:{
                Node *letterO = new Node;
                Node *letterN = new Node;
                Node *letterG = new Node;

                letterO->setChar('o');
                letterN->setChar('n');                
                letterG->setChar('g');

                if((curr->getNext())->getChar() == ' ') {

                    letterG->setNext(curr->getNext());
                
                    curr->setNext(letterO);
                    letterO->setNext(letterN);
                    letterN->setNext(letterG);
                    curr = letterG;
                
                    curr = curr->getNext();
                    break;
                } else {
                    Node *insert = new Node;

                    insert->setChar('-');

                    insert->setNext(curr->getNext());

                    curr->setNext(letterO);
                    letterO->setNext(letterN);
                    letterN->setNext(letterG);
                    letterG->setNext(insert);
                    curr = insert;

                    curr = curr->getNext();
                    break;
                }

                
            }
        }
        curr = curr->getNext();
    }
}


// decryptOng
// decryptor for Ong cipher. removes excess nodes such as "o", "n", "g", and "-" to reveal message
// THIS IS NOT FINISHED, UNABLE TO FINISH
void CipherString::decryptOng() {

    //Node *curr = new node;
   
    //bool letterO;
    //bool letterN;
    //bool letterG
    //curr = m_head;
    //while(curr != NULL) {
       
     //   if((curr->getNext())->getChar() == 'o' ) {





      //  curr = curr->getNext();
   // }

}



// encryptCaesar
// encryptor for Caesar cipher, shifts all given chars in the linked list to specified key
void CipherString::encryptCaesar(int a) {

    Node *curr = m_head;

    // Iterates through whole linked list
    while(curr != NULL) {
        // using ascii table numbers we are able to manipulate each char by adding or subracting
        // using an algorithm
        if(curr->getChar() >= 'a' && curr->getChar() <= 'z') {
            curr->setChar(curr->getChar() + a);
            if(curr->getChar() > 'z') {
                curr->setChar(curr->getChar() - 'z' + 'a' - 1);
            }
        }
        else if(curr->getChar() >= 'A' && curr->getChar() <= 'Z') {
            curr->setChar(curr->getChar() + a);
            if(curr->getChar() > 'Z') {
                curr->setChar(curr->getChar() - 'Z' + 'A' - 1);
            }
        }
        // sets to go to next element of linked list
        curr = curr->getNext();  
    }
}


// decryptCaesar
// decryptor for Caesar cipher, shifts all given chars in the linked list back to original
// state based on key
void CipherString::decryptCaesar(int a) {

    Node *curr = m_head;
    
    // Iterates through whole linked list
    while (curr != NULL) {
        // using ascii table numbers we are able to manipulate each char by adding or subtracting
        // using an algorithm
        if(curr->getChar() >= 'a' && curr->getChar() <= 'z') {
            curr->setChar(curr->getChar() - a);
            if(curr->getChar() < 'a') {
                curr->setChar(curr->getChar() + 'z' - 'a' + 1);
            }
        } else if(curr->getChar() >= 'A' && curr->getChar() <= 'Z') {
            curr->setChar(curr->getChar() - a);
            if(curr->getChar() < 'A') {
                curr->setChar(curr->getChar() + 'Z' - 'A' + 1);
            } 
        }
        // sets to go to next element of linked list
        curr = curr->getNext();
    }

}


// encryptVigenere
// encryptor for Vigenere cipher, creates key relative to size of the linked list, uses key to 
// shift letters based on Vig ciphers table
void CipherString::encryptVigenere(string key) {
 
    // Converts key to match the size of the list for easy decryption
    int listSize = getSize(); // x
    int keySize = key.size(); // y
   
    for(unsigned int i = 0; i < key.length(); i++) {
        key[i] = toupper(key[i]);
    }

    if(keySize >= listSize) {

    } else {
        for(int i = 0; ; i++) {
            if(listSize == i) {
                i = 0;
            }
            if(keySize == listSize) {
                break;
            } 
            keySize++;
            key = key + key[i];
        }     
    }

    
    Node *curr = new Node;
    curr = m_head;
    int charManip = 0; // j
    // iterates over entire linked list
    while(curr != NULL) {
        // uses ascii table numbers and modulus to take each char of linked list 
        // and convert based on key that was made before
        char newChar = curr->getChar();
        if(newChar == ' ') {
            curr = curr->getNext();
        } else {
            if(newChar >= 'a' && newChar <= 'z') {
                newChar += 'A' - 'a';
            } else if(newChar < 'A' || newChar > 'Z') {
                continue;
            }
            newChar = (newChar + key[charManip] - 2 * 'A') % 26 + 'A';
            curr->setChar(newChar);
            charManip = (charManip + 1) % key.length();
            // goes to next node in linked list
            curr = curr->getNext();
        }
    }
}

// decryptVigenere
// decrytor for the vigenere cipher creates key, and iterates over linked list and changes
// each individual char back to original chars
void CipherString::decryptVigenere(string key) {

        
    // Converts key to match the size of the list for easy decryption
    int listSize = getSize(); // x
    int keySize = key.size(); // y
   
    for(unsigned int i = 0; i < key.length(); i++) {
        key[i] = toupper(key[i]);
    }

    if(keySize >= listSize) {

    } else {
        for(int i = 0; ; i++) {
            if(listSize == i) {
                i = 0;
            }
            if(keySize == listSize) {
                break;
            } 
            keySize++;
            key = key + key[i];
        }     
    }

    Node *curr = new Node;
    curr = m_head;
    int charManip = 0; // j
    
    while(curr != NULL) {
        char newChar = curr->getChar();
        if(curr->getChar() == ' ') {
            curr = curr->getNext();
        } else {
            if(newChar >= 'a' && newChar <= 'z') {
                newChar += 'A' - 'a';
            } else if(newChar < 'A' || newChar > 'Z') {
                continue;
            }

            newChar = (newChar - key[charManip] + 26) % 26 + 'A';
            curr->setChar(newChar);
            charManip = (charManip + 1) % key.length();
            curr = curr->getNext();
        }
    }
}


// getSize
// Used to return the size of the linked list
int CipherString::getSize() {

    return m_size;

}

// Overloaded "<<" operator function
// This allows us to easily output the linked list using the "<<" operator
// it iterates over the entire linked list and out puts it to the screen
ostream& operator<<(ostream& os, const CipherString& str) {
    // loop for iterating over entire linked list
    for( Node *curr = str.m_head; curr != NULL; curr = curr->getNext()){
        os << curr->getChar();
    }
    return os;
}
