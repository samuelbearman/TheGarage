#ifndef CIPHER_H
#define CIPHER_H

#include "CipherString.h"

class Cipher{
public:
  enum Mode{CAESAR=1, ONG=2, VIGENERE=3};
    // Name: Cipher(char) - Overloaded constructor for Caesar cipher
    // Preconditions - Caesar cipher is defined
    // Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
    Cipher(char);
    // Name: Cipher(string) - Overloaded constructor for Vigenere cipher
    // Preconditions - Vigenere cipher is defined
    // Postconditions - Constructor for the Vigenere cipher (sets m_mode to VIGENERE)
    Cipher(string);
    // Name: Cipher() - Overloaded constructor for Vigenere cipher
    // Preconditions - Ong Cipher is defined
    // Postconditions - Constructor for the Ong cipher (sets m_mode to ONG)
    Cipher();
    // Name: setPlainText
    // Preconditions - File with text is available (in current directory)
    // Postconditions - Stores file text in m_cipherString
    void setPlainText(char*);
    // Name: encrypt
    // Preconditions - m_cipherString populated
    // Postconditions - Calls correct encryption function based on the cipher chosen
    void encrypt();
    // Name: decrypt
    // Preconditions - m_cipherString populated and encrypted
    // Postconditions - Calls correct decryption function based on the cipher chosen
    void decrypt();
    // Name: changeKey
    // Preconditions - key exists
    // Postconditions - Key is updated
    void changeKey(string);
    // Name: printString
    // Preconditions - m_cipherString populated
    // Postconditions - Outputs the value of m_cipherString
    void printString();
private:
    Mode m_mode; //Uses enum to manage type of cipher
    CipherString* m_cipherString; //Linked List of the cipher string
    char m_caesar_key; //Used for Caesar ciphers as the key
    string m_vig_key; //Used for Vigenere ciphers as the key
};
#endif
