#include"Tank.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Tank::Tank(uint id,int x, int y, Team team):Player(id,x,y,team){
  this->attackDamage = 25;
  this->healPower = 0;
  this->maxHP = 1000;
  this->HP = 1000;
  goalPriorityList.push_back(TO_ENEMY);
  goalPriorityList.push_back(ATTACK);
  goalPriorityList.push_back(CHEST);
  attackableCoordinates.push_back(Coordinate(x,y+1));
  attackableCoordinates.push_back(Coordinate(x,y-1));
  attackableCoordinates.push_back(Coordinate(x+1,y));
  attackableCoordinates.push_back(Coordinate(x-1,y));

  moveableCoordinates.push_back(Coordinate(x,y+1));
  moveableCoordinates.push_back(Coordinate(x,y-1));
  moveableCoordinates.push_back(Coordinate(x+1,y));
  moveableCoordinates.push_back(Coordinate(x-1,y));
  if(team == BARBARIANS){
    classAbbreviation = "TA";
  }
  else{
    classAbbreviation = "ta";
  }
}
Tank::~Tank(){};

int Tank::getAttackDamage() const{
  return attackDamage;
}
int Tank::getHealPower() const{
  return healPower;
}
int Tank::getMaxHP() const{
  return maxHP;
}
std::vector<Goal> Tank::getGoalPriorityList(){
  return goalPriorityList;
}
const std::string Tank::getClassAbbreviation() const{
  return classAbbreviation;
}
std::vector<Coordinate> Tank::getAttackableCoordinates(){
  Coordinate currentCoord = this->getCoord();
  attackableCoordinates.clear();
  attackableCoordinates.push_back(currentCoord + Coordinate(0,1));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  attackableCoordinates.push_back(currentCoord + Coordinate(1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  return attackableCoordinates;
}
std::vector<Coordinate> Tank::getMoveableCoordinates(){
  Coordinate currentCoord = this->getCoord();
  moveableCoordinates.clear();
  moveableCoordinates.push_back(currentCoord + Coordinate(0,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  return moveableCoordinates;
}
std::vector<Coordinate> Tank::getHealableCoordinates(){
  return healableCoordinates;
}
