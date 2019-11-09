#ifndef CIPHER_STRING_H
#define CIPHER_STRING_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include "Node.h"

using namespace std;

class CipherString{
public:
  // Name: CipherString - default constructor
  // Preconditions - None
  // Postconditions - Creates a new CipherString
  CipherString();
  // Name: CipherString - overloaded constructor
  // Preconditions - None
  // Postconditions - Creates a new CipherString (using char*)
  CipherString(const char*);
  // Name: ~CipherString - destructor
  // Preconditions - None
  // Postconditions - Destroys CipherString
  ~CipherString();  
  // Name: loadMessage
  // Preconditions - File (with text in it) is passed to function
  // Postconditions - Opens file and loads one character at a time into the linked list
  void loadMessage(const char*);
  // Name: addCharacter
  // Preconditions - Linked list exists
  // Postconditions - Adds character to end of linked list
  void addCharacter(char);

  // Name: encryptOng
  // Preconditions - Linked list exists
  // Postconditions - For each consonent, adds a node with "o", adds a node with "n"
  // adds a node with "g". Every "letter" is separated with a "-" and each word is
  // seperated by a space.
  void encryptOng();
  // Name: decryptOng
  // Preconditions - Linked list exists
  // Postconditions - For each consonent, adds a node with "o", adds a node with "n"
  // adds a node with "g". Every "letter" is separated with a "-" and each word is
  // seperated by a space
  void decryptOng();
  // Name: encryptCaesar
  // Preconditions - Linked list exists
  // Postconditions - Shifts each character "right" by the int provided. 
  // See project document for additional details.
  void encryptCaesar(int);
  // Name: decryptCaesar
  // Preconditions - Linked list exists
  // Postconditions - Shifts each character "left" by the int provided.
  // See project document for additional details.
  void decryptCaesar(int);
  // Name: encryptVigenere
  // Preconditions - Linked list exists
  // Postconditions - Shifts each character by the character (in string) provided.
  // See project document for additional details.
  void encryptVigenere(string);
  // Name: decryptVigenere
  // Preconditions - Linked list exists
  // Postconditions - Shifts each character by the character (in string) provided
  // See project document for additional details.
  void decryptVigenere(string);
  
  // Name: getSize
  // Preconditions - Linked list exists
  // Postconditions - Return size of structure
  int getSize();



  void insertNode(char, Node*);
  // Name: operator<< (overloaded insertion operator)
  // Preconditions - Linked list exists
  // Postconditions - Iterates over the linked list and prints each char in each node
  // In this case, friend means that it is accessible outside the class (like public)
  friend ostream& operator<<(ostream&, const CipherString&);

  // For project 3, you may add additional functions in order to help manage
  // the linked list. You can complete this project without adding anything else but
  // you are allowed to edit the CipherString.h file
  
 private:
  Node* m_head; //Node pointer that is the head of the linked list
  Node* m_tail; 
  int m_size; //Size of the linked list (number of nodes)
};

#endif
