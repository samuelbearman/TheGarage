/*
 * Name: Samuel Bearman
 * File: Player.cpp CMSC 202, Fall 2017
 * Date: 11/16/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the Parent class of the files, User.cpp and Computer.cpp. It has fucntions that both can use
 * Two of the functions in this are declared but not specified, they are specified in the respective classes taht use them since
 * they are virtual fucntions
 *  */

#include "Grid.h"
#include "Player.h"

// Player Constructor
// Makes a new Player object and used Grid constructor for m_grid
Player::Player() {
    
    m_grid = new Grid;

}

// Overloaded Player Constructor
// Makes a new Player object and uses Overloaded Grid constructor for m_grid
Player::Player(string file) {

    m_grid = new Grid(file);

}

// Player Destructor
// Deletes m_grid 
Player::~Player() {
    
    delete m_grid;

}

// printBoard
// Virtual function to be used and defined in User.cpp and Computer.cpp
void Player::printBoard() {}

// hasLost
// Method that used noOccupiedLeft to check if the game has been lost or not
bool Player::hasLost() {
   
    if(m_grid->noOccupiedLeft() == true) {
        return true;
    } else { 
        return false;
    }
}

// getGrid
// Simple getter method for getting the grid
Grid* Player::getGrid() {
    
    return m_grid;

}

