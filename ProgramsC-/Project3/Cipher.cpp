/*
 * Name: Samuel Bearman
 * File: Cipher.cpp CMSC 202, Fall 2017
 * Date: 11/2/2017
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: Cipher.cpp is the class that manages the linked list. There are constructors 
 * for each type of cipher and menu managers for each of the ciphers decrypt and encrypt functions 
 *
 *
 * */
#include "Cipher.h"
#include "CipherString.h"

using namespace std;

// Cipher
// main cipher constructor, sets the mode to Ong cipher and intializes m_cipherString to null 
Cipher::Cipher() {

    m_mode = ONG; 
    m_cipherString = NULL;        
}


// Cipher(char)
// Overloaded Cipher constructor, allows us to pass in key for Caesar cipher
Cipher::Cipher(char c) {

    m_mode = CAESAR;
    m_caesar_key = c;
    m_cipherString = NULL;

}

// Cipher(string)
// Overlaoded Cipher constructor, allows us to pass in a key for Vigenere cipher
Cipher::Cipher(string c) {

    m_mode = VIGENERE;
    m_vig_key = c;
    m_cipherString = NULL;
}

 
// setPlaintext
// Creates new m_cipherString(linked list) and pass in file paramateres to load
void Cipher::setPlainText(char* d) {
 
    m_cipherString = new CipherString(d);
}


// encrypt
// switch structure that manages which encrypt function to call for each cipher
void Cipher::encrypt() {

    switch(m_mode) {
        case 1:
            m_cipherString->encryptCaesar(m_caesar_key);
            break;
        case 2:
            m_cipherString->encryptOng();
            break;
        case 3:
            m_cipherString->encryptVigenere(m_vig_key);
            break;
        default:
            cout << "Something went wrong " << endl;
    }
}

// decrypt
// switch structure that manages which decrypt function to call for each cipher
void Cipher::decrypt() {

    switch(m_mode) {
        case 1:
            m_cipherString->decryptCaesar(m_caesar_key);
            break;
        case 2:
            m_cipherString->decryptOng();
            break;
        case 3:
            m_cipherString->decryptVigenere(m_vig_key);
            break;
        default:
            cout << "Something went wrong " << endl;
    }
}


// changeKey
// allows us to change the key of vigenere key
void Cipher::changeKey(string key) {

    m_vig_key = key;

}

// printString
// Uses CipherString's overloaded operator of "<<" to easily print out linked list to menu
void Cipher::printString() {
    cout << *m_cipherString;
}

