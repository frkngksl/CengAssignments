#ifndef HW4_PRIEST_H
#define HW4_PRIEST_H

#include"Player.h"

class Priest : public Player{
  /**
   * Attack damage 0
   * Heal power 50
   * Max HP 150
   * Goal Priorities -> {HEAL,TO_ALLY,CHEST} in decreasing order
   * Class abbreviation -> "pr" or "PR"
   * Can move to all adjacent squares, including diagonals.
   * Can heal all adjacent squares, including diagonals.
   *
   */
   int attackDamage;
   int healPower;
   int maxHP;
   std::vector<Goal> goalPriorityList;
   std::string classAbbreviation;
   std::vector<Coordinate> attackableCoordinates;
   std::vector<Coordinate> moveableCoordinates;
   std::vector<Coordinate> healableCoordinates;

 public:
   int getAttackDamage() const;
   int getHealPower() const;
   int getMaxHP() const;
   std::vector<Goal> getGoalPriorityList();
   const std::string getClassAbbreviation() const;
   std::vector<Coordinate> getAttackableCoordinates();
   std::vector<Coordinate> getMoveableCoordinates();
   std::vector<Coordinate> getHealableCoordinates();
   Priest(uint id,int x, int y, Team team);
   ~Priest();

};

#endif
