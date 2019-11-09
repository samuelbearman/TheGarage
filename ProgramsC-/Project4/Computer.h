/*****************************************
** File:    Computer.h
** Project: BattleShip, Fall 2017
** Author:  Samuel Bearman
** Date:    11/16/17
** Section: 14
** E-mail:  bearman1@umbc.edu 
**
**   This file contains the header file of the Computer class 
**	 this class is a child of Player and  outlines what
**   a CPU or AI player can do in the game of battleship.
**
***********************************************/

#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "Grid.h"
#include "Player.h"
 
class Computer: public Player  {
 public:
  // Name: Computer (Default Constructor)
  // Preconditions - None
  // Postconditions - Creates computer player
  Computer();
  // Name: Computer (Overloaded Constructor)
  // Preconditions - None
  // Postconditions - Creates computer player with file name
  Computer(string file);
  // Name: makeMove()
  // Preconditions - grid is already created
  // Postconditions - Makes an educated guess for next place to fire for computer
  // **This function should be more thoughtful than just two random numbers**
  void makeMove(Grid* grid);
  // Name: printBoard
  // Preconditions - Board exists
  // Postconditions - Prints the computer's board
  void printBoard();  
 private:
  int m_xLast; //x coordinate of last move
  int m_yLast; //y coordinate of last move
  int m_xCenter; //x coordinate of first move of current ship
  int m_yCenter; //y coordinate of first move of current ship
};

#endif
