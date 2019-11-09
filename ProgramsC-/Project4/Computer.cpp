/*
 * Name: Samuel Bearman
 * File: Computer.cpp CMSC 202, Fall 2017
 * Date: 11/16/17
 * Section: 14
 * Email: bearman1@umbc.edu
 * 
 * Description: This .cpp file is the child class of PLayer.cpp, it is the main class for the Computer. It has its
 * own definitions for making a move, using ranom numbers and logic, and has its own print board function. It also
 * has a few member variables for helping with the Logic of making moves after a hit.
 *  */

#include "Player.h"
#include "Computer.h"

// Computer Constructor
// Makes new Computer object just like parent class, Player.cpp, only exception being that is initializes new values to -1
Computer::Computer() {

    m_grid = new Grid;
    m_xLast = -1;
    m_yLast = -1;
    m_xCenter = -1;
    m_yCenter = -1;
}

//Overloaded Computer Constructor
//Makes new Overloaded Computer Constructor just like parent class, Player.cpp, only exception that it initalizes new values to 
// -1
Computer::Computer(string file) {

    m_grid = new Grid(file);
    m_xLast = -1;
    m_yLast = -1;
    m_xCenter = -1;
    m_yCenter = -1;

}

// printBoard
// Virtual function for print board, does not show ships to User while playing 
void Computer::printBoard() {

    cout << "*******Computer******" << endl;
    string board = m_grid->print(false);
    cout << board << endl;

}

// makeMove
// Computer's version of make move, includes alot of logic for guessing which is the next location to attack at
void Computer::makeMove(Grid* grid) {

    bool currentAttack = true;

    // While loop for current attack
    while(currentAttack != false) {

        // if statement for when the computer knows no information
        // randomly selects spot until it finds a hit
        if(m_xLast == -1 && m_yLast == -1) {
            cout << "Finding new Ship" << endl;
            srand(time(NULL));
            //m_xCenter = 7;
            //m_yCenter = 1;
            m_xCenter = rand() % 9;
            m_yCenter = rand() % 9;
            // Smae logic as User.cpp, but utilizing a random number generator above
            if(grid->alreadyTried(m_xCenter, m_yCenter) != true) {
                if(grid->isMiss(m_xCenter, m_yCenter) == true) {
                    cout << "The computer has missed! " << endl;
                    grid->attack(m_xCenter, m_yCenter);
                    currentAttack = false;
                } else {
                    cout << "The computer has hit your ship!" << endl;
                    grid->attack(m_xCenter, m_yCenter);
                    // Once it has found a hit it initalizes the "Last" member variables equal 
                    m_xLast = m_xCenter;
                    m_yLast = m_yCenter;
                    currentAttack = false;
                }
            }
            //Computer generated random number that was already selected
        // If there has been a hit this logic will now run looking for next possible hit
        } else if(m_xLast != -1 && m_yLast != -1) {

            cout << "search for rest of ship" << endl;
            // Values used to hold 4 spaces around intial hit
            int rightX = m_xLast + 1;
            int leftX = m_xLast - 1;
            int upY = m_yLast + 1;
            int downY = m_yLast - 1;

           
            // Converts any value that is outside the scope of the grid back to appropriate number
            if(rightX < 0) {rightX = 0;}
            if(rightX > 10) {rightX = 10;}
            if(leftX < 0) {leftX = 0;} 
            if(leftX > 10) {leftX = 10;}
            if(upY < 0) {upY = 0;} 
            if(upY > 10) {upY = 10;}
            if(downY < 0) {downY = 0;} 
            if(downY > 10) {downY = 10;}

            
            // Logic for selecting next spot to attack
            // checks if each spot around has already been tried, if not attacks that spot
            // Once it hits a ship again it starts to move in that direction until the rest of the ship is found
            // while the logic is not completely flawless (i.e. doesnt go back to check other direction from original hit)
            // it is still smarter then random numbers picked each time
            if(grid->alreadyTried(rightX, m_yLast) == true) {
                if(grid->alreadyTried(leftX, m_yLast) == true) {
                    if(grid->alreadyTried(m_xLast, upY) == true) {
                        if(grid->alreadyTried(m_xLast, downY) == true) {
                            // All spots around origial hit have been try
                           m_xLast = -1;
                           m_yLast = -1;
                        } else {
                            if(grid->isMiss(m_xLast, downY) == true) {
                                grid->attack(m_xLast, downY);
                            } else {
                                m_yLast = downY; 
                                grid->attack(m_xLast, downY);
                            }
                        }
                    } else {
                        if(grid->isMiss(m_xLast, upY) == true) {
                            grid->attack(m_xLast, upY);
                        } else {
                            m_yLast = upY;
                            grid->attack(m_xLast, upY);
                        }
                    }
                } else { 
                    if(grid->isMiss(leftX, m_yLast) == true) {
                        grid->attack(leftX, m_yLast);
                    } else {
                        m_xLast = leftX;
                        grid->attack(leftX, m_yLast);
                    }
                }
            } else {
                if(grid->isMiss(rightX, m_yLast) == true) {
                    grid->attack(rightX, m_yLast);
                } else {
                    grid->attack(rightX, m_yLast);
                    m_xLast = rightX;
                }
            }
        }
        currentAttack = false;
    }
}
