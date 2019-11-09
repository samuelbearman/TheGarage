/*************************************  
 * Name: Samuel Bearman
 * File: Game.cpp CMSC 202, Fall 2017
 * Date: 10/19/17
 * Section: 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is the what takes our Troop class (Troop.cpp)
 * and creates game assests from that, we have the main vectors that are 
 * used to hold teams and various methods that use the Troop class. These are
 * the main Methods that are used to make the actual game part, while the Troop
 * class creates the game assets.
 * */

#include "Game.h"
#include "Troop.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>



using namespace std;


// Game Constructor
// Takes in user input that is necessary for constructiong Game class
Game::Game() {

    // Boolean value for testing user input is correct in menu
    bool inputVal = false;

    cout << "What is your name? " << endl;
    cin >> m_name;
    while(inputVal != true) {
        cout << "How many troops on a team? (2-5)" << endl;
        cin >> m_max;
        // Tests to see if user input is between 2 and 5
        if( m_max <= 5 && m_max >= 2) {
            inputVal = true;
        }
    }

    // Calls method to load all possible troops into m_troop vector
    LoadTroops();
    // Calls method that selects random troops from m_troop
    RandomizeTeam();
}



// LoadTroops
// Method that loads data from "proj2_troop.txt" file into Troop class
// then loads each Troop class into vector
void Game::LoadTroops() {
    
    // Variables used to load into Troop constructor
    string troopName;
    int troopHealth;
    int troopDamage;
    string troopTarget;
    bool troopIsFly;

    // Strings for reading data from file to be converted into appropriate typee later
    string flyConversion;
    string healthConversion;
    string damageConversion;

    // Stream variable used to load all data from "proj2_troops.txt" file
    ifstream troopFile("proj2_troops.txt");

    // While loop to loop through each line of file and get data, terminates at EOF
    while(getline(troopFile, troopName, '\t')) {
        getline(troopFile, healthConversion, '\t');
        getline(troopFile, damageConversion, '\t');
        getline(troopFile, troopTarget, '\t');
        getline(troopFile, flyConversion, '\n');

        // Converts string flyConversion into boolean value
        if( flyConversion == "1") {
            troopIsFly = true;
        } else {
            troopIsFly = false;
        }

        // Converts String Conversions into int values
        troopHealth = atoi(healthConversion.c_str());
        troopDamage = atoi(damageConversion.c_str());


        // Calls Troop class and overloads with variables
        Troop newTroops(troopName, troopHealth, troopDamage, troopTarget, troopIsFly);

        // Pushes newly made class into "m_troop" vector
        m_troop.push_back(newTroops);
    }

    // Output to tell if troops were loaded
    cout << "Troops loaded" << endl;
    // Closes troopFile stream
    troopFile.close();
}


// RandomizeTeam
// Method that takes newly created "m_troop" vector and randomly selects troops
// for both player and computer, the amount of troops is specified in original 
// constructor.
void Game::RandomizeTeam() {

    // Used to generate random numbers
    srand(time(NULL));

    // integer values that are random from between 0 and 49
    int troopSelect1 = rand() % 49; 
    int troopSelect2 = rand() % 49;
    
    // vectors used to hold random troops
    vector<Troop> randNumsPlayer;
    vector<Troop> randNumsComputer;  
    

    //randNumsPlayer = m_troop;
    
    // For loop used to load random troops into each "randNum" vector and then insert
    // them into "m_player" and "m_computer" vectors.
    for(int i = 0; i < m_max; i++) {

        // Reinitialize random number each tim through for loop
        troopSelect1 = rand() % 49;
        troopSelect2 = rand() % 49;

        // Sets randNum vectors equal to m_troop
        randNumsPlayer = m_troop;
        randNumsComputer = m_troop;

        // Erases all vectors in "randNumsPlayer" besides the "troopSelect1" index 
        randNumsPlayer.erase(randNumsPlayer.begin() + 0, randNumsPlayer.begin() + troopSelect1);
        randNumsPlayer.erase(randNumsPlayer.begin() + 1, randNumsPlayer.end());

        // Erases all vectors in "randNumsComputer" besides the "troopSelect2" index
        randNumsComputer.erase(randNumsComputer.begin() + 0, randNumsComputer.begin() + troopSelect2);
        randNumsComputer.erase(randNumsComputer.begin() + 1, randNumsComputer.end());

        // Takes both previous vectors and inserts them into "m_player" and "m_computer"
        m_player.insert(m_player.end(), randNumsPlayer.begin(), randNumsPlayer.end());
        m_computer.insert(m_computer.end(), randNumsComputer.begin(), randNumsComputer.end());

    }


}



