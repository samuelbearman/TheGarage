#include "Cipher.h"
#include "CipherString.h"

// Name: printMenu()
// Preconditions - None
// Postconditions - Chooses which Cipher to use
void printMenu();
// Name: printCipherMenu()
// Preconditions - Cipher already chosen and Cipher linked list populated
// Postconditions - Prints, encrypts, or decrypts message
void printCipherMenu();
// Name: setNext()
// Preconditions - Have a node
// Postconditions - Sets the target of the next pointer
Cipher createCipher(int choice);
// Name: main()
// Preconditions - Have correct mode, Node, Cipher, and CipherString
// Postconditions - Correct cipher (linked list) is created

int main(int argc, char* argv[]){
  int choice;
  Cipher c;

  //Rather than have to enter the name of a test file over and over, use makefile
  //rule to pass the file name in using "command line argument"
  if(argv[1] > 0){
    cout << "Message Loaded" << endl;
  } else{
    cout << "No text file loaded - try make run1" << endl;
    return 0;
  }

  //Chooses the cipher to use and creates the cipher
  do{
    printMenu();
    cin >> choice;
    if (choice == 4)
      return 0;
    c = createCipher(choice); //creates the linked list
  }while(choice < 1 || choice > 4 );
  
  c.setPlainText(argv[1]); //Passes the message to the cipher

  do{
    printCipherMenu();
    cin >> choice;
    switch(choice){
    case 1:
      c.printString();
      break;
    case 2:
      c.encrypt();
      break;
    case 3:
      c.decrypt();
      break;
    case 4:
      return 0;
    }
  }while(choice != 4);
  return 0;
}


void printMenu(){
  cout << endl;
  cout << "Welcome to the Cipher Machine" << endl;
  cout << "Select a type of Cipher:" << endl;
  cout << "1. Caesar Cipher" << endl;
  cout << "2. Vigenere Cipher" << endl;
  cout << "3. Ong Cipher" << endl;
  cout << "4. Cancel" << endl;
}

void printCipherMenu(){
  cout << endl;
  cout << "Select an option:" << endl;
  cout << "1. Print current string" << endl;
  cout << "2. Encrypt" << endl;
  cout << "3. Decrypt" << endl;
  cout << "4. Exit" << endl;
}

Cipher createCipher(int choice){
  string word;
  int key;
  switch(choice){
  case 1:
    cout << "Creating Caesar cipher" << endl;
    cout << "Please enter your key (positive integer): ";
    do{
      cin >> key;
    }while(key<=0);
    return Cipher(key);
  case 2:
    cout << "Creating Vigenere cipher" << endl;
    cout << "Please enter your key (word): ";
    cin >> word;
    return Cipher(word);
  default:
    cout << "Creating ong cipher" << endl;
    return Cipher();
  }
}
