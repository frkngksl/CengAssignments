#include"Fighter.h"

/*
YOU MUST WRITE THE IMPLEMENTATIONS OF THE REQUESTED FUNCTIONS
IN THIS FILE. START YOUR IMPLEMENTATIONS BELOW THIS LINE
*/

Fighter::Fighter(uint id,int x, int y, Team team):Player(id,x,y,team){
  this->attackDamage = 100;
  this->healPower = 0;
  this->maxHP = 400;
  this->HP = 400;
  goalPriorityList.push_back(ATTACK);
  goalPriorityList.push_back(TO_ENEMY);
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
    classAbbreviation = "FI";
  }
  else{
    classAbbreviation = "fi";
  }
}
Fighter::~Fighter(){};

int Fighter::getAttackDamage() const{
  return attackDamage;
}
int Fighter::getHealPower() const{
  return healPower;
}
int Fighter::getMaxHP() const{
  return maxHP;
}
std::vector<Goal> Fighter::getGoalPriorityList(){
  return goalPriorityList;
}
const std::string Fighter::getClassAbbreviation() const{
  return classAbbreviation;
}
std::vector<Coordinate> Fighter::getAttackableCoordinates(){
  attackableCoordinates.clear();
  Coordinate currentCoord = this->getCoord();

  attackableCoordinates.push_back(currentCoord + Coordinate(0,1));
  attackableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  attackableCoordinates.push_back(currentCoord + Coordinate(1,0));
  attackableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  return attackableCoordinates;
}
std::vector<Coordinate> Fighter::getMoveableCoordinates(){
  moveableCoordinates.clear();
  Coordinate currentCoord = this->getCoord();

  moveableCoordinates.push_back(currentCoord + Coordinate(0,1));
  moveableCoordinates.push_back(currentCoord + Coordinate(0,-1));
  moveableCoordinates.push_back(currentCoord + Coordinate(1,0));
  moveableCoordinates.push_back(currentCoord + Coordinate(-1,0));
  return moveableCoordinates;
}
std::vector<Coordinate> Fighter::getHealableCoordinates(){
  return healableCoordinates;
}
