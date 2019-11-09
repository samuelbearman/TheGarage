/*
 * Name: Samuel Bearman
 * File: User.cpp CMSC 202, Fall 2017
 * Date: 11/16/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 *  Description: This .cpp file is the child class of Player.cpp, it is the main class for the actual human user of 
 *  the game. It has its own defintion for making amove in the game and its own specific printing function
 *  */

#include "User.h"
#include "Player.h"

// User Constructor
// Constructs new User using the same methods as the Parent class, Player.cpp
User::User() {

    m_grid = new Grid;

}

// Overloaded User Constructor
// Constructs overloaded User by taking in file same as the Parent class, Player.cpp
User::User(string file) {

   m_grid = new Grid(file); 

}

// makeMove
// Main method for user input with making moves, takes user entered coordinates and checks to see if its a hit or miss
void User::makeMove(Grid* grid) {

    int xAttack;
    int yAttack;

    bool currentAttack = true;

    // While loop for checking user input
    while(currentAttack != false) {
        cout << "Enter the cooridnates to attack: " << endl;
        cout << "Enter x: ";
        cin >> xAttack;
        cout << "Enter y: ";
        cin >> yAttack;

        // Checks if user entered number bigger than 0-9
        if(xAttack < 0 || xAttack > 9 || yAttack < 0 || yAttack > 9) {
            cout << "You have entered a number bigger than 9 or smaller than 0, please try again" << endl;
        } else {
            // Basic logis is, if they already tried, loop back through
            // if its a miss, output miss, end while
            // if its a hit, output hit, end while
            if(grid->alreadyTried(xAttack, yAttack) != true) { 
                if(grid->isMiss(xAttack, yAttack) == true) {
                    cout << "You have missed! " << endl;
                    grid->attack(xAttack, yAttack);
                    currentAttack = false;
                } else {
                    cout << "You hit something!" << endl;
                    grid->attack(xAttack, yAttack);
                    currentAttack = false;
                }
            } else {
            // Output for if the already tried the same coordinates twice
            cout << "You have already tried those coordinates, try again" << endl;
            }
        }     
    }
}



// printBoard
// Virtual function implemented for User, shows ships in game
void User::printBoard() {

    cout << "********User*********" << endl;
    string test = m_grid->print(true);
    cout << test << endl;

}
