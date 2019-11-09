/*
 * Name: Samuel Bearman
 * File Troop.cpp CMSC 202, Fall 2017
 * Date: 10/19/17
 * Section 14
 * Email: bearman1@umbc.edu
 *
 * Description: This .cpp file is for the construction and methods used in making 
 * Troop classes. It uses getters and setters for Name, Health, Damage, Target, and
 * isFlying. There is also one more Method called AttackTroop which has a 
 * pass-by-reference for calculating results of one troop attacking another.
 *
 * */

#include "Troop.h"

using namespace std;

// Troop constructor
// Main constructor that takes in Name, Health, Damage, Target, and isFlying values
// and sets them equal to corresponding private variables
Troop::Troop(string name, int health, int damage, string target, bool isFlying) {
    m_name = name;
    m_health = health;
    m_damage = damage;
    m_target = target;
    m_isFlying = isFlying;

}


// GetName
// Returns the name of the Troop
string Troop::GetName() {
    return m_name;    
}

// SetName
// Sets the name of the Troop
void Troop::SetName(string name) {
    m_name = name;
}

// GetHealth
// Returns the health of the troop
int Troop::GetHealth() {
    return m_health;
}

// SetHealth
// Sets the health of the Troop
void Troop::SetHealth(int health) {
    m_health = health;
}

// GetDamage
// Returns the damage of the troop
int Troop::GetDamage() {
    return m_damage;
}

// GetTarget
// Returns the target of the troop
string Troop::GetTarget() {
    return m_target;
}

// GetIsFlying
// Returns the IsFlying value of the troop
bool Troop::GetIsFlying() {
    return m_isFlying;
}

// AttackTroop
// Method that is called by the "Game.cpp" method called "Attack"
// Has a pass-by-reference which is the troop that is being attacked
// Calculates whether the attacking troop can attack the attacked troop,
// then calculates the damage that was taken, and finally outputs the damage done.
void Troop::AttackTroop(Troop& enemyTroop) {

    // If the attacker cand attack both
    if(m_target == "Both") {
        // Calculates damage done
        enemyTroop.SetHealth(enemyTroop.GetHealth() - m_damage);
        // If its flying, output is attacked in air
        if(enemyTroop.GetIsFlying() == true) {
            cout << m_name << " attacks " << enemyTroop.GetName() << " in the air!" << endl; 
            cout << "Damage Done: " << m_damage << endl;;
        // If not in air, it must be on ground
        } else { 
            cout << m_name << " attacks " << enemyTroop.GetName() << " on the ground!" << endl;
            cout << "Damage Done: " << m_damage << endl;
        }
    // If it cant target both, must be ground
    } else {
        // If they are not flying, it can target them
        if(enemyTroop.GetIsFlying() == false) {
            // Calculates damage done
            enemyTroop.SetHealth(enemyTroop.GetHealth() - m_damage);
            cout << m_name << " attacks " << enemyTroop.GetName() << " on the ground!" << endl;
            cout << "Damage Done: " << m_damage << endl;
        // if they are flying then it cant attack
        } else {
            cout << "That troop cannot be targeted" << endl;
        }
    }
}
