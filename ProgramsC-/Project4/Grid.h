/*****************************************
** File:    Grid.h
** Project: BattleShip, Fall 2017
** Author:  Samuel Bearman
** Date:    11/16/17
** Section: 14
** E-mail:  bearman1@umbc.edu 
**
**   This file contains the class header of the Grid class
**	 this class is resposible for keeping track of all
**   spaces on the board and their current state
**
***********************************************/

#ifndef _Grid_H_
#define _Grid_H_

#include <string>
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include <sstream>

using namespace std;

class Grid{ 
public:
  const static int SIZE = 10; //size of board in the x and y directions
  
  //info for reading in orientation of ships
  const static char VERTICAL = 'V';
  const static char HORIZONTAL = 'H';

  //States of each cell
  const static int EMPTY = 0;
  const static int OCCUPIED = 1;
  const static int MISS = 2;
  const static int HIT = 3;
  
  // Name: Grid() Default Constructor
  // Preconditions - 
  // Postconditions - Constructor for the grid
  Grid(); 
  // Name: Grid (file name) - Overloaded Constructor
  // Preconditions - Have file name with valid input
  // Postconditions - Constructor to build grid with ship locations from file
  Grid(string file);
  // Name: alreadyTried(int, int)
  // Preconditions - Have a grid with data
  // Postconditions - Returns true if location has already been checked (returned MISS)
  bool alreadyTried(int x, int y);
  // Name: isMiss(int, int)
  // Preconditions - Have a grid with data
  // Postconditions - Returns true if a location is not occupied
  bool isMiss(int x, int y);
  // Name: attack(int, int)
  // Preconditions - Have a grid with data
  // Postconditions - Returns integer based on result also checks if occupied
  int attack(int x, int y); 
  // Name: noOccupiedLeft()
  // Preconditions - Have a grid with data
  // Postconditions - Returns true if no cells in grid have a value of 1 (checks win)
  bool noOccupiedLeft();
  // Name: print(bool)
  // Preconditions - Have a grid with data
  // Postconditions - Prints the grid - parameter toggles if ships are hidden or not
  string print(bool hideShips);
private:
  int m_grid[SIZE][SIZE]; //Grid to hold integer (game itself)
};

#endif
