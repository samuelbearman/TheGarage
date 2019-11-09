#ifndef TROOP_H //Include/Header Guard
#define TROOP_H //Include/Header Guard

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
using namespace std;

class Troop{
 public:
  // Name: Troop() - Overloaded constructor
  // Desc - Used to build a new troop
  // Preconditions - Requires name, health, damage, target, and isFlying (from file)
  // Postconditions - Creates a new troop
  Troop(string name, int health, int damage, string target, bool isFlying);
  // Name: GetName()
  // Desc - Getter for troop name
  // Preconditions - Troop exists
  // Postconditions - Returns the name of the troop
  string GetName();
  // Name: SetName(string)
  // Desc - Allows the user to change the name of the troop
  // Preconditions - Troop exists
  // Postconditions - Sets name of troop
  void SetName(string name);
  // Name: GetHealth()
  // Desc - Getter for troop health
  // Preconditions - Troop exists
  // Postconditions - Returns the health of the troop
  int GetHealth();
  // Name: SetName(int)
  // Desc - Allows the user to change the health of the troop
  // Preconditions - Troop exists
  // Postconditions - Sets health of troop
  void SetHealth(int health);
  // Name: GetDamage()
  // Desc - Getter for troop name
  // Preconditions - Troop exists
  // Postconditions - Returns the damage of the troop
  int GetDamage();
  // Name: GetTarget()
  // Desc - Getter for troop target ("Both" can attack ground + air)
  //                                ("Ground" can ONLY attack ground)
  // Preconditions - Troop exists
  // Postconditions - Returns what the troop can target
  string GetTarget();
  // Name: GetIsFlying()
  // Desc - Getter for troop flying (1 is flying and only things with target both)
  //                                (0 is not flying)
  // Preconditions - Troop exists
  // Postconditions - Returns if the troop is flying
  bool GetIsFlying();
  // Name: AttackTroop(Troop&)
  // Desc - Allows the user to attack an enemy troop
  // Checks to see if 1. Attacking troop can attack "both" or "ground"
  //                  2. If the target is flying or not.
  //                  3. Updates health of target (current health - damage)
  // Preconditions - Troops exist
  // Postconditions - Health of target is updated
  void AttackTroop(Troop&);
 private:
  string m_name; //Name of troop
  int m_health; //Health of troop
  int m_damage; //Damage of troop
  string m_target; //What the troop can target (Both or Ground) only
  bool m_isFlying; //if the troop is flying (1 = yes)
};

#endif //Exit Header Guard
