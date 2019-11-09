/*****************************************
** File:    User.h
** Project: BattleShip, Fall 2017
** Author:  Samuel Bearman
** Date:    11/16/17
** Section: 14
** E-mail:  bearman1@umbc.edu 
**
**   This file contains the header file of the User class 
**	 this class is a child of Player and  outlines what
**   a human user can do in the game of battleship.
**
***********************************************/

#ifndef _USER_H_
#define _USER_H_

#include "Grid.h"
#include "Player.h"
 
class User: public Player  {
public:
  // Name: User (Default Constructor)
  // Preconditions - None
  // Postconditions - None
  User();
  // Name: User (Overloaded Constructor)
  // Preconditions - None
  // Postconditions - None
  User(string file);
  // Name: makeMove(grid)
  // Preconditions - None
  // Postconditions - Checks if move (x,y) hits or misses (or if already checked)
  void makeMove(Grid* grid);
  // Name: printBoard
  // Preconditions - User's grid exists
  // Postconditions - Displays the users grid
  void printBoard();
};

#endif
