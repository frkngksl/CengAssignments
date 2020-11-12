#ifndef HW4_ARCHER_H
#define HW4_ARCHER_H

#include"Player.h"

class Archer : public Player{
  /**
   * Attack damage 50
   * Heal power 0
   * Max HP 200
   * Goal Priorities -> {ATTACK}
   * Class abbreviation -> "ar" or "AR"
   * Not able to move at all.
   * Can attack to a range of 2 squares directly up, down, left or right, from
   * its coordinate.
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
   Archer(uint id,int x, int y, Team team);
   ~Archer();

};

#endif
