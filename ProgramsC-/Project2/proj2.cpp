/*
 * Name: Samuel Bearman
 * File: proj2.cpp CMSC 202, Fall 2017
 * Date: 10/19/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file if the main of the entire program, it ultizes the
 * Troop.h and Game.h files and runs the game. It is only one line long.

*/

#include "Troop.h"
#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

int main () {
  
    // Creates new Game class called "newGame"
    Game newGame;
  
    // Calls method StartGame to start the game
    newGame.StartGame();
  
    // Exits with 0
    return 0;
}
