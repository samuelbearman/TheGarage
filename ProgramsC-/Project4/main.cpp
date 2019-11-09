/*
 * Name: Samuel Bearman
 * File: main.cpp CMSC 202, Fall 2017
 * Date: 11/16/17
 * Section: 14
 * Email: bearman1@umbc.edu
 * 
 * Description: This .cpp file is the main driver of all of our classes and actually suses the classes to create the
 * game. It takes in the text files from the command line and loads them in and uses a simple modulus to alternate
 * the game turns. 
 *
 *
 *  */
#include "Computer.h"
#include "User.h"
#include "Grid.h"
#include "Player.h"



using namespace std;

int main(int argc, char* argv[]) {

    bool gameRun = true;
    int gameTurn = 0;

    if( argv[1] > 0) {
        cout << "Arguments loaded" << endl;
    } else {
        cout << "No text file loaded" << endl;
    }

    // Creates new User and Computer objects
    User* x = new User(argv[2]); 
    Computer* z = new Computer(argv[1]);

    // Prints current grids
    z->printBoard();
    x->printBoard();

    while(gameRun != false) {

        // If statements to check if game has been won or not
        if((z->getGrid())->noOccupiedLeft() == true) {
            cout << "The computer has no more ships, You won! " << endl;
            gameRun = false;
        }
        if((x->getGrid())->noOccupiedLeft() == true) {
            cout << "All your ships are destroyed, You have lost " << endl;
            gameRun = false;
        }
        
        // Users turn
        if(gameTurn % 2 == 0) {
            cout << "User turn" << endl;
            x->makeMove(z->getGrid());
    
            z->printBoard();
            x->printBoard();

        // Computer turn
        } else {
        
            cout << "Computer turn" << endl;
            z->makeMove(x->getGrid());

            z->printBoard();
            x->printBoard();
        }
        gameTurn++;
    }
}
