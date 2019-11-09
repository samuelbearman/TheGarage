#ifndef GAME_H //Header Guard
#define GAME_H //Header Guard

#include "Troop.h"
#include <fstream>

const string PROJ2_TROOPS = "proj2_troops.txt"; //File constant

class Game{
public:
  /* Name: Game() Default Constructor
  // Desc - Builds a new game by: 
  // 1. Asking user for their name,
  // 2. Asking number of troops on team, 
  // 3. Loading all troops from file (function call)
  // 4. Randomizes both teams (function call)
  // 5. Starts game (function call)
  // Preconditions - None
  // Postconditions - m_players is populated (each player has a team)
  //                  and all troops on team - game started 
  */ 
  Game(); //Default Constructor
  // Name: LoadTroops
  // Desc - Loads each troop into m_troop from file
  // Preconditions - Requires file with valid troop data
  // Postconditions - m_troop is populated with Troop objects
  void LoadTroops();
  // Name: RandomizeTeam
  // Desc - Randomly chooses a troop and puts it on a team
  // Preconditions - m_troop is populated
  // Postconditions - m_player and m_computer is populated
  void RandomizeTeam();
  // Name: StartGame()
  // Desc - Manages the game itself including win conditions continually
  //         calling the main menu 
  // Preconditions - Both players have teams with troops
  // Postconditions - Continually checks to see if player/computer has troops
  void StartGame();
  // Name: DisplayTroops()
  // Desc - Displays the current teams (both user and computer)
  // Preconditions - Players have a team with troops
  // Postconditions - Displays a numbered list of troops 
  void DisplayTroops();
  // Name: ChangeTroop()
  // Desc - Allows the user to change current troop
  // Preconditions - Players have troops and have not lost
  // Postconditions - Displays a numbered list of troops and m_curTroop is updated
  void ChangeTroop();
  // Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Players have a team with troops
  // Postconditions - Displays a numbered list of troops
  void MainMenu();
  // Name: DisplayTeams()
  // Desc - Displays the current teams (both player and computer)
  // Preconditions - m_player/m_computer have a team with troops
  // Postconditions - Displays a numbered list of troops
  void DisplayTeams();
  // Name: DisplayTeam()
  // Desc - Displays just player team (for changing current troop)
  // Preconditions - Player and Computer both have troops left
  // Postconditions - Displays a numbered menu
  void DisplayTeam();
  // Name: Attack()
  // Desc - Manages the troops attacking each other
  // If a troop has less than or equal to 0 health, removes "dead" troop from vector
  // FYI: remove element at front of a vector is m_computer.erase(m_computer.begin());
  // If player or computer has no troops left, declares winner
  // Preconditions - Player and Computer both have troops left
  // Postconditions - Depending on whose turn it is, calls attacks
  void Attack();
private:
  vector <Troop> m_troop; //All troops in game
  vector <Troop> m_player; //Player's troops
  vector <Troop> m_computer; //Computer's troops
  int m_max; //Max number of troops on a team
  int m_curTroop; //Currently selected troop (player only)
  int m_curPlayer; //Current player's turn (player or computer)
  string m_name; //Player's name
};

#endif //Exit Header Guard