// DisplayTroops
// Method that returns void, prints out both the player and computer's teams to the
// screen
void Game::DisplayTroops() {

    cout << "********************" << endl;
    cout << m_name << "'s Team" << endl;
    // for loop to print out any possible size of teams
    for(unsigned int i = 0; i < m_player.size(); i++) {
        cout << i + 1 << ". " << m_player[i].GetName() << " " << m_player[i].GetHealth() << endl;
    }
    cout << "********************" << endl;
    cout << "Computer's Team" << endl;
    // for loop to print out any possible size of teams
    for(unsigned int i = 0; i < m_computer.size(); i++) {
        cout << i + 1 << ". " << m_computer[i].GetName() << " " << m_computer[i].GetHealth() << endl;
    }
    cout << "********************" << endl;

}

// DisplayTeam
// Method that is used to be specifically called in the ChangeTroops method. Only shows the 
// players team, not the computers team.
void Game::DisplayTeam() {

    cout << "********************" << endl;
    cout << m_name << "'s Team" << endl;
    // for loop used to print out any possible size of team
    for(int i = 0; i < m_max; i++) {
        cout << i + 1 << ". " << m_player[i].GetName() << " " << m_player[i].GetHealth() << endl;
    }
}



// MainMenu
// Menu method that manages user selection after constructor
void Game::MainMenu() {
    

    int userInput = 0;
    bool inputVal = false;  


    // Method to show what troops each team has
    DisplayTroops();


    // While loop to validate user input is correct
    while(inputVal != true) {

        cout << "What would you like to do? " << endl;
        cout << "1. Display Team" << endl;
        cout << "2. Change Current Troop" << endl;
        cout << "3. Attack" << endl;
        cout << "4. Exit" << endl;
    
        cin >> userInput;

        switch(userInput) {

            case 1:
                // Method for re-displaying current troops
                DisplayTroops();
                break;
            case 2:
                // Method for changing attacking troop
                ChangeTroop();
                break;
            case 3:
                // Method for attacking other teams troops
                Attack(); 
                inputVal = true;
                break;
            case 4:
                // Exits program
                exit(0);
            default:
                // Outputs if user did not put in valid input
                cout << "Invalid entry" << endl;
        }
    }

}


// ChangeTroop
// Method that allows user to select which of their units they would like to attack with
void Game::ChangeTroop() {

    // Method to display only users team
    DisplayTeam();

    cout << "Which Troop would you like to use?" << endl;
    cin >> m_curTroop;
    // Increments users selection back one due to vectors indexes starting at 0 and not 1 
    m_curTroop--;


}


// StartGame
// Method that manages whether the game has been won, if a troop of either team has died,
// and also manages if it is the player or computers turn.
void Game::StartGame() {
    
    // boolean to hold if game has been won
    bool gameWin = false;


    // while loop to stop if game has been won
    while(gameWin != true) {
        // Tests whos turn is next
        if(m_curPlayer % 2 == 0) {
            MainMenu();
        } else {
            Attack();
        }
        // Checks for if a player troop died during the turn
        if(m_player[m_curTroop].GetHealth() <= 0) {
            cout << m_player[m_curTroop].GetName() << " has died!" << endl;
            m_player.erase(m_player.begin());
            m_curTroop = 0;
        }
        // Checks for if a computer troop died during the turn
        if(m_computer[0].GetHealth() <= 0) {
            cout << m_computer[0].GetName() << " has died!" << endl;
            m_computer.erase(m_computer.begin());
        }

        // Checks to see if the size of the player vector is zero, if it is the player has lost
        if(m_player.size() == 0) {
            cout << "The computer has won the game! Better luck next time! " << endl;
            gameWin = true;
        }
        // Checks to see if the size of the computer vecto is zero, if it is the computer has lost
        if(m_computer.size() == 0) {
            cout << m_name << " has won the game! Congratualtions! " << endl;
            gameWin = true;
        }
    }
}

// Attack
// Method that manages when one troop attacks another troop, calls AttackTroop from Troop Class, and
// also increments "m_curPlayer" for StartGame method.
void Game::Attack() {
    
    // If it is the players turn
    if(m_curPlayer % 2 == 0) {
        // Calls Troop class method to attack computer
        m_player[m_curTroop].AttackTroop(m_computer[0]);
        m_curPlayer++;
    } else {
        // Calls Troop class method to attack player
        m_computer[0].AttackTroop(m_player[m_curTroop]);
        m_curPlayer++;
    }



}
