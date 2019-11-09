/*
 * Name: Samuel Bearman
 * File: Grid.cpp CMSC 202, Fall 2017
 * Date: 11/16/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the object class to manage both the User and Computer's grids along with functions that allow
 * them to be changed and manipulated according to the hits and misses and ship placement. 
 *
 *  */
#include "Grid.h"

// Grid Constructor
// Default grid constructor that fills the grid with EMPTY
Grid::Grid() {

    for(int i = 0; i < SIZE; i++) {
        for(int x = 0; x < SIZE; x++) {
            m_grid[x][i] = EMPTY;
        }
    }

}

// Overloaded Grid constructor
// Allows the grid to be constructed and take in a file to read in ship placements and places them on the board
Grid::Grid(string file) {
  
    int shipLength = 0;
    int startCol = 0;
    int startRow = 0;
    char shipOrientation = ' ';

    // Conversion strings for reading from file
    string lengthConversion;
    string colConversion;
    string rowConversion;
    string orientationConversion;

    // Initially fills grid with empty
    for(int i = 0; i < SIZE; i++) {
        for(int x = 0; x < SIZE; x++) {
            m_grid[x][i] = EMPTY;
        }
    }

    ifstream ship(file.c_str());

    while(!ship.eof()) {
         
        shipLength = 0; 
        startCol = 0; 
        startRow = 0;
        shipOrientation = ' ';
        lengthConversion = " ";
        colConversion = " ";
        rowConversion = " ";
        orientationConversion = " ";

        // getting all the information from file lines
        getline(ship, lengthConversion, ' ');
        getline(ship, colConversion, ' ');
        getline(ship, rowConversion, ' ');
        getline(ship, orientationConversion, '\n');

        // Converts all strings from file to appropriate conversions
        startCol = atoi(colConversion.c_str());
        startRow = atoi(rowConversion.c_str());
        shipOrientation = orientationConversion[0]; 
        shipLength = atoi(lengthConversion.c_str());  


        // Evaluates the orientation of ship and loops through until all cells have been changed
        if(shipOrientation == HORIZONTAL) {
            for(int i = startCol; i < (shipLength + startCol); i++) {
                m_grid[i][startRow] = OCCUPIED;
            }

        } else if(shipOrientation == VERTICAL) { 
            for(int i = startRow; i < (shipLength + startRow); i++) { 
                m_grid[startCol][i] = OCCUPIED;
            }
        } 
    }
}

// print
// Takes all information from int m_grid[][] and prints it according to value of each cell, stored in a string and concatenated // to string 
string Grid::print(bool hideShips) {

    string board;

    board += "  0 1 2 3 4 5 6 7 8 9 \n";
        for(int y = 0; y < SIZE; y++) {
            string line = static_cast<ostringstream*>( &(ostringstream() << y) )->str() + " ";
            board += line;
            for(int x = 0; x < SIZE; x++) {
                if(m_grid[x][y] == EMPTY) {
                    
                    board += ". ";
                }
                if(m_grid[x][y] == OCCUPIED) {
                    if(hideShips == true) {
                        board += "# ";
                    } else {
                        board += ". ";
                    }
                }
                if(m_grid[x][y] == HIT) {
                    board += "X ";
                }
                if(m_grid[x][y] == MISS) {
                    board+= "O ";
                }
            }
            board += "\n";
        }
    return board;
}

// noOccupiedLeft
// Checks grid and return boolean value based on whether there are an y ships left on a team
bool Grid::noOccupiedLeft() {

    for(int y = 0; y < SIZE; y++) {
        for(int x = 0; x < SIZE; x++) {
            if(m_grid[x][y] == OCCUPIED) {
                return false;
            }
        }
    }
    return true;
}


// attack
// Used to assign when a hit or miss on the board occurs, also returns int value according to hit or miss
int Grid::attack(int x, int y) {

    if(m_grid[x][y] == OCCUPIED) {
        m_grid[x][y] = HIT;
        return HIT;
    }
    if(m_grid[x][y] == EMPTY) {
        
        m_grid[x][y] = MISS;
        return MISS;
    }
    
    if(m_grid[x][y] == HIT) {
        return -1;
    }
    if(m_grid[x][y] == MISS) {
        return -1;
    } else {
        return 0;
    }
}


// alreadyTried
// Used to establish if cell has already been tried, returns a boolean value
bool Grid::alreadyTried(int x, int y) {

    if(m_grid[x][y] == MISS) {
        return true;
    } else if(m_grid[x][y] == HIT) {
        return true;
    } else {
        return false;
    }
}


// isMiss
// Used to check if cell is a miss
bool Grid::isMiss(int x , int y) {
    
    if(m_grid[x][y] != OCCUPIED) {
        return true;
    } else {
        return false;
    }
}
